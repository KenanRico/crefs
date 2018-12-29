#include "myqueue.h"

#include <stdio.h>
#include <stdlib.h>


typedef struct node{
	int ID;
	struct node* left;
	struct node* right;
} Node;


Node* genTree();
Node* findDeepestParent(Node const *, int, int);
void freeTree(Node*);
void printTree(Node const *);


int main(void){
	Node* root = genTree();
	printTree(root);
	int a = 17;
	int b = 40;
	Node* parent = findDeepestParent(root, a, b);
	if(parent!=NULL){
		printf("Parent's ID is %d\n", parent->ID);
	}else{
		printf("Unable to find a parent\n");
	}
	freeTree(root);
	return 0;
}


Node* genTree(){
	Node* root = malloc(sizeof(Node));
	root->ID = 12;
	Node* l0 = (root->left = malloc(sizeof(Node)));
	l0->ID = 49;
	Node* r0 = (root->right = malloc(sizeof(Node)));
	r0->ID = 6;
	Node* l1 = (l0->left = malloc(sizeof(Node)));
	l1->ID = 19;
	Node* r1 = (l0->right = malloc(sizeof(Node)));
	r1->ID = 27;
	Node* l2 = (r0->left = malloc(sizeof(Node)));
	l2->ID = 3;
	Node* r2 = (r0->right = malloc(sizeof(Node)));
	l2->ID = 1;
	Node* l3 = (l2->left = malloc(sizeof(Node)));
	l3->ID = 55;
	Node* l4 = (l3->left = malloc(sizeof(Node)));
	l4->ID = 20;
	Node* r4 = (l3->right = malloc(sizeof(Node)));
	r4->ID = 5;
	Node* l5 = (l1->left = malloc(sizeof(Node)));
	l4->ID = 16;
	Node* r5 = (l1->right = malloc(sizeof(Node)));
	r4->ID = 40;
	return root;
}

Node* findDeepestParent(Node const * root, int a, int b){
	return NULL;
}

void freeTree(Node* node){
	//push root into queue

	//make loop on condition (!empty(queue)) that run below procedure
		//pop queue and get node
		//free that node
		//push node's children

	//done

	if(node==NULL){
		//do nothing
	}else if(node->left==NULL && node->right==NULL){
		free(node);
	}else{
		if(node->left!=NULL){
			freeTree(node->left);
		}
		if(node->right!=NULL){
			freeTree(node->right);
		}
		free(node);
	}
}

void printTree(Node const * node){

	if(node==NULL){
		//do nothing
	}else{
		printf("%d ", node->ID);
		if(node->left!=NULL){
			printTree(node->left);
		}
		if(node->right!=NULL){
			printTree(node->right);
		}
	}

}
