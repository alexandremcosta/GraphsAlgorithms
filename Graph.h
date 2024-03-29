#include <string>
#include <map>

#define MAX_DISTANCE 1000

using namespace std;

class Graph
{
private:
	int** m_adjacency;
	int** l_adjacency;
	int** distance;
	int* indegree;
	int* outdegree;

	const int n_vertices;
	const double density;
	int infinity_distance;
	double random();
public:
	//Params:	int number_of_vertices, 
	//			double density
	Graph(int, double);
	~Graph();

	string to_string() const;

	//Algorithms
	int strong_components() const;

	//Params:	int choice, 
	//		int first,
	//		int last
	//TO DO: also create keys: "path", "first"
	map<string, string> shortest_path( char, int );
	map<string, string> dijkstra( int );
};