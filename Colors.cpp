#include <iostream>
using namespace std;


class Graph {

private:

	int n;	// Number of vertices
	int **adj;	// Adjacency matrix


public:

	Graph();
	Graph(int size);	// Constructor
	~Graph();	// Destructor
	void setSize(int size);
	int getSize();
	void addEdge(int x, int y);  // Add an edge to the graph
	void addNodColor(int n, int c);
	bool isConnected(int x, int y);	// Check if two vertices are connected
	bool possible(int x, int c); // check if the given test is possible
	bool ConnectedColor(int n, int c);// check if the given vertex is already connectedto a calor
	bool VertexAlone(int x); //checck if the given vertex is isolated
	int* verC; //vectot of the colors of the vertex
	
};


// Constructor

Graph::Graph(int size) {
	if (size > 1) {
		n = size;
	}
	else {
		n = 2;
	}
	adj = new int*[n];
	verC = new int[n];
	for (int i = 0; i < n; i++) {
		adj[i] = new int[n];	// Allocate memory for adjacency matrix
	}
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			adj[i][j] = 0;	// Initialize the vertices to 0
		}
	}
}// construtor

Graph::Graph() {
	n = 0;
}

// Destructor

Graph::~Graph() {
	for (int i = 0; i < n; i++) {
		delete[] adj[i];
	}
	delete[] adj;
	delete[] verC;
}// destrutor
void Graph::setSize(int size) {
	if (size > 1) {
		n = size;
	}
	else {
		n = 2;
	}
	adj = new int*[n];
	verC = new int[n];
	for (int i = 0; i < n; i++) {
		adj[i] = new int[n];	// Allocate memory for adjacency matrix
	}
	for (int i = 0; i < n; i++) {
		verC[i] = 0;
		for (int j = 0; j < n; j++) {
			adj[i][j] = 0;	// Initialize the vertices to 0
		}
	}
} //setSize

int Graph::getSize() {
	return n;
} //getSize

 // Add an edge to the graph, with with weigth

void Graph::addEdge(int x, int y) {
	adj[x][y] = adj[y][x] = 1;
}// addEdge

void Graph::addNodColor(int n, int c) {
	verC[n] = c;
}// addNodColor


 // Check if two vertices are connected

bool Graph::isConnected(int x, int y) {
	return (adj[x][y] == 1);
} //isConnected

//x = number of inserts; c = color
bool Graph::possible(int x, int c) {
	bool res = false;
	for (int i = 0; i < n && x > 0; i++) {
		if ( VertexAlone(i)) {
			for (int j = 0; j < n && x > 0; j++) {
				if (i != j && !isConnected(i, j)) {
					if (!ConnectedColor(i, verC[j])) {
						addEdge(i, j);
						x - 1;
						if (x == 0) {
							res = true;
							return res;
						}
					}
				}
			}
		}
	}
	for (int i = 0; i < n && x > 0; i ++) {
		for (int j = 0; j < n && x > 0; j++) {
			if (i != j && !isConnected(i, j)) { //if i and j are not connected
				if (!ConnectedColor(verC[i], verC[j])) { //if i is not conneced to a vertex with the same colo of the vertex  j
					addEdge(i , j);
					x = x - 1;
					if (x == 0) {
						res = true;
						return res;
					}
				}
			}
		}
	}
	return res;
}

bool Graph::ConnectedColor(int n, int c) {
	bool res = false;
	for (int i = 0; i < n; i++) {
		if (verC[i] == c) {
			res = true;
			break;
		}
	}
	return res;
}// ConnectedColor

bool Graph::VertexAlone(int x) {
	bool res = true;
	for (int i = 0; i < n; i++) {
		if (isConnected(x, i)) {
			res = false;
			break;
		}
	}
	return res;
}// VertexAlone

int main(){

	Graph g;
	int T, M, N, P, K, C, edge1, edge2;
	cin >> T;
	for (int i = 0; i < T; i++) {
		cin >> N;
		g.setSize(N);
		cin >> M >> P >> K;
		for (int j = 0; j < N; j++) {
			cin >> C;
			g.addNodColor(j, C);
		}
		for (int j = 0; j < M; j++) {
			cin >> edge1;
			cin >> edge2;
			g.addEdge(edge1 - 1, edge2 - 1);
		}
		if (M + P < (N-1) || !g.possible(P, K)) {
			cout << "N" << endl;
		}
		else {
			cout << "Y" << endl;
		}

	}



    return 0;

}// main
