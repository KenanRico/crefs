#include <stdlib.h>



void getInfo(int*, int**, int*, int*);
int minCapacity(int, int *, int, int);
void moveStation(int*, float const *, const int);


int main(void){
	int distance = 0;
	int* pos = NULL;
	int movable_station_count = 0;
	int money = 0;
	getInfo(&distance, &pos, &movable_station_count, &money);
	int bus_capacity = minCapacity(distance, pos, movable_station_count, money);


	return 0;
}


void getInfo(int* dis, int** pos, int* num_station, int* money){
	*dis = 20;
	*num_station = 5;
	*money = 8;
	*pos = (int*)malloc(sizeof(int)*num_station);
}

int minCapacity(int dis, int* pos, int num_station, int budget){
	int result = 0;
	if(dis>0 && num_station>0 && budget>0){
		
		//define array "ideal_pos" that represents ideal positions for optimal solution
		float* ideal_pos = malloc(sizeof(int)*num_station);
		float average_gap = (float)dis / (num_station+1);
		for(int i=0; i<num_station){
			ideal_pos[i] = average_gap * (i+1);
		}

		//ultimate goal is to minimize the largest gap between any two stations (including end stations at two ends)
		//below procedure uses greedy algorithm
		/*
		The algorithm works as below: First define an array which stores ideal positions. Then run a loop that executes C iterations (C being 
		the bedget in dollars). For every iteration, check the largest gap between any two stations. For the two stations with largest gap,
		check each against its ideal position. Then move the station (among the two) that is further from its ideal position 1 unit toward its
		ideal position.
		Corner cases: If there exist more than one pair of stations that has the largest gap:
			- First filter out any station that, if moved, results in a new largest gap. 
			- Among the remaining stations, move the one that is furthest from its ideal position.
			- If there exist more than one station that has the furthest gap from its ideal position, pick one at random
		*/
		for(int i=0; i<budget; ++i){
			moveStation(pos, ideal_pos, num_station);
		}
		free(ideal_pos);
	}else{
		result = -1;
		printf("ERROR: invalid info \n");
	}
	return result;
}

void moveStation(int* pos_int, float const * ideal_pos, const int num_station, int distance){
	//get a float pointer to pos
	float* pos = (float*)pos_int;

	//end gaps
	const float left_gap = pos[0];
	const float hotel_gap = (float)distance - pos[num_station];

	//allocate arrays to keep track of stations across largest gaps
	int* left = malloc(sizeof(int)*num_station);
	int* right = malloc(sizeof(int)*num_station);
	
	//declare largest gap info var
	float largest_gap = 0.0f;
	int num_largest_gap = 0;

	//init infos
	if(left_gap > right_gap){
		largest_gap = left_gap;
		num_largest_gap = 1;
		left[0] = -1;
		right[0] = 0;
	}else if(right_gap>left_gap){
		largest_gap = right_gap;
		num_largest_gap = 1;
		left[0] = num_station-1;
		right[0] = -1;
	}else if(left_gap==right_gap){
		largest_gap = left_gap;
		num_largest_gap = 2;
		left[0] = -1;
		right[0] = 0;
		left[1] = num_station-1;
		right[1] = -1;
	}else{
		printf("ERROR: impossible case \n");
		return;
	}

	//find largest gap distance, and positions of stations across largest gaps
	float prev_pos = 0.0f;
	for(int i=1; i<num_station; ++i){
		if(pos[i]-prev_pos > largest_gap){
			//new largest gap found, reset then update left/right, update largest_gap and num_largest_gap
			left[0] = i-1;
			right[0] = i;
			for(int i=1; i<num_largest_gap; ++i){
				left[i] = 0;
				right[i] = 0;
			}
			largest_gap = pos[i] - prev_pos;
			num_largest_gap = 1;
		}else if(pos[i]==largest_gap){
			//equally large largest gap found, update left/right, update num_largest_gap
			left[num_largest_gap] = i-1;
			right[num_largest_gap] = i;
			++num_largest_gap;
		}else{
			//nothing happens, check next gap
		}
		prev_pos = pos[i];
	}

	//move a station according to left/right and largest_gap and num_largest_gap
	if(num_largest_gap==1){
		//one largest gap
		float diff_from_ideal_a = ideal_pos[left[0]]-pos[left[0]];
		float diff_from_ideal_b = ideal_pos[right[0]]-pos[right[0]];
		if(absolute(diff_from_ideal_a) > absolute(diff_from_ideal_b)){
			pos_int[left[0]] += (diff_from_ideal_a > 0) ? 1 : -1;
		}else if(absolute(diff_from_ideal_a) < absolute(diff_from_ideal_b)){
			pos_int[right[0]] += (diff_from_ideal_b > 0) ? 1 : -1;	
		}else if(absolute(diff_from_ideal_a)==absolute(diff_from_ideal_b)){
			//move a station that does not create larger largest gap

		}else{
			//impossible case
			printf("ERROR: impossible case \n");			
			return;
		}

	}else if(num_largest_gap>1)
		//multiple largest gaps
		for(){

		}
	}else{
		//no largest gaps, do nothing
	}
	
	//free dynamic mem
	free(left);
	free(right);
}
