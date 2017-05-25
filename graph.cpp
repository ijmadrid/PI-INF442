#include "graph.h"
#include <fstream>
#include <limits>
#include <cstdlib>


Graph::Graph(int nb_noeuds){
	n = nb_noeuds;
	adj = new list<int>[nb_noeuds];
	scc = new list<int>;
}

Graph::Graph(const char *filename){
	ifstream file(filename);
	int nb_noeuds;
	int edges;
	file >> nb_noeuds >> edges;
	n = nb_noeuds;
	int i;
	int j;
	while (file >> i >> j) {
		addEdge(i,j);
	}
}

void addEdge(int i, int j){
	adj[i].push_back(j);
}

void kosajaru(){
}

Graph er_graph(int nb_noeuds, double p){
	Graph g(nb_noeuds);
	double u;
	for(int i = 0; i < nb_noeuds; i++){
	for(int j = 0; j < nb_noeuds; j++){
		u = rand()/(double)RAND_MAX;
		if(u < p){
			g.addEdge(i,j);
		}
	}}
	return g;
}


