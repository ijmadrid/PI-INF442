#include "graph.h"
#include <fstream>
#include <iostream>
#include <limits>
#include <cstdlib>
#include <iterator>

Graph::Graph(int nb_noeuds){
	n = nb_noeuds;
//	adj = new list<int>[nb_noeuds];
	adj = * new map<int, list<int> >;
	scc = new list<stack<int> >;
}

Graph::Graph(const char *filename){
	ifstream file(filename);
	int nb_noeuds;
	int edges;
	file >> nb_noeuds >> edges;
	cout << "Graph loaded : " << nb_noeuds << " nodes and " << edges << " edges." << endl;
	n = nb_noeuds;
//	adj = new list<int>[nb_noeuds];
	adj = * new map<int, list<int> >;
	scc = new list<stack<int> >;
	int i;
	int j;
	while (file >> i >> j) {
		addEdge(i,j);
	}
	cout << "All edges charged succesfully." << endl;
}


Graph::Graph(int  **A, int nb_noeuds){
	n = nb_noeuds;
	adj = * new map<int, list<int> >;
	scc = new list<stack<int> >;
	for (unsigned int i = 0; i < n; ++i){
	for (unsigned int j = 0; j < n; ++j){	
		if(A[i][j] == 1){
			addEdge(i,j);}
	}}
}

list<int> Graph::successors(int v){
	return adj[v];
}

void Graph::addEdge(int i, int j){
	adj[i].push_back(j);
}

void Graph::dfs(int v, map<int, bool > &visited, stack<int> &reachable_vertices){
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
//	bool *visited = new bool[n];
	map<int, bool > visited;
//  for(int i = 0; i < n; i++){
	int contador = 0;
	for(map<int, list<int> >::iterator it = adj.begin(); it!= adj.end(); it++){ 
	    visited[it->first] = false;
		cout << "Pasada numero " << contador++ << " por adj" << endl; }
	cout << "1. Initialisation passed" << endl;
	cout << "Visited a une taille de " << visited.size() << endl;

	// 2. Premier DFS
//  for(int i = 0; i < n; i++){  // TODO: changer a for(int i in keys)
	for(map<int, bool >::iterator it = visited.begin(); it!= visited.end(); it++){
        if(it->second==false){
            dfs(it->first, visited, reachable_vertices);}}
	cout << "2. Premier DFS passed" << endl;
	cout << "Visited a une taille de " << visited.size() << endl;

	for(map<int, bool >::iterator it = visited.begin(); it!= visited.end(); it++){
		cout << "Noeud " << it->first << " : visited = " << it->second << endl;}

	// 3. Inversion de direction des aretes
	Graph g_inverse(n);
    for(map<int, list<int> >::iterator it = adj.begin(); it!= adj.end(); it++){
		int i = it->first;
        list<int>::iterator j;
        for(j = adj[i].begin(); j != adj[i].end(); ++j){
            g_inverse.adj[*j].push_back(i);}}
	cout << "3. Inversion passed" << endl;
	cout << "Visited a une taille de " << visited.size() << endl;


	// 4. Deuxieme DFS
//	for(int i = 0; i < n; i++){
//        visited[i] = false;}  // on reset visited

	for(map<int, list<int> >::iterator it = adj.begin(); it!= adj.end(); it++){ 
	    visited[it->first] = false;}
	cout << "reachable_vertices a une taille de " << reachable_vertices.size() << endl;

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
	cout << "4. Deuxieme DFS passed" << endl;
	cout << "Visited a une taille de " << visited.size() << endl;

	//delete *g_inverse;
	//delete &visited;
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


