#include <stdio.h>
#include <string.h>

int gcd(int, int);

int main(void){
	int a = 96;
	int b = 84;
	int g = gcd(a,b);
	printf("gcd is %d\n", g);
	return 0;
}

int gcd(int a, int b){
	int larger = a>b?a:b;
	int smaller = a>b?b:a;
	int c = larger%smaller;
	while(c!=0){
		larger = smaller;
		smaller = c;
		c = larger%smaller;
	}
	return smaller;
}
