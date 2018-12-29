#include <stdio.h>


void func1(void);
void func2(void);
void func3(void);

int main(void){

	for(unsigned int i=0; i<1000000; ++i){
		func1();
		func2();
		func3();
	}

	return 0;
}

void func1(void){
	int x = 0;
	for(unsigned int i=0; i<500; ++i){
		x += 10;
	}
	//printf("%d\n", x);
}

void func2(void){
	int x = 0;
	for(unsigned int i=0; i<2000; ++i){
		x += 10;
	}
	//printf("%d\n", x);
}

void func3(void){
	int x = 0;
	for(unsigned int i=0; i<10000; ++i){
		x += 10;
	}
	//printf("%d\n", x);
}
