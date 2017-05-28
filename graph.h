#ifndef GRAPH_H
#define GRAPH_H
#include <list>
#include <map>
#include <set>
#include <stack>

using namespace std;

class Graph{
	public:
		int n;	// nb de noeuds
		// list<int> *adj;  // liste d'adjacence (plus performante qu'avec une matrice d'adj.)
		map<int, list<int> > adj;
		list<stack<int> > *scc;  // liste de Strongly Connected Components

		// constructor : graphe vide de taille nb_noeuds
		Graph(int);

		// constructor : build graph from a text file
		Graph(const char *);

		// destructor
		~Graph() {};

		// add the edge i -> j
		void addEdge(int, int);

		// get successors
		list<int> successors(int);

		// Parcours en profondeur (DFS)
		void dfs(int, bool*, stack<int>&);
		//void dfs(int);

		// Kosajaru's algorithm
		void scc_kosajaru();

		// Print SCC
		void printscc();

		// ER Graph
		Graph er_graph(int, double);
};

#endif
