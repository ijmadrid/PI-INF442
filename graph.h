#ifndef GRAPH_H
#define GRAPH_H
#include <list>

using namespace std;

class Graph{
	public:
		int n;	// nb de noeuds
		list<int> *adj;  // liste d'adjacence (plus performante qu'avec une matrice d'adj.)
		list<int> *scc;  // liste de Strongly Connected Components
}

// constructor : graphe vide de taille nb_noeuds
Graph::Graph(int)

// constructor : build graph from a text file
Graph::Graph(const char *);

// add the edge i -> j
void Graph::addEdge(int, int);

// Kosajaru's algorithm
void Graph::kosajaru();


#endif
