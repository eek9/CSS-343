#include <iostream>
#include <list>
#pragma once

using namespace std;

class hashing {
private:
	//variable of how many buckets/size of the array
	int bucket;
	//using a linked list that will keep the keys in the hash table
	list<int>* table;
	//variable of minimum collisions
	int min;
	//variable of maximum collisions
	int max;

public:
	//constructor
	hashing(int size);
	//getter for size of array/amount of buckets
	int getSize();
	//inserting a new key in array
	void insert(int key);
	//printing records
	void print();
	//calculating the max and min collisions
	void maxMinCollisions();
	//calculating the amount of empty arrays
	void emptyArrays();
};