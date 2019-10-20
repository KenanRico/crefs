#include <types.h>
#include <kern/errno.h>
#include <lib.h>
#include <machine/pcb.h>
#include <machine/spl.h>
#include <machine/trapframe.h>
#include <kern/callno.h>
#include <syscall.h>
#include <thread.h>

#include "addrspace.h"
#include "vfs.h"


/*
 * System call handler.
 *
 * A pointer to the trapframe created during exception entry (in
 * exception.S) is passed in.
 *
 * The calling conventions for syscalls are as follows: Like ordinary
 * function calls, the first 4 32-bit arguments are passed in the 4
 * argument registers a0-a3. In addition, the system call number is
 * passed in the v0 register.
 *
 * On successful return, the return value is passed back in the v0
 * register, like an ordinary function call, and the a3 register is
 * also set to 0 to indicate success.
 *
 * On an error return, the error code is passed back in the v0
 * register, and the a3 register is set to 1 to indicate failure.
 * (Userlevel code takes care of storing the error code in errno and
 * returning the value -1 from the actual userlevel syscall function.
 * See src/lib/libc/syscalls.S and related files.)
 *
 * Upon syscall return the program counter stored in the trapframe
 * must be incremented by one instruction; otherwise the exception
 * return code will restart the "syscall" instruction and the system
 * call will repeat forever.
 *
 * Since none of the OS/161 system calls have more than 4 arguments,
 * there should be no need to fetch additional arguments from the
 * user-level stack.
 *
 * Watch out: if you make system calls that have 64-bit quantities as
 * arguments, they will get passed in pairs of registers, and not
 * necessarily in the way you expect. We recommend you don't do it.
 * (In fact, we recommend you don't use 64-bit quantities at all. See
 * arch/mips/include/types.h.)
 */
extern struct thread* curthread;

void
mips_syscall(struct trapframe *tf) {
    int callno;
    int32_t retval;
    int err;

    assert(curspl == 0);

    callno = tf->tf_v0;

    /*
     * Initialize retval to 0. Many of the system calls don't
     * really return a value, just 0 for success and -1 on
     * error. Since retval is the value returned on success,
     * initialize it to 0 by default; thus it's not necessary to
     * deal with it except for calls that return other values, 
     * like write.
     */

    retval = 0;

    switch (callno) {
        case SYS_reboot:
            err = sys_reboot(tf->tf_a0);
            break;

        case SYS_fork:
            err = fork(tf, &retval);
            break;

        case SYS_getpid:
            err = 0;
            retval = curthread->process_id;
            break;

        case SYS_waitpid:
            err = waitpid(tf->tf_a0, tf->tf_a1, tf->tf_a2, &retval);
            break;

        case SYS__exit:
            exit(tf->tf_a0);
            break;

        case SYS_read:
            err = sys_read(tf->tf_a0, (char *) tf->tf_a1, tf->tf_a2, &retval);
            break;

        case SYS_write:
            err = sys_write(tf->tf_a0, (void *) tf->tf_a1, tf->tf_a2, &retval);
            break;

        case SYS_execv:
            err = execv((const char *)tf->tf_a0, (char *const*)tf->tf_a1, &retval);
            break;

            /* Add stuff here */

        default:
            kprintf("Unknown syscall %d\n", callno);
            err = ENOSYS;
            break;
    }


    if (err) {
        /*
         * Return the error code. This gets converted at
         * userlevel to a return value of -1 and the error
         * code in errno.
         */
        tf->tf_v0 = err;
        tf->tf_a3 = 1; /* signal an error */
    } else {
        /* Success. */
        tf->tf_v0 = retval;
        tf->tf_a3 = 0; /* signal no error */
    }

    /*
     * Now, advance the program counter, to avoid restarting
     * the syscall over and over again.
     */

    tf->tf_epc += 4;

    /* Make sure the syscall code didn't forget to lower spl */
    assert(curspl == 0);
}

