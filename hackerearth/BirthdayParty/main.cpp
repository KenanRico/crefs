


int N = 0;
int* C = NULL;
int* W = NULL;
int M = 0;
int* L = NULL;



int main(void){
	getInfo();
	sortArrays();

	int min_time = minTime(apetite_asc, weight_dec);



	return 0;
}
//feed largest cake to person with smallest apetite


void getInfo(){
	N = 6
	M = 10;
	C = (int*)malloc(sizeof(int)*N); //amounts
	W = (int*)malloc(sizeof(int)*N); //weights
	L = (int*)malloc(sizeof(int)*M); //apetite
	
}

int minTime(){ //assuming W is in descending order (C is sorted according to W) and L is sorted in ascending order
	for(int i=0; i<N; ++i){ //weights
		for(int j=0; j<M; ++j){ //apetite
			if(W[i]<L[j]){
				int fit = L[j]/W[i];
				int ate = 0
				if(C[i]>=number){
					ate = fit;
					C[i] -= fit;
				}else{
					ate = C[i];
					C[i] = 0;
				}
				L[j] -= ate * W[i];
			}else;
		}
	}

	int ate_all = 0;
	if(allGone()){
		ate_all = 1;
	}else{
		ate_all = -1;
	}
	
	return ate_all;
}

bool allGone(){
	for(int i=0; i<N; ++i){
		if(C[i]!=0){
			return false;
		}else;
	}
	return true;
}

void sortArrays(){
	//sort W then C
	
}
