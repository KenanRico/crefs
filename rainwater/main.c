//Try to find the first element that is taller or equal, if not then find tallest element that is shorter

#include <stdio.h>
#include <string.h>


#define SIZE 36

int array[SIZE] = {3, 3, 8, 1, 19, 6, 4, 15, 4, 3, 14, 0, 20, 9, 6, 1, 18, 14, 3, 8, 19, 1, 20, 7, 91, 0, 3, 31, 4, 4, 5, 8, 0, 12, 0, 30};

typedef char bool;
#define true 1
#define false 0

void findBarriersInArray(bool*);
int computeWaterVolume(bool*);
void printResult(int);
int min(int, int);


int main(void){
	bool barriers[SIZE]; //all false
	memset(barriers, 0, SIZE);
	barriers[0] = true;
	findBarriersInArray(barriers);
	int volume = computeWaterVolume(barriers);
	printResult(volume);

	return 0;
}


void findBarriersInArray(bool* barriers){
	int i = 0;
	while(i<SIZE){
		//find next bar
		int next_bar = i;
		int tallest_dwarf = 0;
		int tallest_dwarf_pos = i;
		int first_giant_pos = i;
		for(int j=i+1; j<SIZE; ++j){
			if(array[j]>=array[i]){
				next_bar = j;
				break;
			}else{
				if(array[j]>tallest_dwarf){
					tallest_dwarf = array[j];
					tallest_dwarf_pos = j;
					next_bar = j;
				}else{
					//do nothing
				}
			}
		}
		barriers[next_bar] = true;
		//start searching from next bar
		i = next_bar;
		if(i==SIZE-1){
			break;
		}else;
	}
	for(int i=0; i<SIZE; ++i){
		printf("%d ", barriers[i]);
	}
	printf("\n");

}
int computeWaterVolume(bool* barriers){
	//init sum
	int sum = 0;
	//iterate
	int left = 0;
	int right = 0;
	for(int i=1; i<SIZE; ++i){
		if(barriers[i]==true){
			right = i;
			int top = min(array[left], array[right]);
			int rocks = 0;
			for(int r=left+1; r<right; ++r){
				rocks += array[r];
			}
			sum += top*(right-left-1)-rocks;
			left = i;
		}else;
	}
	return sum;
}
void printResult(int vol){
	printf("Array is: ");
	for(int i=0; i<SIZE; ++i){
		printf("%d ", array[i]);
	}
	printf("\n");
	printf("It can hold %d units of rain water\n", vol);
}
int min(int a, int b){
	return (a<b)?a:b;
}
