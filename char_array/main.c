#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void){
	char str[] = "hi my name is lucas";
	const int size = strlen(str);
	char* p1 = str;
	char* p2 = p1+size-1;
	while(p1<p2){
		char temp = *p1;
		*p1 = *p2;
		*p2 = temp;
		p1++;
		p2--;
	}
	printf("new string is \"%s\"\n", str);
	return 0;
}
