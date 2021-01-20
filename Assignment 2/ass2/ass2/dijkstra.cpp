#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <map>
#include <queue>
#include <algorithm>
#include "dijkstra.h"

using namespace std;

//constructor that takes in an int value and initializes the amount of vertices
//and pairs
dijkstra::dijkstra(int v) : V{v}, adj{new list<p>[v]}{}

//this function will take in int values of the points and the distance between
void dijkstra::addEdge(int v1, int v2, int dist)
{
    //this will direct the two points to be adjacent to one another
    //and push back the pairs of making the distances between them
    adj[v1].push_back(make_pair(v2, dist));
    adj[v2].push_back(make_pair(v1, dist));
}

//this function will calculate and print the shortest distance between the 
//departing airport and the destination airport
void dijkstra::shortestPath(int depart, int dest)
{
    //a priority queue to keep track of the vertices
    priority_queue< p, vector <p>, greater<p> > q;

    //a vector for distances and initializing all unvisited distances to INF
    vector<int> dis(V, INF);
 
    //pushing the departing airport into the priority queue and initilizing
    //the distance to itself as 0
    q.push(make_pair(0, depart));
    dis[depart] = 0;

    //while the priority queue is not empty, or until it becomes empty
    while (!q.empty())
    {
        //the priority queue will be popped after labeling vertex into
        //an int second pair
        int u = q.top().second;
        q.pop();

        //using an iterator to find the adjacent vertices
        list< pair<int, int> >::iterator i;
        //for loop to go through the adjacent points
        for (i = adj[u].begin(); i != adj[u].end(); ++i)
        {
            //storing the label of the vertex and weight of the
            //current adjacent of u
            int v = (*i).first;
            int weight = (*i).second;

            //if a shorter path from v to u is found
            if (dis[v] > dis[u] + weight)
            {
                //will update the distance of v
                dis[v] = dis[u] + weight;
                //pushing the new shorter length into the priority queue
                q.push(make_pair(dis[v], v));
            }
        }
    }

    //an array to keep track of the airports available in the file
    const char* airports[26] = { "OLM", "BOI", "HLN", "EKO", "SAF",
                                "LAS", "SLC", "BIS", "DEN", "FOE",
                                "LIT", "BTR", "AUS", "TLH", "CVG",
                                "RDU", "LCK", "PIT", "LAN", "STL",
                                "DSM", "OKC", "XMD", "LNK", "AUM",
                                "PIR" };

    //printing the shortest distance between the two airports that were requested
    //from the parameter inputs
    printf("shortest distance between the two airports:\n");
    printf("%d\n", dis[dest]);
}

int main() {
    //int value of how many vertices are available
    int V = 26;
    //initializing the amount of vertices into the constructor
    dijkstra g(V);
    //array that keeps track of airports
    const string airports[26] = { "OLM", "BOI", "HLN", "EKO", "SAF",
                                "LAS", "SLC", "BIS", "DEN", "FOE",
                                "LIT", "BTR", "AUS", "TLH", "CVG",
                                "RDU", "LCK", "PIT", "LAN", "STL",
                                "DSM", "OKC", "XMD", "LNK", "AUM",
                                "PIR" };
    //opening the file
    ifstream file("AirportDistances.csv");
    //if the file is found
    if (file.is_open()) {
        string line;
        //while getting the next line
        while (getline(file, line)) {
            stringstream ss(line);
            
            string d;
            string a;
            string dis;
            //identify and direct the departing, arriving, and distance values from the file
            //into the variables
            getline(ss, d, ',');
            getline(ss, a, ',');
            getline(ss, dis, ',');
            //convert the string of distance into an int
            int distance = stoi(dis);
            int dd = 0;
            int aa = 0;
            //finding the index of where the string comes from in the array
            //to label as an int(making it able to be used as an input to a function)
            for (int i = 0; i < 27; i++) {
                if (airports[i] == d) {
                    dd = i;
                }
            }
            for (int i = 0; i < 27; i++) {
                if (airports[i] == a) {
                    aa = i;
                }
            }
            //adding an edge by inputing the designated array numbers based on the matching
            //airport code, and the distance between the two
            g.addEdge(dd, aa, distance);
        }
    }
    else {
        cout << "file not found" << endl;
    }
    string d;
    string de;
    //asking the user which airport to depart from
    cout << "where would you like to depart from?" << endl;
    cin >> d;
    //asking the user which airport to arrive at
    cout << "where is your destination?" << endl;
    cin >> de;
    int departure = 0;
    int destination = 0;
    //finding the array index based on the input given from user
    for (int i = 0; i < 27; i++) {
        if (airports[i] == d) {
            departure = i;
        }
    }
    for (int i = 0; i < 27; i++) {
        if (airports[i] == de) {
            destination = i;
        }
    }
    //calculate the shortest path that was requested
	g.shortestPath(departure, destination);

	return 0;
}