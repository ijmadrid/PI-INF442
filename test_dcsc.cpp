#include "graph.h"
#include <math.h>
#include <iostream>
#include <stdlib.h>

using namespace std;

int main() {

    // create the graph (ex. from wikipedia)
	// https://en.wikipedia.org/wiki/Strongly_connected_component#/media/File:Scc.png

    Graph g(8);
    g.addEdge(0, 1);
    g.addEdge(1, 2);
	g.addEdge(1, 4);
	g.addEdge(1, 5);
	g.addEdge(2, 3);
	g.addEdge(2, 6);
	g.addEdge(3, 2);
	g.addEdge(3, 7);
	g.addEdge(4, 0);
	g.addEdge(4, 5);
	g.addEdge(5, 6);
	g.addEdge(6, 5);
	g.addEdge(7, 6);
	g.addEdge(7, 3);

    int v = 3;
    cout << " Pivot choisi : 3 " << endl; 
    list<list<int> > *localscc = new list<list<int> >;
    g.dcsc(v, *localscc);
    cout << (*localscc).size() << endl;
    g.scc = localscc;
    cout << "Strongly connected components : " << endl;
    g.printscc();
 

    return 0;

}
