#ifndef AVLTREEBOARD_H
#define AVLTREEBOARD_H

#include "Header.h"

struct node
{
	int val;
	int height;
	node* left;
	node* right;
};

class AVLTree
{
private:
	

	node* root;
	int size;

	// helper functions

	// right rotates a certain node
	node* rightRotate(node* oldSub);

	// left rotates a certain node
	node* leftRotate(node* oldSub);

	// gets the balance of a certain node
	int getNodeBalance(node* n);

	// gets the height of a ceratain node
	int height(node* n);

	// traverses in order
	void traverseInOrder(node* n, vector<int>& scores);

public:

	// constructor for the tree
	AVLTree();

	// a function that inserts a node recursively from a certain node
	node* insertRec(node* n, int data);

	// inserts a node without in the tree
	void insert(int val);

	// traverses the whole tree in order
	void traverse(vector<int>&);

	// a getter for the root of the tree
	node* getRoot() const;



	//void scTraversal(node*, int, vector<int>&, vector<int>&);
	//void contTraversal(int, vector<int>&, node*);
	//int leftMost(node* n);
	//static int getNum();
	//int rightMost(node* n);
};

#endif

