#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
using namespace std;

struct Node {
	string name;
	int pos;
	int connect = 0;
	Node* next;
	bool mark = false;
	bool connected = false;
};

class Graph {
private:
	Node* top;
	int size;
	int total;
	vector<vector<int>> graph;
	void add(string);
	void update(vector<string>);
	void dfs(string);
	void bfs(string);
	void connected(Node*, Node*);
	void dike(Node*, Node*, int, int& curr, int, vector<Node*>& order);
	void path(vector<Node*>, Node*);
	void cleanup();
public:
	Graph();
	void load(string);
	void display();
	void adjacent(string);
	void DFS(string);
	void BFS(string);
	bool Connected();
	void Dijkstra(string, string);
};