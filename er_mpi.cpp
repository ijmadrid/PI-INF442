#include "graph.h"
#include <math.h>
#include <iostream>
#include <stdlib.h>
#include <mpi.h>

using namespace std;

int Graph::parallel_er(int nb_noeuds, double proba){

	const int root = 0;
	int numtasks, taskid;
	MPI_Comm_rank(MPI_COMM_WORLD, &taskid);
	MPI_Comm_size(MPI_COMM_WORLD, &numtasks);
	MPI_Status status;

	if (proba > 1 or proba < 0){
		if (taskid == root) {
			cerr << "Argument must be a double between 0 and 1" << std::endl;
		} else {
			// print nothing, fail quietly
		}
		MPI_Finalize();
		return 1;
	}

    // Each of the processors generate edges for floor(n/p) or ceil(n/p) rows of this matrix.
    // The zero adjacency matrix is replicated on each processor. 

	int** A = new int*[nb_noeuds]; 	//Matrice d'adjacence
	for(int i = 0; i < nb_noeuds; ++i)
    	A[i] = new int[nb_noeuds];

	for (unsigned int i = 0; i < nb_noeuds; ++i) {
	for (unsigned int j = 0; j < nb_noeuds; ++j)
		A[i][j] = 0;
	}

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

	// edges generation
	double u;
	for(int i = debut; i < fin; i++){
	for(int j = 0; j < nb_noeuds; j++){
		u = rand()/(double)RAND_MAX;
		if(u < proba){
			A[i][j] = 1;			
		}
	}}

	// each non-root process send its rows to the root
	if (taskid != root){
		MPI_Send(A, nb_noeuds*nb_noeuds, MPI_INT, 0, 1, MPI_COMM_WORLD);}


	// the root assembles the adjacency matrix  (naive, il y a une façon plus performante pour ce faire, certainement)
	else{
		for (int p = 1; p < numtasks; p++){

			int** Atemp = new int*[nb_noeuds]; 	
			for(int i = 0; i < nb_noeuds; ++i){
				Atemp[i] = new int[nb_noeuds];}

			MPI_Recv(Atemp, nb_noeuds*nb_noeuds, MPI_INT, p, 1, MPI_COMM_WORLD, &status);
			for (unsigned int i = 0; i < nb_noeuds; ++i){
			for (unsigned int j = 0; j < nb_noeuds; ++j){
				A[i][j] += Atemp[i][j];}}

			delete [] Atemp;
		}

		// Graph generation
		
		Graph g(A,nb_noeuds);

		delete [] A;

		for(map<int, list<int> >::iterator it = g.adj.begin(); it!= g.adj.end(); it++){
			cout << "Noeud " << it->first << " : connected to { ";
			for(list<int>::iterator jt = it->second.begin(); jt != it->second.end(); jt++){
				cout << (*jt) << " ";
			}
			cout << "} " << endl;
		}

		return 1;
		}

	
}

