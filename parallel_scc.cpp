#include "graph.h"
#include <math.h>
#include <iostream>
#include <stdlib.h>
#include <algorithm>
//#include <mpi.h>

using namespace std;

list<int> Graph::succ(int v){

	// Parcours en profondeur:
	list<int> reachable_vertices; 
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

int Graph::pivot(list<int> nodes_set){
	// Le pivot est juste le premier element du set (à amelliorer)
	if(nodes_set.empty()){return 0;}
	else{return nodes_set.back();}
}

/*void Graph::topologicalSort(){
	stack<int> Q;
	list<int> T;
	for(map<int, list<int> >::iterator it = adj_in.begin(); it!= adj_in.end(); it++){
		if ((it->second).empty()){
			Q.push(it->first);}
	}
	while(!Q.empty()){
		int v = Q.top();
		Q.pop();	
		T.push_back(v);
			
	}	
}*/


void Graph::dcsc(int v, list<list<int> > &localscc){
	cout << "Pivot is " << v << endl;
	// SEQUENTIAL (just for test)
	if (adj.empty()){ cout << "adj is empty " << endl; return;}

	// Obtain predecesors and sucessor
	list<int> pred = this->pred(v);
	list<int> succ = this->succ(v);
	
	pred.sort();
	succ.sort();

	list<int> s1;
	list<int> s2;
	list<int> s3;
	list<int> s4;

	set_intersection(pred.begin(),pred.end(),succ.begin(),succ.end(),inserter(s1,s1.begin()));
	set_difference(pred.begin(),pred.end(),succ.begin(),succ.end(),inserter(s2,s2.begin()));
	set_difference(succ.begin(),succ.end(),pred.begin(),pred.end(),inserter(s3,s3.begin()));
	
	for(map<int, list<int> >::iterator it = adj.begin(); it!= adj.end(); it++){
		s4.push_back(it->first);
	}
	
	for(list<int>::iterator it = pred.begin(); it!= pred.end(); it++){
		s4.remove(*it);
	}

	for(list<int>::iterator it = succ.begin(); it!= succ.end(); it++){
		s4.remove(*it);
	}

	localscc.push_back(s1);  // s1 is a scc
	cout << " SCC found and added " << endl;
	cout << " Verified : scc.size() = " << localscc.size() << endl;

	cout << " S1 = { ";
	for(list<int>::iterator it = s1.begin(); it!= s1.end(); it++){
		cout << *it << " ";
	}
	cout << " } " << endl;

	cout << " S2 = { ";
	for(list<int>::iterator it = s2.begin(); it!= s2.end(); it++){
		cout << *it << " ";
	}
	cout << " } " << endl;

	cout << " S3 = { ";
	for(list<int>::iterator it = s3.begin(); it!= s3.end(); it++){
		cout << *it << " ";
	}
	cout << " } " << endl;

	cout << " S4 = { ";
	for(list<int>::iterator it = s4.begin(); it!= s4.end(); it++){
		cout << *it << " ";
	}
	cout << " } " << endl;

	// recursion (partie à paralleliser après):
	// TODO: completer subgraph in graph.cpp ; completer un methode pour choisir pivot
	cout << " RECURSION WITH S2 " << endl;
	subgraph(s2).dcsc(pivot(s2),localscc);
	cout << " RECURSION WITH S3 " << endl;
	subgraph(s3).dcsc(pivot(s3),localscc);
	cout << " RECURSION WITH S4 " << endl;
	subgraph(s4).dcsc(pivot(s4),localscc);



	return;
}

void parallel_dcsc(int v, list<list<int> > &localscc){
	// SEQUENTIAL (just for test)
	if (adj.empty()){return;}

	// Obtain predecesors and sucessor
	list<int> pred = this->pred(v);
	list<int> succ = this->succ(v);
	
	pred.sort();
	succ.sort();

	list<int> s1;
	list<int> s2;
	list<int> s3;
	list<int> s4;

	set_intersection(pred.begin(),pred.end(),succ.begin(),succ.end(),inserter(s1,s1.begin()));
	set_difference(pred.begin(),pred.end(),succ.begin(),succ.end(),inserter(s2,s2.begin()));
	set_difference(succ.begin(),succ.end(),pred.begin(),pred.end(),inserter(s3,s3.begin()));
	
	for(map<int, list<int> >::iterator it = adj.begin(); it!= adj.end(); it++){
		s4.push_back(it->first);
	}
	for(list<int>::iterator it = pred.begin(); it!= pred.end(); it++){
		s4.remove(*it);
	}
	for(list<int>::iterator it = succ.begin(); it!= succ.end(); it++){
		s4.remove(*it);
	}

	localscc.push_back(s1);  // s1 is a scc
	cout << " SCC found and added " << endl;
	cout << " Verified : scc.size() = " << localscc.size() << endl;

	cout << " S1 = { ";
	for(list<int>::iterator it = s1.begin(); it!= s1.end(); it++){
		cout << *it << " ";
	}
	cout << " } " << endl;

	cout << " S2 = { ";
	for(list<int>::iterator it = s2.begin(); it!= s2.end(); it++){
		cout << *it << " ";
	}
	cout << " } " << endl;

	cout << " S3 = { ";
	for(list<int>::iterator it = s3.begin(); it!= s3.end(); it++){
		cout << *it << " ";
	}
	cout << " } " << endl;

	cout << " S4 = { ";
	for(list<int>::iterator it = s4.begin(); it!= s4.end(); it++){
		cout << *it << " ";
	}
	cout << " } " << endl;

	// recursion (partie à paralleliser après):
	// TODO: completer subgraph in graph.cpp ; completer un methode pour choisir pivot
	cout << " RECURSION WITH S2 " << endl;
	subgraph(s2).dcsc(pivot(s2),localscc);
	cout << " RECURSION WITH S3 " << endl;
	subgraph(s3).dcsc(pivot(s3),localscc);
	cout << " RECURSION WITH S4 " << endl;
	subgraph(s4).dcsc(pivot(s4),localscc);
}

/*void Graph::parallel_scc(int v){

	const int root = 0;
	int rank, size;
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Comm_size(MPI_COMM_WORLD, &size);
	MPI_Status status;

	stack<int> pred(v);
	stack<int> succ(v);

	stack<int> s1 = pred inter succ

	scc->push_back(s1);  // s1 est scc

	stack<int> s2 = pred - succ;
	stack<int> s3 = succ - pred;
	stack<int> s4 = reste;

	

}*/
