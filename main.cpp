#include <iostream> //cin, cout
#include <string>
#include <map>
#include "Graph.h"

//Auxiliar function's prototypes
void wait();

int main( void )
{
	int n_vertices;
	double density;
	int choice = 1;

	cout << "Number of vertices: ";
	cin >> n_vertices;

	cout << "Graph's density (0.0 ~ 1.0): ";
	cin >> density;
	cout << endl;

	Graph* graph = new Graph(n_vertices, density);
	cout << graph->to_string();
	cout << "Number of strong components: ";
	cout << graph->strong_components() << endl;;
	wait();

	do
	{
		int first, last, choice_int;
		
		cout << "Shortest paths" << endl;
		cout << "First vertex: ";
		cin >> first;
		cout << "Last vertex: ";
		cin >> last;
		do
		{
			cout << "(1)Dijkstra, (2)Bellman or (3)Floyd: ";
			cin >> choice_int;
			switch(choice_int)
			{
			case 1:
				choice = 'd';
				break;
			case 2:
				choice = 'b';
				break;
			case 3:
				choice = 'f';
				break;
			default:
				cout << "Wrong choice!" << endl;
			}
		}while( choice_int != 1 && choice_int != 2 && choice_int != 3);
		map<string, string> shortest_path = graph->shortest_path( choice, first, last );
		cout << shortest_path["to_string"] << endl;
		cout << "Press 0 to finish or 1 to continue... ";
		cin >> choice;
	} while( choice != 0 );

	delete graph;
	return 0;
}

void wait( void )
{
	char ch;
	cout << "Press any key..." << endl;
	while (cin.get(ch) && ch != '\n');
	cin.get();
}

