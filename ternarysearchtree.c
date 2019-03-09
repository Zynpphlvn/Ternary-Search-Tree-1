#include <stdio.h>
#include <stdlib.h>
#include <math.h>

struct ternaryTreeNode{
	int data;	//key
	struct ternaryTreeNode *left, *right, *middle;
};

//Prototypes
typedef struct ternaryTreeNode TTNode;
void insert(TTNode **tree, int data);
void printLNMR(TTNode *tree);
TTNode *removeNode(TTNode *tree, int x);
int middleSearch(TTNode *tree);
int max(TTNode *tree);
int min(TTNode *tree);
TTNode* find(TTNode ** tree, int val);
TTNode* findPlace(TTNode ** tree, int val);
int depthLevel(TTNode *tree, int lvl, int key);

main(void){
	FILE* fp = fopen ("input.txt", "r");
	TTNode *ternaryTree = NULL;
	TTNode *tmp;
	
	if (fp){
	  	int i = 0;
	 	while (!feof(fp)){ 
    		fscanf(fp, "%d", &i);
    		insert(&ternaryTree, i);
  		}
  	fclose(fp);
	}
	else{
		printf("No such file!");
	}
	
	printLNMR(ternaryTree);

	int x = 1;
	int num;
	
	while(x != 0){
		printf("Enter -1 for delete a node\n");
		printf("      -2 for search for a node\n");
		printf("      -0 for exit\n");
		scanf("%d", &x);
		if(x == 1){
			printf("Select a number to remove from ternary tree: \n");
			scanf("%d", &num);
			tmp = find(&ternaryTree, num);
			if(tmp != NULL){
				removeNode(ternaryTree, num);
				printf("---------------------------\n");
				printLNMR(ternaryTree);
				printf("Removed node=%d\n", num);
			}
			else{
				printf("Data Not found in tree.\n");
			}
		}
		if(x == 2){
			printf("Select a number to find in ternary tree:\n");
			scanf("%d", &num);
			tmp = find(&ternaryTree, num);
			if(tmp != NULL){
				printf("%d is at %dth depth level", num, depthLevel(ternaryTree, 0, num));
				findPlace(&ternaryTree, num);
			}
			else{
				printf("Data Not found in tree.\n");
			}
		}
		if(x == 0)
			exit(0);
	}
}

void insert(TTNode **tree, int val){	
    TTNode *temp = NULL;
	    
    if(!(*tree)){//if ternary tree is null
        temp = (TTNode *)malloc(sizeof(TTNode));
        temp -> left = temp -> right = temp -> middle = NULL;
        temp -> data = val;
        *tree = temp;
        return;
    }

    if(val < (*tree) -> data)//if key is smaller than current node
    {
        insert(&(*tree) -> left, val);
    } 
	if((val > (*tree) -> data) && (val <= pow((*tree) -> data, 2))){//if key is greater than current node
		insert(&(*tree) -> middle, val);							//and equal or less than the square of current node
	}
    if(val > pow((*tree) -> data, 2)){//if key is greater than square of current node
        insert(&(*tree) -> right, val);
    }
}

TTNode *removeNode(TTNode *tree, int x){//Remove specified node from the tree
	
	if(tree == NULL)
		return NULL;
	
	else{
		if(tree -> data == x){ //if int is current node
			if(tree -> left != NULL && tree -> middle != NULL){//if there is a left child
				if(pow(max(tree -> left), 2) < middleSearch(tree -> middle)){//if there is a integer that bigger than the number that maximum of the left subtree
				//	printf("max of left subtree %d", max(tree->left));
					int a = middleSearch(tree -> middle);
					removeNode(tree, middleSearch(tree -> middle));//remove that bigger integer first
					tree -> data = max(tree -> left);//find the max in left subtree and put it int the parent			
					tree -> left = removeNode(tree -> left, max(tree -> left));//remove max in left subtree
					insert(&tree, a);//insert that bigger integer to tree again
					return tree;
				}
				tree -> data = max(tree -> left);//find the max in left subtree and put it int the parent			
				tree -> left = removeNode(tree -> left, max(tree -> left));//remove max in left subtree
				return tree;
			}
			else if(tree -> left == NULL && tree -> middle != NULL){//if there is no left child
				tree -> data = min(tree -> middle);//find the min in the middle subtree and put it in the parent
				tree -> middle = removeNode(tree -> middle, min(tree -> middle));//remove the min in the middle child
				return tree;
			}
			return NULL;
		}
		if(x < tree -> data){//if int is in left subtree
			tree -> left = removeNode(tree -> left, x);//remove int from left subtree
			return tree;
		}
		else if(x > tree -> data && (x <= pow(tree -> data, 2))){//if int is in middle subtree
			tree -> middle = removeNode(tree -> middle, x);//remove int from middle subtree
			return tree;
		}
		else if(x > pow(tree -> data, 2)){//if int is in right subtree
			tree -> right = removeNode(tree -> right, x);//remove int from right subtree
			return tree;
		}
	}
}

int depthLevel(TTNode *tree, int lvl, int key){//Find depthLevel of node
  	if(!tree) return -1;
	
	if(tree->data == key)
		return lvl;
	
	if(key < tree->data)
		return depthLevel(tree->left, lvl+1,key);
	else if(key > pow(tree -> data, 2))
		return depthLevel(tree->right, lvl+1, key);
	else if(key > tree -> data && key < pow(tree -> data, 2))
		return depthLevel(tree->middle, lvl+1, key);
}

TTNode* find(TTNode ** tree, int val){	
    if(!(*tree)){
        return NULL;
    }

    if(val < (*tree) -> data){
        find(&((*tree) -> left), val);
    }
    else if((val > (*tree) -> data) && (val <= pow((*tree) -> data, 2))){
    	find(&((*tree) -> middle), val);
	}
    else if(val > pow((*tree) -> data, 2)){
        find(&((*tree) -> right), val);
    }
    else if(val == (*tree) -> data){
        return *tree;
    }
}
TTNode* findPlace(TTNode ** tree, int val){
	
    if(!(*tree)){
        return NULL;
    }

    if(val < (*tree) -> data){
        printf(", left subtree of %d", (*tree) -> data);
    	findPlace(&((*tree) -> left), val);
    }
    else if((val > (*tree) -> data) && (val <= pow((*tree) -> data, 2))){
    	printf(", middle subtree of %d", (*tree) -> data);
    	findPlace(&((*tree) -> middle), val);
	}
    else if(val > pow((*tree) -> data, 2)){
        printf(", right subtree of %d", (*tree) -> data);
        findPlace(&((*tree) -> right), val);
    }
    else if(val == (*tree) -> data){
    	printf(". %d is found\n", val);
        return *tree;
    }
}
int max(TTNode *tree){//Find the max node
	while(tree -> right != NULL){
		tree = tree -> right;	
	}
	while(tree -> right == NULL && tree -> middle != NULL){
		tree = tree -> middle;
	}		
	return tree -> data;
}
int min(TTNode *tree){//Find the minimum node in left or middle subtree!!!!!!middle yanlýþ olabilir kontrol ettim ama emin deðilim
	while(tree -> left != NULL)
		tree = tree -> left;
	return tree -> data;
}
int middleSearch(TTNode *tree){
	while(tree -> middle != NULL)
		tree = tree -> middle;
	return tree -> data;
}
void printLNMR(TTNode *tree){//print the tree in left-node-middle-right order
	if(tree){
		printLNMR(tree -> left);
		printf("%d\n", tree -> data);
		printLNMR(tree -> middle);
		printLNMR(tree -> right);
	}	
}
