#include <stdio.h>
#include <stdlib.h>



void getJourneyInfo(unsigned int*, unsigned int**, unsigned int**);
unsigned int minCost(unsigned int const *, unsigned int const *, unsigned int);
void freeArrays(unsigned int*, unsigned int*);


/*----------------Main------------*/
int main(void){
	unsigned int N = 0;
	unsigned int* C = NULL;
	unsigned int* L = NULL;
	getJourneyInfo(&N, &C, &L);
	unsigned int min_cost = minCost(C, L, N);
	printf("Minimum cost is: %d\n", min_cost);
	freeArrays(C, L);
	return 0;
}
/*--------------End Main----------*/


void getJourneyInfo(unsigned int* N_ptr, unsigned int** C_ptr, unsigned int** L_ptr){
	*N_ptr = 8;
	*C_ptr = (unsigned int*)malloc(sizeof(unsigned int)*(*N_ptr));
	*L_ptr = (unsigned int*)malloc(sizeof(unsigned int)*(*N_ptr));
	(*C_ptr)[0] = 12;
	(*C_ptr)[1] = 3;
	(*C_ptr)[2] = 2;
	(*C_ptr)[3] = 2;
	(*C_ptr)[4] = 1;
	(*C_ptr)[5] = 20;
	(*C_ptr)[6] = 7;
	(*C_ptr)[7] = 3;
	(*L_ptr)[0] = 3;
	(*L_ptr)[1] = 5;
	(*L_ptr)[2] = 2;
	(*L_ptr)[3] = 4;
	(*L_ptr)[4] = 10;
	(*L_ptr)[5] = 4;
	(*L_ptr)[6] = 1;
	(*L_ptr)[7] = 6;
}

unsigned int minCost(unsigned int const * C, unsigned int const * L, unsigned int N){
	unsigned int total = 0;
	unsigned int i=0;
	//for every checkpoint
	while(i<N){
		unsigned int amount = 0;
		unsigned int j = 0;
		//for any checkpoint ahead of the current one that has higher petrol price
		while(i+j<N && C[i+j]>=C[i]){
			amount += L[i+j];
			++j;
		}
		//sum up all cost 
		total += amount * C[i];
		//jump straight to jth checkpoint starting from current one
		i += j;
	}
	return total;
}

void freeArrays(unsigned int* C, unsigned int* L){
	free(C);
	free(L);
}
