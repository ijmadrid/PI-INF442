#include "graph.h"
#include <math.h>
#include <iostream>
#include <stdlib.h>

using namespace std;

int main(int argc, char **argv) {

    // Trouve les SCC pour le graphe donné en input

	if (argc != 2) {
		std::cerr << "Usage : " << argv[0]
			<< " graphfile(.txt)"
			<< std::endl;
		return 1;
	}

	// Load graph
	Graph g(argv[1]);
 	cout << "graph building passed succesfully" << endl;

    cout << "Strongly connected components : " << endl;
    g.scc_kosajaru();
    g.printscc();
 

    return 0;

}
