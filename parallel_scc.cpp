#include "graph.h"
#include <math.h>
#include <iostream>
#include <stdlib.h>
#include <mpi.h>

using namespace std;

stack<int> Graph::succ(int v){

	// Parcours en profondeur:
	stack<int> reachable_vertices; 
	map<int, bool > visited;

	for(map<int, list<int> >::iterator it = adj.begin(); it!= adj.end(); it++){ 
	    visited[it->first] = false; }

	dfs(v, visited, reachable_vertices);

	return reachable_vertices;
}

list<int> Graph::pred(int v){

	// DFS du graphe inverse
	
	Graph g_inverse(n);
	for(map<int, list<int> >::iterator it = adj.begin(); it!= adj.end(); it++){
		int i = it->first;
		list<int>::iterator j;
		for(j = adj[i].begin(); j != adj[i].end(); ++j){
		    g_inverse.adj[*j].push_back(i);}}

	return g_inverse.succ(v);

}

void Graph::parallel_scc(){

}
