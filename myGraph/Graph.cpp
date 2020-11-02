#include "Graph.h"

Graph::Graph() {
	top = nullptr;
	graph;
	size = 0;
	total = 0;
}

void Graph::load(string s) {
	ifstream infile(s);

	if (infile) {
		string line;
		while (getline(infile, line)) {
			string word, num = "";
			vector<string> new_line;
			int counter = 0;
			line += ' ';
			for (char c : line) {
				if (counter % 2 == 1 || counter == 0) {
					if (c == ' ') {
						if (word != "") {
							add(word);
							new_line.push_back(word);
							word = "";
							counter++;
						}
					}
					else if (c == '=' || c == '>') {
						continue;
					}
					else {
						word += c;
					}
				}
				else {
					if (c == ' ') {
						counter++;
						new_line.push_back(num);
						num = "";
					}
					else {
						num += c;
					}
				}
			}
			update(new_line);
		}
		infile.close();
	}
}

void Graph::add(string s) {
	Node* runner = top;
	while (runner != nullptr) {
		if (runner->name == s) return;
		runner = runner->next;
	}
	if (size == 0) {
		Node* p = new Node;
		p->name = s;
		p->pos = size;
		p->next = top;
		top = p;
	}
	else if (runner == nullptr) {
		Node* r = top;
		while (r->next != nullptr)
			r = r->next;
		Node* p = new Node;
		p->name = s;
		p->pos = size;
		p->next = nullptr;
		r->next = p;
	}
	size++;
	vector<int> new_vector(size);
	graph.push_back(new_vector);
	for (int i = 0; i < size - 1; i++) {
		graph[i].push_back(0);
	}
}

void Graph::update(vector<string> s) {
	Node* runner = top;
	while (runner->name != s.at(0))
		runner = runner->next;
	int spot = runner->pos;
	int num = 0;
	for (int i = s.size(); i > 1; i--) {
		if (i % 2 == 0) {
			runner = top;
			while (runner->name != s[i - 1])
				runner = runner->next;
			graph[spot][runner->pos] = num;
		}
		else {
			num = stoi(s[i - 1]);
			total += num;
		}
	}
}

void Graph::display() {
	Node* runner = top;
	cout << '\t';
	while (runner != nullptr) {
		cout << runner->name << '\t';
		runner = runner->next;
	}
	cout << endl << endl;
	runner = top;
	for (int i = 0; i < size; i++) {
		cout << " " << runner->name << "\t";
		for (int j = 0; j < size; j++) {
			cout << graph[i][j] << "\t";
		}
		cout << endl << endl;
		runner = runner->next;
	}
}

void Graph::adjacent(string s) {
	Node* runner = top;
	while (runner != nullptr && runner->name != s)
		runner = runner->next;
	if (runner == nullptr) {
		cout << "There is no " << s << " name in the digraph\n\n";
		return;
	}
	Node* run = top;
	cout << runner->name << ": ";
	for (int i = 0; i < size; i++) {
		if (graph[runner->pos][i] > 0) {
			cout << run->name << " ";
		}
		run = run->next;
	}
	cout << endl << endl;
}

void Graph::dfs(string s) {
	Node* runner = top;
	while (runner != nullptr && runner->name != s)
		runner = runner->next;
	Node* run = top;
	for (int i = 0; i < size; i++) {
		if (graph[runner->pos][i] > 0 && run->mark == false) {
			run->mark = true;
			cout << " -> " << run->name;
			dfs(run->name);
			cout << "\nBack to " << s;
			run->mark = false;
		}
		run = run->next;
	}
}

void Graph::DFS(string s) {
	Node* runner = top;
	while (runner != nullptr && runner->name != s)
		runner = runner->next;
	if (runner == nullptr) {
		cout << "There is no " << s << " word in the digraph\n\n";
		return;
	}
	runner->mark = true;
	cout << s;
	dfs(s);
	cout << endl << endl;
	runner->mark = false;
}

