#include<iostream>

#pragma once

using namespace std;

struct BTreeNode {
private:
	//minimum degree of a btree node
	int minDeg;
	//key of arrays in node
	int* keys;
	//number of keys
	int numOfKeys;
	//children pointer arrays of node
	BTreeNode** children;
	//leaf is true when node is a leaf
	bool leaf;

public:
	BTreeNode(int m, bool l);
	void insertnf(int k);
	void print();
	BTreeNode* search(int k);
	void splitChild(int i, BTreeNode* a);
	friend class tree234;
};

class tree234
{
private:
	//root node pointer
	BTreeNode* root;
	int minDeg;

public:
	tree234(int m);
	BTreeNode* search(int k);
	void insert(int k);
	void print();
};