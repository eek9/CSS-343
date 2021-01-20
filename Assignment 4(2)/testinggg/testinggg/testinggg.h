#include<iostream>

#pragma once

using namespace std;

class BTreeNode

{

	int* keys; // An array of keys

	int t; // Minimum degree (defines the range for number of keys)

	BTreeNode** C; // An array of child pointers

	int n; // Current number of keys

	bool leaf; // Is true when node is leaf. Otherwise false

public:

	BTreeNode(int t, bool leaf); // Constructor

	void insertNonFull(int k);

	void splitChild(int i, BTreeNode* y);

	void traverse();

	BTreeNode* search(int k); // returns NULL if k is not present.

	friend class BTree;

};
// A BTree

class BTree

{

	BTreeNode* root; // Pointer to root node

	int t; // Minimum degree

public:

	BTree(int _t)

	{
		root = NULL; t = _t;
	}

	void traverse()

	{
		if (root != NULL) root->traverse();
	}

	BTreeNode* search(int k)

	{
		return (root == NULL) ? NULL : root->search(k);
	}

	void insert(int k);

};