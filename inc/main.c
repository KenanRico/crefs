#include <stdio.h>

int main(){
	int i = 0;
	if(&i==&(++i)){
		printf("yes \n");
	}else;

	return 0;
}
