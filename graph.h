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
//		list<int> *adj;  // liste d'adjacence 
		map<int, list<int> > adj;  // liste d'adjacence comme map
		map<int, list<int> > adj_in;  // liste de voisins precedents
		list<list<int> > *scc;  // liste de Strongly Connected Components

		// constructor : graphe vide de taille nb_noeuds
		Graph(int);

		// constructor : build graph from a text file
		Graph(const char *);

		// constructor : build graph from an adjacency matrix of given size
		Graph(int**, int);

		// destructor
		~Graph() {};

		// add the edge i -> j
		void addEdge(int, int);

		// get successors
		list<int> successors(int);

		// Parcours en profondeur (DFS)
		void dfs(int, map<int, bool >&, list<int>&);
		//void dfs(int);

		// Kosajaru's algorithm
		void scc_kosajaru();

		// Print SCC
		void printscc();

		// ER Graph
		Graph er_graph(int, double);

		// MPI ER Graph
		int parallel_er(int, double);

		// Parallel SCC detection
		void dcsc(int, list<list<int> >&);

		// Obtain the sets Succ and Pred of a given node:
		list<int> succ(int);
		list<int> pred(int);

		// Subgraph
		Graph subgraph(list<int>);

		// Get pivot for the parallel SCC search
		int pivot(list<int>);
		
};

#endif
