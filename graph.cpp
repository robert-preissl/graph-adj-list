#include <iostream>
#include <unordered_map>
#include <vector>
#include <set>

using namespace std;


class Node {
	public:
		int id;
		int x;

		Node(int id, int value) {
			this->id = id;
			this->x = value;
		}
		
		friend bool operator< (const Node &a, const Node &b) {
			return a.id < b.id;
		}
	
};


class Graph {
	private:
		int nrV;
		unordered_map<int, vector<Node> > adjList;
		set<Node> nodes;
		
		void dfTrUtil( unordered_map<int, bool >& visited, Node start );
		
	public:
		Graph(); // default Cons
		Graph(const Graph& g); // copy Cons
		
		~Graph(); // Destr
		
		Graph& operator=(const Graph& g); // copy assignment op
		
		void addEdge( const Node& a, const Node& b);
		
		void printAdjList();
		
		void dfTraversal(Node start);

};

void printVec(const vector<Node>& vec ) {
	for( int i = 0; i < vec.size(); ++i ) {
		cout << "[" << vec[i].id << ", " << vec[i].x << "], ";
	}
	cout << endl;
}

void Graph :: printAdjList() {
	cout << "Print adj list. for " << nrV << " many nodes. " << endl;
	unordered_map<int, vector<Node> > :: const_iterator cit;
	for( cit = adjList.begin(); cit != adjList.end(); ++cit ) {
		cout << " for node with id " << cit->first << " :  ";
		for( int i = 0; i < cit->second.size(); ++i ) {
			cout << "[" << cit->second[i].id << ", " << cit->second[i].x << "], ";
		}
		cout << endl;
	}
}

void Graph :: dfTrUtil( unordered_map<int, bool >& visited, Node start ) {
	cout << " Node with value: " << start.x << endl;
	visited[ start.id ] = true;
	
	vector<Node> vN = adjList[start.id];
	for( int i = 0; i < vN.size(); ++i ) {
		if( !visited[ vN[i].id ] ) {
			dfTrUtil(visited, vN[i]);
		}
	}
}

void Graph :: dfTraversal(Node start) {
	unordered_map<int, bool > visited;
	set<Node> :: const_iterator cit;
	for( cit = nodes.begin(); cit != nodes.end(); ++cit ) {
		visited[ cit->id ] = false;
	}
	dfTrUtil(visited, start);
}

void Graph :: addEdge( const Node& a, const Node& b) {
	// check if a is new node
	unordered_map<int, vector<Node> > :: iterator it = adjList.find(a.id);
	if( it != adjList.end() ) {
		//cout << "Found. adding vec: " << endl; printVec(v);
		it->second.push_back(b);
	} else {
		vector<Node> v;
		v.push_back(b);
		adjList[a.id] = v;
		// cout << "NOT Found. adding vec: " << endl; printVec(v);
	}
	nodes.insert(a);
	nodes.insert(b);
	nrV = nodes.size();
}

Graph :: Graph() {
	nrV = 0;
}

Graph :: Graph(const Graph& g) {
	this->nrV     = g.nrV;
	this->adjList = g.adjList;
}

Graph :: ~Graph() {
	adjList.clear();
}

Graph& Graph :: operator=(const Graph& g) {
	this->nrV     = g.nrV;
	this->adjList = g.adjList;
	return *this;
}


int main() {

	Node n1 = Node(1,1);
	Node n2 = Node(2,3);
	Node n3 = Node(3,5);
	Node n4 = Node(4,7);
	Node n5 = Node(5,9);
	Node n6 = Node(6,13);
	Node n7 = Node(7,2);
	Node n8 = Node(8,11);
	Node n9 = Node(9,12);
	Node n10 = Node(10,100);

	Graph* gp = new Graph();
	gp->addEdge(n1, n3);
	gp->addEdge(n2, n3);
	gp->addEdge(n4, n3);
	gp->addEdge(n2, n4);
	gp->addEdge(n7, n3);
	gp->addEdge(n7, n6);
	gp->addEdge(n4, n7);
	gp->addEdge(n3, n6);
	gp->addEdge(n3, n5);
	gp->addEdge(n5, n8);
	gp->addEdge(n8, n9);
	gp->addEdge(n3, n10);
	gp->addEdge(n10, n5);
	
	cout << "Start" << endl;
	gp->printAdjList();
	cout << endl; cout << endl;

	gp->dfTraversal(n1);
	
	delete gp;

	return 0;

}