void Graph::bfs(string s) {
	cout << s << " -> ";
	Node* runner = top;
	while (runner != nullptr && runner->name != s)
		runner = runner->next;
	Node* run = top;
	for (int i = 0; i < size; i++) {
		if (graph[runner->pos][i] > 0) {
			cout << " " << run->name;
		}
		run = run->next;
	}
	cout << endl;
	run = top;
	for (int i = 0; i < size; i++) {
		if (graph[runner->pos][i] > 0 && run->mark == false) {
			run->mark = true;
			bfs(run->name);
		}
		run = run->next;
	}
}

void Graph::BFS(string s) {
	Node* runner = top;
	int depth, total = 0;
	while (runner != nullptr && runner->name != s)
		runner = runner->next;
	if (runner == nullptr) {
		cout << "There is no " << s << " word in the digraph\n\n";
		return;
	}
	runner->mark = true;
	bfs(s);

	cleanup();
	cout << endl;
}

void Graph::connected(Node* r, Node* n) {
	Node* runner = top;
	for (int i = 0; i < size; i++) {
		if (graph[n->pos][i] > 0 && runner->mark == false) {
			if (runner->connected == true) {
				r->connected = true;
				return;
			}
			else {
				runner->mark = true;
				r->connect++;
			}
		}
		runner = runner->next;
	}
	if (r->connect != size - 1) {
		int j = n->pos;
		n = top;
		for (int i = 0; i < size; i++) {
			if (graph[j][i] > 0)
				connected(r, n);
			n = n->next;
			if (r->connected == true) {
				break;
			}
		}
	}
	else {
		r->connected = true;
		return;
	}
}

bool Graph::Connected() {
	Node* runner = top;
	Node* r = top;
	while (runner != nullptr) {
		connected(runner, runner);
		while (r != nullptr) {
			r->mark = false;
			r = r->next;
		}
		r = top;
		runner = runner->next;
	}

	runner = top;
	while (runner != nullptr) {
		if (runner->connected != true) {
			cleanup();
			return false;
		}
		runner = runner->next;
	}
	cleanup();
	return true;
}

void Graph::dike(Node* s, Node* e, int t, int& curr, int run, vector<Node*>& order) {
	Node* r = top;
	for (int i = 0; i < size; i++) {
		if (graph[s->pos][i] > 0 && r == e && (t + graph[s->pos][i]) < curr) {
			order[run] = r;
			curr = t + graph[s->pos][i];
			e->connected = true;
			break;
		}
		r = r->next;
	}
	r = top;
	for (int i = 0; i < size; i++) {
		if (graph[s->pos][i] > 0 && r->mark == false && r != e && t + graph[s->pos][i] < curr) {
			r->mark = true;
			bool hold = false;
			if (e->connected) {
				e->connected = false;
				hold = true;
			}
			dike(r, e, t + graph[s->pos][i], curr, run + 1, order);
			if (e->connected) order[run] = r;
			if (hold) e->connected = hold;
			r->mark = false;
		}
		r = r->next;
	}
}

void Graph::path(vector<Node*> order, Node* e) {
	if (order[1] == nullptr) {
		cout << "The two are not connected in any way\n\n";
		return;
	}
	int i = 0;
	while (i < size) {
		if (order[i] == e) break;
		cout << order[i]->name << " -" << graph[order[i]->pos][order[i + 1]->pos] << "-> ";
		i++;
	}
	cout << order[i]->name << endl << endl;
}

void Graph::Dijkstra(string start, string end) {
	Node* s = top;
	Node* e = top;
	while (s != nullptr && s->name != start) {
		s = s->next;
	}
	while (e != nullptr && e->name != end) {
		e = e->next;
	}
	if (s == nullptr) {
		cout << start << " does not exist in the digraph\n\n";
		return;
	}
	if (e == nullptr) {
		cout << end << " does not exist in the digraph\n\n";
		return;
	}
	if (start == end) {
		cout << "They are the same place\n\n";
		return;
	}
	int curr = total;
	vector<Node*> order(size);
	order[0] = s;
	s->mark = true;
	dike(s, e, 0, curr, 1, order);
	s->mark = false;
	path(order, e);
	cleanup();
}

void Graph::cleanup() {
	Node* r = top;
	while (r != nullptr) {
		r->connect = 0;
		r->connected = false;
		r->mark = false;
		r = r->next;
	}
}
