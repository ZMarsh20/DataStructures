#include "Graph.h"

int main() {
	Graph g1 = Graph();
	g1.load("Text.txt");
	string enter, enter2;

	g1.display();
	cout << "pick a name for adjacency: ";
	cin >> enter;
	g1.adjacent(enter);
	cout << "pick a name for DFS: ";
	cin >> enter;
	g1.DFS(enter);
	cout << "pick a name for BFS: ";
	cin >> enter;
	g1.BFS(enter);
	if (g1.Connected()) {
		cout << "Connected!!\n\n";
	}
	else {
		cout << "Not connected :(\n\n";
	}

	cout << "pick a name Dijkstra: ";
	cin >> enter;
	cout << "pick the second name: ";
	cin >> enter2;
	g1.Dijkstra(enter, enter2);
}