#include "AVLTree.h"

node* AVLTree::rightRotate(node* oldSub)
{
	node* newSub = oldSub->left;
	node* temp = newSub->right;

	newSub->right = oldSub;
	oldSub->left = temp;

	if (height(oldSub->left) > height(oldSub->right))
		oldSub->height = height(oldSub->left) + 1;
	else
		oldSub->height = height(oldSub->right) + 1;

	if (height(newSub->left) > height(newSub->right))
		newSub->height = height(newSub->left) + 1;
	else
		newSub->height = height(newSub->right) + 1;

	return newSub;
}

node* AVLTree::leftRotate(node* oldSub)
{
	node* newSub = oldSub->right;
	node* temp = newSub->left;

	newSub->left = oldSub;
	oldSub->right = temp;

	if (height(oldSub->left) > height(oldSub->right))
		oldSub->height = height(oldSub->left) + 1;
	else
		oldSub->height = height(oldSub->right) + 1;

	if (height(newSub->left) > height(newSub->right))
		newSub->height = height(newSub->left) + 1;
	else
		newSub->height = height(newSub->right) + 1;

	return newSub;

}

int AVLTree::getNodeBalance(node* n)
{
	if (n == NULL)
		return 0;
	else
		return height(n->left) - height(n->right);
}

int AVLTree::height(node* n)
{
	if (n == NULL)
		return 0;
	return n->height;
}

void AVLTree::traverseInOrder(node* n, vector<int>& scores)
{
	if (n == NULL)
		return;
	traverseInOrder(n->left, scores);
	scores.push_back(n->val);
	traverseInOrder(n->right, scores);
}

AVLTree::AVLTree()
{
	root = NULL;
	size = 0;
}

node* AVLTree::insertRec(node* n, int value)
{

	if (n == NULL)
	{
		n = new node;
		n->val = value;
		n->left = NULL;
		n->right = NULL;
		n->height = 1;
		size++;
		return n;
	}

	if (value < n->val)
		n->left = insertRec(n->left, value);
	else if (value > n->val)
		n->right = insertRec(n->right, value);
	else
		return n;

	if (height(n->left) > height(n->right))
		n->height = 1 + height(n->left);
	else
		n->height = 1 + height(n->right);

	int balance = getNodeBalance(n);

	if (balance > 1 && value < n->left->val)
		return rightRotate(n);
	else if (balance < -1 && value > n->right->val)
		return leftRotate(n);
	else if (balance > 1 && value > n->left->val)
	{
		n->left = leftRotate(n->left);
		return rightRotate(n);
	}
	else if (balance < -1 && value > n->right->val)
	{
		n->right = rightRotate(n->right);
		return leftRotate(n);
	}

	return n;


}

void AVLTree::insert(int value)
{
	root = insertRec(root, value);
}

void AVLTree::traverse(vector<int>& sc)
{
	traverseInOrder(root, sc);
}

node* AVLTree::getRoot() const
{
	return root;
}







/*
void AVLTree::contTraversal(int currSc, vector<int>& high, node* n)
{
	vector<int> tr;
	traverseInOrder(root, tr);
	high.push_back(tr[0]);
	high.push_back(tr[1]);
	tr.clear();
	cout << "before the traversal" << endl;
	scTraversal(root, currSc, high, tr);
	cout << "after the traversal" << endl;
}



void AVLTree::scTraversal(node* n, int currScore, vector<int>& high, vector<int>&sc)
{
	//cout << "the n is now " << n << endl;

	if (n == NULL)
		return;

	if (n->left == NULL || n->right == NULL)
		return;

	//cout << "after the if" << endl;

	scTraversal(n->left, currScore, high, sc);
	//cout << "im before the traversal" << endl;
	if(n->val > currScore)
		cout << "the value now is " << n->val << endl;
	cout << "the rightmost value is " << rightMost(n->left) << endl;

	if (n->val > currScore && currScore > rightMost(n->left))
	{
		cout << "i got the two values" << endl;
		high[1] = n->val;
		
		high[0] = leftMost(n->right);
		return;
	}
	scTraversal(n->right, currScore, high, sc);
}



int AVLTree::leftMost(node* n)
{
	if (n->left == NULL)
		return n->val;
	
	return leftMost(n->left);

	if (n->left == NULL);
		return n->val;

	return leftMost(n->right);
}

int AVLTree::getNum()
{
	return num;
}

int AVLTree::rightMost(node* n)
{
	if (n->right == NULL)
		return n->val;

	return rightMost(n->right);

	if (n->right == NULL);
	return n->val;

	return rightMost(n->left);
}
*/