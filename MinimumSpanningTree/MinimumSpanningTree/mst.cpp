#include <vector>
#include <iostream>
#include <map>
#include <string>
#include <algorithm>
#include <sstream>

using namespace std;

struct Edge{
	Edge(int u, int v, int w) :from(u), to(v), weight(w), selected(false){}
	bool operator<(const Edge &a){ return (weight < a.weight); }
	int from, to, weight;
	bool selected;
};

class Graph{
public:
	bool connected(const string, const string);
	void addEdge(const string, const string, int weight);
	void addNode(const string node);
	void generateMST();
	int getRoot(int);
	void printMST();
private:
	vector<Edge> edge;
	vector<int> parent;
	map<string, int> id2index;
	map<int, string> index2id;
};


void Graph::addNode(const string node)
{
	int num = id2index.size();
	id2index[node] = num;
	index2id[num] = node;
	parent.push_back(num);
}

void Graph::addEdge(const string u, const string v, int weight)
{
	edge.push_back(Edge(id2index[u], id2index[v], weight));
}

int Graph::getRoot(int node)
{
	while (parent[node] != node) node = parent[node];
	return node;
}

void Graph::generateMST()
{
	sort(edge.begin(), edge.end());
	for (auto &p : edge) p.selected = false;
	for (auto &p : edge)
	{
		if (p.selected) continue;
		if (getRoot(p.from) == getRoot(p.to)) continue;
		p.selected = true;
		parent[p.from] = getRoot(p.to);
	}
}

void Graph::printMST()
{
	cout << endl;
	for (auto p : edge)
	{
		if (p.selected) cout << index2id[p.from] << "---<" << p.weight << ">---" << index2id[p.to] << endl;
	}
	cout << endl;
}

int main()
{
	cout << "Power Grid Price Assessment System" << endl;
	cout << "==================================" << endl;
	cout << "1 - add vertex" << endl;
	cout << "2 - add edge" << endl;
	cout << "3 - create MST" << endl;
	cout << "4 - show MST" << endl;
	cout << "5 - quit" << endl;
	cout << "==================================" << endl << endl;

	int op;
	Graph graph;
	while (1)
	{
		cout << "please input the operation: ";
		cin.sync(); cin.clear();
		cin >> op;
		if (op == 5) break;
		switch (op)
		{
		case 1:{
			cout << "！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！" << endl;
			cout << "Please input the names of the vertexes, divided by space and end with Enter: ";
			string input, node;
			cin.sync(); cin.clear();
			getline(cin, input);
			istringstream iss(input);
			while (iss >> node) graph.addNode(node);}
			break;
		case 2:{
		   int weight;
		   string input, node, node2;		
		   cout << "！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！" << endl;
		   while (1)
		   {
			   cout << "Please input the vertexes of the edge and the weight, stop input with input \"#\" " << endl;
			   cin.sync(); cin.clear();
			   getline(cin, input);
			   istringstream iss(input);
			   iss >> node;
			   if (node == "#") break;
			   iss >> node2 >> weight;
			   graph.addEdge(node, node2, weight);
		   }}
			break;
		case 3:
			graph.generateMST();
		case 4:
			graph.printMST();
		default:
			break;
		}
		cout << "！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！" << endl;
	}
	return 0;
}