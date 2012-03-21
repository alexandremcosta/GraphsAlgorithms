#include <string>
#include <map>

#define MAX_DISTANCE 1000

using namespace std;

class Graph
{
private:
	int** m_adjacency;
	int** m_distance;

	const int n_vertices;
	const double density;
	int infinity_distance;
	double random();
	//int* from_vertex;
	//int* to_vertex;
public:
	//Params:	int number_of_vertices, 
	//			double density
	Graph(int, double);
	~Graph();

	string to_string() const;

	int strong_components() const;

	//Params:	int choice, 
	//			int first,
	//			int last
	//TO DO: also create keys: "path", "first", "last"
	map<string, string> shortest_path( char, int, int );
};