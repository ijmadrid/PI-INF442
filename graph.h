#ifndef GRAPH_H
#define GRAPH_H
#include <vector>
#include <set>

using namespace std;

typedef vector<Vertex> Vertices;
typedef set<int> Neighbours;

struct Vertex{
	public:
		int label;
		Neighbours links_to;
}

class Graph{
	public:
		Vertices vertices;
}

// get vertex i
void Graph::getVertex(int i);

// add the edge i -> j
void Graph::addEdge(int i, int j);

// reads in a graph from a text file
Graph readGraph(const char *);


#endif
