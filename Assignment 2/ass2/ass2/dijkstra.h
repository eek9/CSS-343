#pragma once
#include <iostream>
#include <utility>
#include <list>
#include <vector>
#include <set>

using namespace std;
//this INF value is a placement for a distance between two airports
//that have not been visited yet with a defined length 
# define INF 123456789

// an integer pair
typedef pair<int, int> p;


class dijkstra
{
    //int value of vertices
    int V;    
    // vertex and weight pair
    list< pair<int, int> >* adj;

public:
    //constructor
    dijkstra(int v);

    //function for adding an edge between two vertices with an input of
    //how far distance is between
    void addEdge(int v1, int v2, int dist);

    //finds and prints the shortest path between two airports
    void shortestPath(int depart, int dest);
};