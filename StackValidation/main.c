#include <stdio.h>


int SequenceIsValid(int const *, size_t, int const *, size_t);

int main(void){
	int push[] = {1,2,3,6,5,7};
	int pop[] = {2,6,7,5,3,1};
	size_t pushs = sizeof(push)/sizeof(int);
	size_t pops = sizeof(pop)/sizeof(int);

	int valid = SequenceIsValid(push, pushs, pop, pops);

	if(valid==1){
		printf("Sequences are valid\n");
	}else if(valid==0){
		printf("Sequences are not valid\n");
	}


	return 0;
}

int SequenceIsValid(int const * push, size_t push_size, int const * pop, size_t pop_size){
	int const * p1 = push;
	int const * p2 = pop;
	int popped = 0;
	while(popped!=pop_size){
		if(*p1==*p2){
			
		}
	}
}
