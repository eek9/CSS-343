#pragma once
#include <fstream>
#include <string>
//
//Created by Eunhee Kim on 04/20/2020
//
using namespace std;

class BSTree {
public:
	BSTree();
	BSTree(int i);
	BSTree* add(BSTree* r, int node);
	int findHeight(BSTree* r);
	void nodeAmt(BSTree* r, int& n);
	bool isBalanced(BSTree* r);
	bool isComplete(BSTree *r, int i, int nodes);
	void records(const string& fileName);
	int data;
	BSTree *left;
	BSTree *right;

};