#include <iostream>
#include <sstream>
#include <fstream>
#include <time.h>
#include <iomanip>
#include <chrono>
#include "tree234.h"

using namespace std;

//constructor to initialize the minimum degree and the leaf
//as well as initializing the keys and children in arrays
//current number of keys also begin as 0
BTreeNode::BTreeNode(int m, bool l)
{
	numOfKeys = 0;
	minDeg = m;
	keys = new int[2 * minDeg - 1];
	children = new BTreeNode * [2 * minDeg];
	leaf = l;
}

//function to go through each node and printing out in order
void BTreeNode::print()
{
	int i;
	//for loop to count up to the number of keys and check
	//if not a leaf, traverse through the children array 
	//before printing the key
	for (i = 0; i < numOfKeys; i++) {
		if (leaf == false) {
			children[i]->print();
		}
		cout << keys[i] << endl;
	}
	//if not a leaf, print subtree rooted with last child
	if (leaf == false) {
		children[i]->print();
	}
}

//function to search the node by inputing the key
BTreeNode* BTreeNode::search(int k)
{
	int i = 0;
	//while loop to go through nodes until end of tree
	while (i < numOfKeys && k > keys[i]) {
		i++;
	}
	//if searching key is equal to a key from the array,
	//will return the node
	if (keys[i] == k) {
		return this;
	}
	//if the leaf is true, return null
	if (leaf == true) {
		return NULL;
	}
	//if none of the above if statements pass through,
	//search the next child
	return children[i]->search(k);
}

//this function will split the child of a node
void BTreeNode::splitChild(int i, BTreeNode* a)
{
	//creating a node that will contain a minDeg-1 keys
	BTreeNode* b = new BTreeNode(a->minDeg, a->leaf);
	b->numOfKeys = minDeg - 1;
	//transferring/copying the last key from a to b
	for (int j = 0; j < minDeg - 1; j++)
		b->keys[j] = a->keys[j + minDeg];
	if (a->leaf == false)
	{
		for (int j = 0; j < minDeg; j++)
			b->children[j] = a->children[j + minDeg];
	}
	//reducing number of keys from a
	a->numOfKeys = minDeg - 1;
	//creating space for new child to be added
	for (int j = numOfKeys; j >= i + 1; j--)
		children[j + 1] = children[j];
	//adding new child into node
	children[i + 1] = b;
	//for loop to go through and add the key from a
	for (int j = numOfKeys - 1; j >= i; j--)
		keys[j + 1] = keys[j];
	//adding middle key from a into node
	keys[i] = a->keys[minDeg - 1];
	// Increment count of keys in this node
	//number of keys need to be updated to match amount from node
	numOfKeys = numOfKeys + 1;
}

//this function is used when a node is not filled up to the
//minimum degree and inserting a key into it to meet that requirement
void BTreeNode::insertnf(int k)
{
	//finding index of rightmost element and declaring into
	//an int
	int i = numOfKeys - 1;
	//if node is a leaf goes into a while loop that will
	//find where to insert new key and shifts the remaining
	//keys up
	if (leaf == true)
	{
		while (i >= 0 && keys[i] > k)
		{
			keys[i + 1] = keys[i];
			i--;
		}
		keys[i + 1] = k;
		numOfKeys = numOfKeys + 1;
	}
	//else, the node is not a leaf
	else {
		//while loop to find the designated area for the new key
		while (i >= 0 && keys[i] > k)
			i--;
		//checking if the child is filled and will split the children
		//array and find which side will have the inserted new key
		if (children[i + 1]->numOfKeys == 2 * minDeg - 1)
		{
			splitChild(i + 1, children[i + 1]);
			if (keys[i + 1] < k)
				i++;
		}
		children[i + 1]->insertnf(k);
	}
}

//constructor to initalize the tree with a root null and minimum degree from input
tree234::tree234(int m)
{
	root = NULL; minDeg = m;
}

//function to run the print function from the root if it is not found null
void tree234::print()
{
	if (root != NULL) { root->print(); }
}

//function to run the search based on the given key and returning the node
BTreeNode* tree234::search(int k)
{
	return (root == NULL) ? NULL : root->search(k); 
}

//insert a key in the 2-3-4 tree
void tree234::insert(int k)
{
	//if the root is null, find the root and insert the key
	//and updating the number of keys in the root
	if (root == NULL)
	{
		root = new BTreeNode(minDeg, true);
		root->keys[0] = k;
		root->numOfKeys = 1;
	}
	//else, if the root is filled, then tree grows in height
	else {
		if (root->numOfKeys == 2 * minDeg - 1)
		{
			//creating a new root and using old root as the child of it
			BTreeNode* n = new BTreeNode(minDeg, false);
			n->children[0] = root;
			//using the splitChild function on the old root to move a key to the new root
			n->splitChild(0, root);
			//new root with two children now needs to find which one
			//will have new key
			int i = 0;
			if (n->keys[0] < k)
				i++;
			n->children[i]->insertnf(k);
			//changing root
			root = n;
		}
		//when root is unfilled, call the insrtnf function to fix it
		else {
			root->insertnf(k);
		}
	}
}

int main()
{
	auto start = chrono::steady_clock::now();

	//initializing the minimum degree of the btree as 2
	//for the requirements of a 2-3-4 tree
	tree234 tree(2);

	ifstream file;
	file.open("B_Tree_Input.txt");
	if (file.is_open()) {
		string line;
		while (getline(file, line)) {
			int i;
			file >> i;
			tree.insert(i);
		}
		file.close();
	}
	else {
		cout << "file not found" << endl;
	}
	tree.print();
	
	ifstream search;
	search.open("B_Tree_Searches.txt");
	auto s = chrono::steady_clock::now();
	int a = 12;
	if (tree.search(a) != NULL) {
		cout << "searching: " << a << endl;
	}
	else {
		cout << "searching: " << a << "not found" << endl;
	}
	auto e = chrono::steady_clock::now();
	cout << "time taken: "
		<< chrono::duration_cast<chrono::nanoseconds>(e - s).count();
	cout << " nanoseconds" << endl;
	if (search.is_open()) {
		string line;
		while (getline(search, line)) {
			auto Sstart = chrono::steady_clock::now();
			int i;
			search >> i;
			if (tree.search(i) != NULL) {
				cout << "searching: " << i << endl;
			}
			else {
				cout << "searching: " << i << " not found" << endl;
			}
			auto endS = chrono::steady_clock::now();
			cout << "time taken: "
				<< chrono::duration_cast<chrono::nanoseconds>(endS - Sstart).count();
			cout << " nanoseconds" << endl;
		}
	}
	else {
		cout << "file not found" << endl;
	}
	search.close();

	auto end = chrono::steady_clock::now();
	cout << "time taken for the whole process to finish: "
		<< chrono::duration_cast<chrono::nanoseconds>(end - start).count();
	cout << " nanoseconds" << endl;
	return 0;

}