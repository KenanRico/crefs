#include <stdlib.h>
#include <assert.h>



typedef struct _Envelope{
	int w;
	int h;
} Envelope;


Envelope* getEnvelopes(int);
int maxEnvelopes(Envelope*, int);
int largestEnvelopes(Envelope*, int, int, int*);
void freeEnvelopes(Envelope*);


int main(void){
	int N = 7;

	//get envelopes' dimensions
	Envelope* envelopes = getEnvelopes(N);
	
	//get max russian doll count
	int max_envelopes = maxEnvelopes(envelopes, N);

	//free envelopes
	freeEnvelopes(envelopes);



	return 0;
}


Envelope* getEnvelopes(int N){
	Envelope* e = NULL;
	e = malloc(sizeof(Envelope)*N);
	e[0].w = 6;
	e[0].h = 9;
	e[1].w = 12;
	e[1].h = 8;
	e[2].w = 4;
	e[2].h = 1;
	e[3].w = 10;
	e[3].h = 3;
	e[4].w = 9;
	e[4].h = 4;
	e[5].w = 2;
	e[5].h = 7;
	e[6].w = 1;
	e[6].h = 3;
	return e;
}

int maxEnvelopes(Envelope* env, int N, int largest){

	assert(env!=NULL);

	int* largestEnvIndices = NULL;
	int largestEnvCount = largestEnvelopes(env, N, largest, &largestEnvIndices);
	int max = 0;
	if(largestEnvIndices!=NULL){
		for(int i=0; i<largestEnvCount; ++i){
			int max_dolls = maxEnvelopes(env, N-1, largestEnvIndices[i]);
			if(max_dolls>max){
				max = max_dolls;
			}else{
				//keep going
			}
		}
		free(largestEnvIndices);
	}else{
		//no envelopes left
	}
	return max+1;
}

int largestEnvelopes(Envelope* env, int N, int largest, int* largestEnvIndices){
	swap(env, largest, N-1);
	
	swap(env, largest, N-1);
}


void freeEnvelopes(Envelope* env){
	free(env);
}
