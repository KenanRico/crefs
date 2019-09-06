#include "heapsort.h"

void ConstructHeap(int* array, int size){
	for(int i=1; i<size; ++i){
		int child = i;
		int parent = (i+1)/2-1;
		while(array[child]<array[parent]){
			int temp = array[child];
			array[child] = array[parent];
			array[parent] = temp;
			if(parent==0) break;
			child = parent;
			parent = (child+1)/2-1;
		}
	}
}

void MaxHeapify(int* array, int size, int i){
	int last = size-1-i;
	int temp = array[0];
	array[0] = array[last];
	array[last] = temp;
	int head = 0;
	int smaller = 0;
	if(last==(head+1)*2-1) {return;}
	else if(last==(head+1)*2) {smaller = (head+1)*2;}
	else {smaller = (array[(head+1)*2-1]<array[(head+1)*2])?(head+1)*2-1:(head+1)*2;}
	while(array[head]<array[smaller]){
		int temp = array[head];
		array[head] = array[smaller];
		array[smaller] = temp;
		if(last==(head+1)*2-1) {return;}
		else if(last==(head+1)*2) {smaller = (head+1)*2;}
		else {smaller = (array[(head+1)*2-1]<array[(head+1)*2])?(head+1)*2-1:(head+1)*2;}
	}
}

void HeapSort(int* array, int size){
	ConstructHeap(array, size);
	for(int i=0; i<size; ++i){
		MaxHeapify(array, size, i);
	}
}
