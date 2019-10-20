#include <stdio.h>


struct Train{
	int a;
	int b;
	double c;
	int d;
	char e;
	int f;
};

int main(void){
	struct Train t = {1,2,3,4,5,6};
	printf("%p\n", &t.a);
	printf("%p\n", &t.b);
	printf("%p\n", &t.c);
	printf("%p\n", &t.d);
	printf("%p\n", &t.e);
	printf("%p\n", &t.f);
	return 0;
}
