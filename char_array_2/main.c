#include <stdio.h>



int main(void){
	char data[256];
	data[256] = '\0';
	for(unsigned int i=0; i<255; ++i){
		data[i] = 'x';
	}

	char piece[] = "hi my name is yung lean";



	data = piece;




	printf("Data is: %s\n", data);



	return 0;
}
