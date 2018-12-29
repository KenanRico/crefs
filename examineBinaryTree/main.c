#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>



typedef struct Node{
	int value;
	struct Node* left;
	struct Node* right;
} Node;

typedef struct NodeQueue{
	Node* top;
	Node* bottom;
} NodeQueue;

void buildTree(Node**);
bool fixTree(Node const *);
void destroyTree(Node*);


int main(void){
	//init tree
	Node* tree = NULL;
	buildTree(&tree);
	//examine tree
	bool is_binary_tree = isBinary(tree);
	//print result
	fixTree(tree);
	//destroy tree
	destroyTree(tree);
	return 0;
}


void buildTree(Node** root){
	//int data[20] = {34, 15, 79, };
	*root = malloc(sizeof(Node));
	Node* current = *root;
	current->value = 34;
	current->left = malloc(sizeof(Node));
	current->left->value = 13;
	current->left->left = NULL;
	current->left->right = NULL;
	current->right = malloc(sizeof(Node));
	current->right->value = 79;
	current->right->left = NULL;
	current->right->right = NULL;
	current->left->right = malloc(sizeof(Node));
	current->left->right->value = 40;
	current->left->right->left = NULL;
	current->left->right->right = NULL;
	
}

bool fixTree(Node const * tree){
	int node_count = countNodes(tree);
	Node** node_array = malloc(sizeof(Node*) * node_count);
	fillArray(node_array, node_count);

	Node* first = NULL;
	Node* second = NULL;

	for(int i=0; i<node_count; ++i){
		if(i==0){
			if(node_array[i]->value > node_array[i+1]->value){
				first = node_array[i];
			}else;
		}else if(i==node_count-1){
			if(node_array[i]->value < node_array[i-1]->value){
				first = node_array[i];
			}else;
		}else{
			if(node_array[i]->value > node_array[i+1]->value && node_array[i]->value < node_array[i-1]->value){
				first = node_array[i];
			}else;
		}
	}
}

int countNodes(Node const * current){
	int count = 0;

	for

	return count;
}

void fillArray(Node** array, int size){

}

void destroyTree(Node* curr){
	if(curr==NULL){
		return;
	}else{
		destroyTree(curr->left);
		destroyTree(curr->right);
		free(curr);
	}
}
