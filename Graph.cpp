#include <sstream>
#include <time.h>
#include <cstdlib>
#include "Graph.h"

Graph::Graph(int n, double d)
	:n_vertices(n), density(d)
{
	infinity_distance = 1;
	srand ( time(NULL) );

	//from_vertex = new int[n_vertices*n_vertices];
	//to_vertex = new int[n_vertices*n_vertices];

	m_adjacency = new int* [n_vertices];
	m_distance = new int* [n_vertices];
	for( int i = 0; i < n_vertices; i++ )
	{
		m_adjacency[i] = new int [n_vertices];
		m_distance[i] = new int [n_vertices];
	}

	for( int i = 0; i < n_vertices; i++ )
	{
		for( int j = 0; j < n_vertices; j++ )
		{
			if( i != j && random() < density )
			{
					//from_vertex[id_edge++] = i;
					//to_vertex[id_edge++] = j;
					m_adjacency[i][j] = 1;
					m_distance[i][j] = (int)(random() * 1000.);
					infinity_distance += m_distance[i][j];
			}
			else
			{
				m_adjacency[i][j] = 0;
				m_distance[i][j] = -1;
			}
		}
	}
	for( int i = 0; i < n_vertices; i++ )
	{
		for( int j = 0; j < n_vertices; j++ )
		{
			if ( m_distance[i][j] == -1 )
				m_distance[i][j] = infinity_distance;
		}
	}
}

Graph::~Graph()
{
	for( int i = 0; i < n_vertices; i++ )
		delete m_adjacency[i];

	//delete from_vertex;
	//delete to_vertex;
	delete m_adjacency;
}

string Graph::to_string() const
{
	stringstream graph_info;
	graph_info << "Graph Information: ";
	graph_info << "Number of vertices: " << n_vertices;
	graph_info << endl << "Density: " << density << endl;
	graph_info << "Adjacency Matrix: " << endl;
	for( int i = 0; i < n_vertices; i++ )
	{
		for( int j = 0; j < n_vertices; j++ )
			graph_info << m_adjacency[i][j] << " ";

		graph_info << endl;
	}
	
	return graph_info.str();
}

int Graph::strong_components() const
{
	return 0;
}

map<string, string> Graph::shortest_path( char choice, int first, int last )
{
	map<string, string> results;
	stringstream aux;

	switch(choice)
	{
	case 'd':
		aux << "Dijkstra";
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

double Graph::random()
{
	return rand() / (double) RAND_MAX;
}