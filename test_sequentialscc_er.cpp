#include "graph.h"
#include <math.h>
#include <iostream>
#include <stdlib.h>

using namespace std;

int main() {

    // create the graph (ex. from wikipedia)
	// https://en.wikipedia.org/wiki/Strongly_connected_component#/media/File:Scc.png


    cout << " Test with graphs of 20 nodes " << endl;
    cout << " ----------------------------- " << endl;
    Graph g0(0);
    for(double i = 1.0; i < 10.0; i+=0.5){
	double p = i/20.0;
	cout << " Edge probability : p = " << p << endl;
	Graph g = g0.er_graph(20, p);
	cout << "Strongly connected components : " << endl;
	g.scc_kosajaru();
	g.printscc();
	cout << " ----------------------------- " << endl;
   }
 

    return 0;

}
