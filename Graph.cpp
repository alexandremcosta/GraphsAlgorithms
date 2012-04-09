#include <sstream>
#include <time.h>
#include <cstdlib>
#include "Graph.h"

Graph::Graph(int n, double d)
	:n_vertices(n), density(d)
{
	infinity_distance = 1;
	srand ( time(NULL) );

	//Create Graph, Adjacency Matrix, Adjacency List (as a matrix) and Distance Matrix
	m_adjacency = new int* [n_vertices];
	l_adjacency = new int* [n_vertices];
	distance = new int* [n_vertices];
	indegree = new int [n_vertices];
	outdegree = new int [n_vertices];

	for( int i = 0; i < n_vertices; i++ )
	{
		m_adjacency[i] = new int [n_vertices];
		l_adjacency[i] = new int [n_vertices];
		distance[i] = new int [n_vertices];
		indegree[i] = 0;
		outdegree[i] = 0;
	}

	for( int i = 0, k = 0; i < n_vertices; i++, k = 0 )
	{
		for( int j = 0; j < n_vertices; j++ )
		{
			l_adjacency[i][j] = -1;
			if( i != j && random() < density )
			{
				m_adjacency[i][j] = 1;
				l_adjacency[i][k++] = j;
				indegree[j]++;
				outdegree[i]++;
				distance[i][j] = (int)(random() * 100.);
				infinity_distance += distance[i][j];
			}
			else
			{
				m_adjacency[i][j] = 0;
				distance[i][j] = -1;
			}
		}
	}
	for( int i = 0; i < n_vertices; i++ )
	{
		for( int j = 0; j < n_vertices; j++ )
		{
			if ( distance[i][j] == -1 )
				distance[i][j] = infinity_distance;
		}
	}	
}

Graph::~Graph()
{
	for( int i = 0; i < n_vertices; i++ )
	{
		delete m_adjacency[i];
		delete distance[i];
	}
	//delete from_vertex;
	//delete to_vertex;
	delete m_adjacency;
	delete distance;
	delete indegree;
	delete outdegree;
}

string Graph::to_string() const
{
	stringstream graph_info;
	graph_info << "Graph Information:" << endl;
	graph_info << "Number of vertices: " << n_vertices << endl;
	graph_info << "Density: " << density << endl;
	graph_info << "Adjacency Matrix:" << endl;

	graph_info << "   ";
	for( int j = 0; j < n_vertices; j++ )
		graph_info << "#" << j << "\t";
	graph_info << endl;
	for( int i = 0; i < n_vertices; i++ )
	{
		graph_info << "#" << i << ": ";
		for( int j = 0; j < n_vertices; j++ )
			graph_info << m_adjacency[i][j] << "\t";

		graph_info << endl;
	}
	graph_info << endl << "Adjacency List:" << endl;
	for( int i = 0; i < n_vertices; i++ )
	{
		graph_info << "Vertex " << i << ": ";
		for( int k = 0; l_adjacency[i][k] != -1; k++ )
			graph_info << l_adjacency[i][k] << ",\t";

		graph_info << endl;
	}

	graph_info << endl << "Distances:" << endl;
	graph_info << "\t";
	for( int j = 0; j < n_vertices; j++ )
		graph_info << "#" << j << "\t";
	graph_info << endl;
	for( int i = 0; i < n_vertices; i++ )
	{
		graph_info << "#" << i << ":\t";
		for( int j = 0; j < n_vertices; j++ )
			graph_info << distance[i][j] << "\t";

		graph_info << endl;
	}

	return graph_info.str();
}

int Graph::strong_components() const
{
	return 0;
}

map<string, string> Graph::shortest_path( char choice, int first )
{
	map<string, string> results;
	stringstream aux;

	switch(choice)
	{
	case 'd':
		return dijkstra( first );
		break;
	case 'b':
		aux << "Bellman";
		break;
	case 'f':
		aux << "Floyd";
		break;
	default:
		aux << "Unknown algorithm!";
	}

	results["to_string"] = aux.str() + " unimplemented!";

	return results;
}

map<string, string> Graph::dijkstra( int first )
{
	int* path_distance = new int [n_vertices];
	int* precedent = new int [n_vertices];
	int* visit_rank = new int [n_vertices];
	stringstream stream;

	//Initialization
	for( int i = 0; i < n_vertices; i++ )
	{
		path_distance[i] = infinity_distance;
		precedent[i] = -2;
		visit_rank[i] = -1;
	}

	//Source initialization
	path_distance[first] = 0;
	precedent[first] = -1;
	visit_rank[first] = 0;

	for( int j = 0; j < outdegree[first]; j++ )
	{
		int vertex = l_adjacency[first][j];
		if( path_distance[vertex] > path_distance[first] + distance[first][vertex] )
		{
			path_distance[vertex] = path_distance[first] + distance[first][vertex];
			precedent[vertex] = first;
		}
	}

	//Dijkstra's algorithm
	for( int rank = 1; rank < n_vertices; rank++ )
	{
		int next_vertex = -1;
		int min_distance = infinity_distance;

		//Find closest vertex
		for( int vertex = 0; vertex < n_vertices; vertex++ )
		{
			if( path_distance[vertex] < min_distance && visit_rank[vertex] == -1 )
			{
				next_vertex = vertex;
				min_distance = path_distance[next_vertex];
			}
		}

		// If there is no next vertex, dijkstra is done
		if( next_vertex == -1 )
			break;

		visit_rank[next_vertex] = rank;
		int visited_vertex = next_vertex;

		stream << "Rank: " << rank << " | Vertex: " << visited_vertex << " | Distance: " << min_distance << endl;

		//Update distances
		for( int j = 0; j < outdegree[visited_vertex]; j++ )
		{
			next_vertex = l_adjacency[visited_vertex][j];
			if( path_distance[next_vertex] > path_distance[visited_vertex] + distance[visited_vertex][next_vertex] 
			&&  visit_rank[next_vertex] == -1 )
			{
				path_distance[next_vertex] = path_distance[visited_vertex] + distance[visited_vertex][next_vertex];
				precedent[next_vertex] = visited_vertex;
			}
		}
	}

	map<string, string> results;
	results["to_string"] = stream.str();

	delete path_distance;
	delete precedent;
	delete visit_rank;

	return results;
}

double Graph::random()
{
	return rand() / (double) RAND_MAX;
}