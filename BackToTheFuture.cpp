
#include <iostream>
#include <stack>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;
const int inf = 1 << 30;

// Abstraction of a graph

class Graph
{
private:
	int n;							// Number of vertices
	int** adj;						// Adjacency matrix
	int length;                     // Length of the Edge 
public:
	Graph(int size);				// Constructor
	~Graph();						// Destructor
	void addEdge(int x, int y, int z); 	// Add an edge the the graph
	void destroyEgde(int x, int y);
	bool isConnected(int x, int y);	// Check if two vertices are connected
	int Dijkstra(int A, int B);     // Dijkstra shortest path
	void printMatrix();              //print the adj Matrix
};

// Constructor

Graph::Graph(int size)
{
	if (size < 2)				// The graph must have at least 2 vertices
	{
		n = 2;
	}
	else
	{
		n = size;
	}

	adj = new int*[n];			// Allocate memory for adjacency matrix

	for (int i = 0; i<n; ++i)
	{
		adj[i] = new int[n];	// Allocate memory for adjacency matrix
	}

	for (int i = 0; i<n; ++i)
	{
		for (int j = 0; j<n; ++j)
		{
			adj[i][j] = inf;		// Initialize the vertices to 0
		}
	}
}

// Destructor

Graph::~Graph()
{
	for (int i = 0; i<n; ++i)
	{
		delete[] adj[i];
	}
	delete[] adj;
}

// Add an edge to the graph

void Graph::addEdge(int x, int y, int z)
{
	adj[x][y] = adj[y][x] = z;
}

// Destroy an edge on the graph

void Graph::destroyEgde(int x, int y)
{
	adj[x][y] = adj[y][x] = inf;
}

// Check if two vertices are connected

bool Graph::isConnected(int x, int y)
{
	//return (adj[x - 1][y - 1] == 1);
	return ((adj[x][y] != 0) && (adj[y][x] != 0));
}

int Graph::Dijkstra(int A, int B) {
	vector<int> dist(n);
	vector<bool> vis(n);

	for (int i = 0; i < n; ++i) {
		dist[i] = inf;
	}
	dist[A] = 0;

	for (int i = 0; i < n; ++i) {
		int cur = -1;
		for (int j = 0; j < n; ++j) {
			if (vis[j]) continue;
			if (cur == -1 || dist[j] < dist[cur]) {
				cur = j;
			}
		}

		vis[cur] = true;
		for (int j = 0; j < n; ++j) {
				int path = dist[cur] + adj[cur][j];
			if (path < dist[j]) {
				dist[j] = path;
			}
		}
	}
	return dist[B];
}

void Graph::printMatrix()
{
	int aux;
	for (int i = 0; i<n; ++i)
	{
		cout << "[ ";
		for (int j = 0; j<n; ++j)
		{
			aux = adj[i][j];		// Initialize the vertices to 0
			cout << aux << " ";
		}
		cout << "]" << endl;
	}
}


// Main function

int main()
{
	int times = 0;
	int number;
	int trips;
	cin >> number >> trips;
	


	while (number != 0 || trips != 0) {
		Graph g(number);
		for (int i = 0; i < trips; ++i) {
			int x, y, z;
			cin >> x >> y >> z;
			g.addEdge(x - 1, y - 1, z);
			
		}
		int humans, seats;
		cin >> humans >> seats;
		int passengers = min(humans, seats);
		long total = 0;

		while (humans > 0 && trips > 0) {
			total = g.Dijkstra(0, (number - 1));
			total *= passengers;
			trips--;
			humans -= passengers;

		}
		
		cout << total;
		cin >> number >> trips;
	}

	return 0;
} 

/**
Code is incomplete whats is missing is a way to delete the shortest path found by 
Dijkstra function  in order to proceed with the resolution of the problem.
**/
