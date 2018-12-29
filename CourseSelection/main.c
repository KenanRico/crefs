#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>


void getCourseInfo(bool***, int*);
void computeCourseOrder(bool const **, int**, int);
void freeArrays(bool**, int, int*);


int main(void){
	bool** course_info_graph = NULL;
	int N = 0;

	//get number of courses and pre-req info
	getCourseInfo(&course_info_graph, &N);

	for(int i=0; i<N; ++i){
		for(int j=0; j<N; ++j){
			printf("%d ", course_info_graph[i][j]);
		}
		printf("\n");
	}
	printf("\n");

	//init and assign orders
	int* order = NULL;
	computeCourseOrder((bool const **)course_info_graph, &order, N);
	for(int j=0; j<N; ++j){
		printf("%d \n", order[j]);
	}

	//free arrays
	freeArrays(course_info_graph, N, order);

	return 0;
}


void getCourseInfo(bool*** graph, int* N){
	//define N
	*N = 6;
	//init graph
	*graph = malloc(sizeof(bool*) * *N);
	for(int i=0; i<*N; ++i){
		(*graph)[i] = malloc(sizeof(bool) * *N);
		for(int j=0; j<*N; ++j){
			(*graph)[i][j] = false;
		}
	}
	//define graph
	(*graph)[2][1] = true;
	(*graph)[2][3] = true;
	(*graph)[3][0] = true;
	(*graph)[3][1] = true;
	(*graph)[3][4] = true;
	(*graph)[3][5] = true;
	(*graph)[4][5] = true;
	(*graph)[5][0] = true;

}

void computeCourseOrder(bool const ** graph, int** order, int N){
	*order = malloc(sizeof(int)*N);

	//declare course_info auxilary array
	int* course_info = malloc(sizeof(int) * N);
	//init array
	for(int i=0; i<N; ++i){
		int prereqs = 0;
		for(int j=0; j<N; ++j){
			if(graph[j][i]){
				++prereqs;
			}else{
				//do nothing
			}
		}
		course_info[i] = prereqs;
	}

	for(int i=0; i<N; ++i){
		printf("%d %d \n", i, course_info[i]);
	}


	/*iterate through all courses, decrement course_info's element whose value==0, 
		and find corresponding elements in graph to decrement those according 
		elements in course_info*/

	for(int i=0; i<N; ++i){
		int course = -1;
		for(int j=0; j<N; ++j){
			if(course_info[j]==0){
				--course_info[j];
				for(int k=0; k<N; ++k){
					if(graph[j][k]){
						--course_info[k];
					}else;
				}
				course = j;
				break;
			}else;
		}
		if(course>0){
			(*order)[i] = course;
		}else{
			break;
		}
	}


	free(course_info);
}

void freeArrays(bool** graph, int N, int* order){
	for(int i=0; i<N; ++i){
		free(graph[i]);
	}
	free(graph);
	free(order);
}
