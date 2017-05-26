#include "graph.h"
#include <fstream>
#include <iostream>
#include <limits>
#include <cstdlib>
#include <iterator>

Graph::Graph(int nb_noeuds){
	n = nb_noeuds;
	adj = new list<int>[nb_noeuds];
	scc = new list<stack<int> >;
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

list<int> Graph::successors(int v){
	return adj[v];
}

void Graph::addEdge(int i, int j){
	adj[i].push_back(j);
}

void Graph::dfs(int v, bool visited[], stack<int> &reachable_vertices){
	visited[v] = true;
	list<int>::iterator i;
	for (i = adj[v].begin(); i != adj[v].end(); ++i)
		if (!visited[*i])
			dfs(*i, visited, reachable_vertices);
	reachable_vertices.push(v);
}

/* void Graph::dfs(int v){
    bool *visited = new bool[n];
    for (unsigned int i = 0; i < n; i++)
        visited[i] = false;
    dfs(v, visited);
}*/

void Graph::scc_kosajaru(){

	// 1. Initialisation
	stack<int> reachable_vertices; // last visited, first out
	bool *visited = new bool[n];
    for(int i = 0; i < n; i++)
	    visited[i] = false;
	//cout << "pass 1" << endl;

	// 2. Premier DFS
    for(int i = 0; i < n; i++){
        if(!visited[i]){
            dfs(i, visited, reachable_vertices);}} 
	//cout << "pass 2" << endl;

	// 3. Inversion de direction des aretes
	Graph g_inverse(n);
    for (int i = 0; i < n; i++){
        list<int>::iterator j;
        for(j = adj[i].begin(); j != adj[i].end(); ++j){
            g_inverse.adj[*j].push_back(i);}}
	//cout << "pass 3" << endl;

	// 4. Deuxieme DFS
	for(int i = 0; i < n; i++){
        visited[i] = false;}  // on reset visited

	while (!reachable_vertices.empty()){
        // Last visited, first out
        int v = reachable_vertices.top();
        reachable_vertices.pop();
 
        // Obtention des SCC
        if (!visited[v]){
			stack<int> scc_of_v;
            g_inverse.dfs(v, visited, scc_of_v);
            scc->push_back(scc_of_v);
        }
    }
	//cout << "pass 4" << endl;

	//delete *g_inverse;
	delete visited;
}

void Graph::printscc(){
	list<stack<int> > tempscc = (*scc);
	list<stack<int> >:: iterator i;
	int counter = 1;
	for(i = tempscc.begin(); i != tempscc.end(); i++){
		cout << " Component #" << counter << " : { ";
		while(!(*i).empty()){
			cout << (*i).top() << " ";
			(*i).pop();}
		cout << "}" << endl;
		counter++;
	}
	//delete tempscc;
}


Graph Graph::er_graph(int nb_noeuds, double p){
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


