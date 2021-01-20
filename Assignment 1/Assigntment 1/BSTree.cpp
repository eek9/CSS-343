#include "BSTree.h"
#include <iostream>
#include <algorithm>
#include <fstream>
//
//Created by Eunhee Kim on 04/20/2020
//
using namespace std;

//default constructor for the BSTree that will initiate all the
//variables to null
BSTree::BSTree() : data(NULL), left(NULL), right(NULL)
{
}

//paramaterized constructor to initiate the root node to be an 
//integer from an input
BSTree::BSTree(int i) : data(i), left(NULL), right(NULL)
{
}

//insert method will add a node into a binary search tree
BSTree* BSTree::add(BSTree* r, int node)
{
	//if the root of the binary search tree is null, then it will
	//return a new Binary search tree oject that initializes the node
	//to be inserted as the root
	if (r == NULL) {
		return new BSTree(node);
	}
	//if the node to be inserted is less than the root of the binary search
	//tree, we will recursively add the node to the left unless otherwise
	else if (node < r->data) {
		r->left = add(r->left, node);
	}
	//else, the node would be greater than the root, so we will recursively be adding the
	//new node to the right
	else {
		r->right = add(r->right, node);
	}
	return r;
}

//this method will return an int of the height from the given binary search tree
//starting from the root
int BSTree::findHeight(BSTree *r)
{
	//if the root is null, it will return a height of one
	if (r == NULL) {
		return 1;
	}
	//else, it will continue to recursively go down through the tree from left or right
	//(depending which side is taller) and then return the height
	else {
		return 1 + max(findHeight(r->left), findHeight(r->right));
	}
}

//this method will calculate the amount of nodes in the binary search tree
void BSTree::nodeAmt(BSTree *r, int &n)
{
	//if the root is null, it will just return without calculating
	//an addition to the n measuremnt
	if (r == NULL) {
		return;
	}
	//else, it will recursively continue to the left and right areas
	//of the node, incrementing the n whenever the data exists to
	//calculate the amount of nodes
	nodeAmt(r->left, n);
	n++;
	nodeAmt(r->right, n);
}

//this method will check to find if the binary search tree is balanced
bool BSTree::isBalanced(BSTree *r)
{
	//a tree with a null root is balanced, so it will return true
	if (r == NULL) {
		return true;
	}
	//else, we will calculate both sides of the left and right side heights
	//of the tree
	else {
		int ls = findHeight(r->left);
		int rs = findHeight(r->right);
		//we will then recursively check if the left and right sides are balanced,
		//as well as if the difference between the heights remain to be less than
		//or equal to 1, then it will return true
		if (abs(ls - rs) <= 1 && isBalanced(r->left) && isBalanced(r->right)) {
			return true;
		}
	}
	return false;
}

//this method will check if the binary search tree is complete
bool BSTree::isComplete(BSTree* r, int i, int nodes)
{
	//an empty tree is complete, so it will return true
	if (r == NULL) {
		return true;
	}
	//if the given index is greater than or equal to the amount of nodes
	//in the tree, then it will return false
	if (i >= nodes) {
		return false;
	}
	//this method will recurse for both left and right subtrees
	return (isComplete(r->left, (2 * i) + 1, nodes) && isComplete(r->right, (2 * i) + 2, nodes));
}

//this method will return the output and records of the binary tree from the given name
//of a file
void BSTree::records(const string& fileName)
{
	ifstream in;
	string line;
	in.open(fileName);
	
	//if the file was able to open, it will run through to examine all the
	//values from each line of the file
	if (in.is_open()) {
		BSTree f, * root = NULL;
		cout << "values in tree: ";
		int i;
		in >> i;
		cout << i << " ";
		root = f.add(root, i);
		while (getline(in, line)) {
			int n;
			in >> n;
			cout << n << " ";
			//while we get each line, we will be filling up the binary search tree
			//with the insert method
			f.add(root, n);
		}
		cout << "\n";
		cout << "smallest branch height: ";
		//to find the smallest branch, we need to compare to find if the left height
		//is less than the height of the right and return the result of whichever height was smaller
		if (f.findHeight(root->left) < f.findHeight(root->right)) {
			cout << f.findHeight(root->left) << "\n";
		}
		else {
			cout << f.findHeight(root->right) << "\n";
		}
		//to find the highest branch, we need to compare to find if the left height
		//is greater than the height of the right and return the result of whichever height was higher
		cout << "highest branch height: ";
		if (f.findHeight(root->left) > f.findHeight(root->right)) {
			cout << f.findHeight(root->left) << "\n";
		}
		else {
			cout << f.findHeight(root->right) << "\n";
		}

		//the n variable will be our starting point of 0 before calculating the number of
		//nodes in the tree
		int n = 0;
		//after we run the nodeAmt method, it will then calculate the node amount and assign
		//the number to n
		f.nodeAmt(root, n);
		cout << "number of nodes in tree: " << n << "\n";
		//this will print out to check if the binary search tree is balanced
		cout << "is tree balanced: " << f.isBalanced(root) << "\n";
		//this will print out to check if the binary search tree is complete
		cout << "is tree complete: " << f.isComplete(root, 0, n) << "\n";
	}
	//if the file was not found, it will give that statement
	else
	{
		cout << "cannot find file";
	}
}


//the main method will run all the tests from the files given
int main() {
	string f1 = "f1.txt";
	BSTree firstTest;
	firstTest.records(f1);

	cout << "-----------------------------\n";

	string f2 = "f2.txt";
	BSTree secondTest;
	secondTest.records(f2);

	cout << "-----------------------------\n";

	string f3 = "f3.txt";
	BSTree thirdTest;
	thirdTest.records(f3);
}
