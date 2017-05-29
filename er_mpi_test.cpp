#include "graph.h"
#include <math.h>
#include <iostream>
#include <stdlib.h>
#include <mpi.h>

int main(int argc, char **argv){

	MPI_Init(&argc, &argv);
	int rank;
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);


	if (argc != 3) {
		std::cerr << "Usage : " << argv[0]
			<< " nb_noeuds probability"
			<< std::endl;
		return 1;
	}

	const int nb_noeuds = atoi(argv[1]);
	const double proba  = atof(argv[2]);

	Graph g(nb_noeuds);
	int z = g.parallel_er(nb_noeuds, proba);

	MPI_Finalize();

	return 0;

}

