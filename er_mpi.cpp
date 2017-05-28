#include "graph.h"
#include <math.h>
#include <iostream>
#include <stdlib.h>
#include <mpi.h>

using namespace std;

int main(int argc, char **argv){

	const int root = 0;

	int numtasks, taskid;
	MPI_Status status;
	MPI_Request request;

	MPI_Init(&argc, &argv);
	MPI_Comm_rank(MPI_COMM_WORLD, &taskid);
	MPI_Comm_size(MPI_COMM_WORLD, &numtasks);

	if (argc != 3) {
		std::cerr << "Usage : " << argv[0]
			<< " nb_noeuds probability"
			<< std::endl;
		return 1;
	}

	const int nb_noeuds = atoi(argv[1]);
	const double proba  = atof(argv[2]);

	if (proba > 1 or proba < 0){
		if (taskid == root) {
			cerr << "Argument must be a double between 0 and 1" << std::endl;
		} else {
			// print nothing, fail quietly
		}
		MPI_Finalize();
		return 1;
	}

	Graph g(nb_noeuds); 

	// asignation of rows of the adjacency matrix to each process
	int rep = nb_noeuds%numtasks;
	int debut;
	int fin;
	if(taskid < rep){
		debut = taskid*(nb_noeuds/numtasks+1);
		fin = debut+nb_noeuds/numtasks+1;}
	else{
		debut = rep*(nb_noeuds/numtasks+1)+(taskid-rep)*(nb_noeuds/numtasks);
		fin = debut + nb_noeuds/numtasks;}

	double u;
	for(int i = debut; i < fin; i++){
	for(int j = 0; j < nb_noeuds; j++){
		u = rand()/(double)RAND_MAX;
		if(u < proba){
			g.addEdge(i,j);
		}
	}}

	// TODO: Faire Gather plutôt...

	/* MPI_Barrier(MPI_COMM_WORLD);

	if(taskid == root){
	for(map<int, list<int> >::iterator it = g.adj.begin(); it!= g.adj.end(); it++){
		cout << "Noeud " << it->first << " : connected to { ";
		for(list<int>::iterator jt = it->second.begin(); jt != it->second.end(); jt++){
			cout << (*jt) << " ";}
		cout << "} " << endl;
	}
	} */

	MPI_Finalize();

	return 1;

}

