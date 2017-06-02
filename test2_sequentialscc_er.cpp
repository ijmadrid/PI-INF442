#include "graph.h"
#include <math.h>
#include <iostream>
#include <stdlib.h>

using namespace std;

int main() {

    // create the graph (ex. from wikipedia)
	// https://en.wikipedia.org/wiki/Strongly_connected_component#/media/File:Scc.png

    int nodes = 20;  // how many nodes
    int N = 100;        // how many simulations

    cout << " Test with graphs of " << nodes << " nodes " << endl;
    cout << " (" << N << " ER graphes created for each probability tested)  " << endl;
    cout << " ----------------------------- " << endl;
    Graph g0(0);
    for(double i = 0.05; i < double(nodes/2); i+=0.2){
	double p = i/double(nodes);
	cout << " Edge probability : p = " << p << endl;
        int total = 0;
	for(int i = 0; i < N; i++){
	Graph g = g0.er_graph(nodes, p);
	g.scc_kosajaru();
	total += g.scc->size();
	}
        cout << "       " << double(total)/double(N) << " SCC found on average." << endl;
	cout << " -------------------------------------------- " << endl;
   }
 

    return 0;

}