int
fork(struct trapframe *tf, int* retval) {
    int s = splhigh();

    struct addrspace *childSpace;
    struct thread *childthread;
    struct trapframe *child_tf;

    int value = as_copy(curthread->t_vmspace, &childSpace);

    if (value != 0) {
        splx(s);
        return value;
    }
    if (childSpace == NULL) {
        splx(s);
        return -1;
    }
    child_tf = kmalloc(sizeof (struct trapframe));

    if (child_tf == NULL) {
        splx(s);
        return ENOMEM;

    }
    memcpy(child_tf, tf, sizeof (struct trapframe));
    value = thread_fork(curthread->t_name, (void*) child_tf, (unsigned long) childSpace, md_forkentry, &childthread);

    if (value != 0) {
        splx(s);
        return ENOMEM;
    }


    *retval = childthread->process_id;
    splx(s);
    return 0;
}

void
md_forkentry(void *tf, unsigned long childSpace) {

    struct trapframe child_tf = *(struct trapframe*) tf;

    child_tf.tf_v0 = 0;
    child_tf.tf_a3 = 0;
    child_tf.tf_epc += 4;
    curthread->t_vmspace = (struct addrspace*) childSpace;
    as_activate(curthread->t_vmspace);

    mips_usermode(&child_tf);


}

void
exit(int code) {
    process_exitcode[curthread->process_id] = code;
    process_exit[curthread->process_id] = 1;
    if (curthread->process_id >= 10)
        V(process_sem[curthread->process_id]);

    thread_exit();

}

int
waitpid(pid_t pid, int* status, int options, int* retval) {
    if (process_occupied[pid] == 0 || options != 0)
        return EINVAL;
    if (parent_thread[pid] != curthread)
        return EINVAL;
    if (status == NULL)
        return EFAULT;

    P(process_sem[pid]);

    *status = process_exitcode[pid];
    *retval = pid;

    process_exit[pid] = 0;
    process_exitcode[pid] = 0;
    parent_thread[pid] = NULL;
    sem_destroy(process_sem[pid]);
    process_occupied[pid] = 0;
    return 0;
}

int
sys_read(int fd, char *buf1, size_t buflen, int* retval) {

    if (buf1 == NULL) {

        *retval = -1;
        return EFAULT;
    }
    if (fd != 0) {
        *retval = -1;

        return EBADF;
    }
    if (buflen == 0){
     *retval = -1;

     return EIO;
    }
    int counter;
    for (counter = 0; counter < buflen; counter++) {
        char* charbuf;
        *charbuf = (char) getch();
        if (charbuf == NULL){
            *retval = -1;

            return EFAULT;
        }

        int a = copyout((void*)charbuf, (userptr_t) buf1 + counter, 1);
        if (a != 0){
            *retval = -1;

            return a;
        }
        buf1++;

    }
    *retval = buflen;

    return 0;
    
    
    
    

    
    
    
    
    
    
    
    
    
    
}

int
sys_write(int fd, void *buf1, size_t buflen, int* retval) {

    char *buf;
    buf = kmalloc(sizeof(char) * (buflen + 1));

    if (buf == NULL) {
        *retval = -1;

        return ENOMEM;
    }
    if (buf1 == NULL) {
        *retval = -1;
        return EFAULT;
    }
    if (buflen == 0){
     *retval = -1;
     return EIO;
    }
    if (fd != 1 && fd != 2) {
        *retval = -1;

        return EBADF;
    }

    
    copyin((const_userptr_t)buf1, buf, buflen);
    buf[buflen] = '\0';
    int i;
    for(i = 0; i < buflen; i++){
        putch((int)buf[i]);
    }
    *retval = buflen;
    kfree(buf);

    return 0;
    
    
    

}





int
execv(const char *program, char *const *args,int *retval){
    int spl=splhigh();
    if(program==NULL){
        return EINVAL;
        
    }
    struct vnode *v;
    char* path = (char *) kmalloc(128 * sizeof(char));
    curthread->t_vmspace=as_create();
    if(curthread->t_vmspace){
        vfs_close(v);
        return ENOMEM;
    }
    
}
