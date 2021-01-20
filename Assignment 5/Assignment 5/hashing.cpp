#include <iostream>
#include <fstream>
#include <sstream>
#include <list>
#include "hashing.h"

using namespace std;

//this is the constructor that will initialize the amount of buckets
//in an array
hashing::hashing(int size) : bucket{ size }, table{new list<int>[bucket]} {}

//this function will get the private variable of the number of buckets available
int hashing::getSize()
{
	return bucket;
}

//this function will insert a new key into the table
void hashing::insert(int key) {
	//finding the location of where the key will be inserted within
	//the array
	int index = key % bucket;
	//pushing the key to the back of the list from that indexed array
	//if there are collisions
	table[index].push_back(key);
}

//this function will print all the records of the hash table
void hashing::print() {
	//this nexted for loop will print out all the elements in each array and its
	//collisions
	for (int i = 0; i < bucket; i++) {
		cout << "index" << i;
		//iterator to go through the chain of collided keys in an index
		list<int>::iterator j = table[i].begin();
		for (; j != table[i].end(); j++)
		{
			cout << "->" << *j;
		}
		cout << endl;

	}
	//printing out the size of the array
	cout << "SIZE OF ARRAY: " << getSize() << endl;
	//calling the function that prints out the maximum and minimum amount
	//of collisions
	maxMinCollisions();
	//calling the function that prints out the value counting how many empty
	//arrays are available
	emptyArrays();
	cout << "-------------------------------------------------";
	cout << "-------------------------------------------------" << endl;
}

//this function will calculate the maximum and minimum amount of collisions from
//the amount of buckets
void hashing::maxMinCollisions() {
	//max will be initialized to 0 until a higher count of collisions is found
	int max = 0;
	//for loop to keep track of counting the amount of elements in each bucket
	for (int i = 0; i < bucket; i++) {
		list<int>::iterator j = table[i].begin();
		int count = 0;
		for (; j != table[i].end(); j++) {
			count++;
		}
		//if the prior max value is less than the count, the max is given a new
		//value of that count
		if (max < count) {
			max = count;
		}
	}
	//reducing the number of maximum collisions because the collision counts up
	//after the first element is added into the index
	if (max != 0) {
		max = max - 1;
	}
	//printing out the final maximum count of collisions
	cout << "MAXIMUM COUNT OF COLLISIONS: " << max << endl;

	//initializing the min count of collisions as the max until a lower count of
	//collisions is found
	int min = max;
	//for loop to keep track of counting the amount of elements in each bucket
	for (int i = 0; i < bucket; i++) {
		list<int>::iterator j = table[i].begin();
		int count = 0;
		for (; j != table[i].end(); j++) {
			count++;
		}
		//if the prior min value is greater than the count, the min is assigned a new
		//value of that count
		if (min > count) {
			min = count;
		}
	}
	//reducing the number of minimum collisions because the collision counts up
	//after the first element is added into the index
	if (min != 0) {
		min = min - 1;
	}
	//printing out the final maximum count of collisions
	cout << "MINIMUM COUNT OF COLLISIONS: " << min << endl;
}

//this function will count the number of empty arrays
void hashing::emptyArrays() {
	//using a variable to keep track of the amount of empty arrays
	int empty = 0;
	//for loop that will count up the empty variable whenever an
	//array is found to be empty
	for (int i = 0; i < bucket; i++) {
		if (table[i].empty()) {
			empty++;
		}
	}
	//printing out the number of array elements with no data
	cout << "NUMBER OF ARRAY ELEMENTS WITH NO DATA: " << empty << endl;
}

int main() {
	hashing a(10);
	hashing b(11);
	hashing c(23);
	hashing d(40);

	ifstream file;
	file.open("CSS343_Final_Data.txt");

	if (file.is_open()) {
		string line;
		while (getline(file, line)) {
			int i;
			file >> i;
			a.insert(i);
			b.insert(i);
			c.insert(i);
			d.insert(i);
		}
	}
	a.print();
	b.print();
	c.print();
	d.print();
	file.close();
	return 0;
}
