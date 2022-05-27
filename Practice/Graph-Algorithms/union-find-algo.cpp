#include<vector>
#include<iostream>
#include<algorithm>

using namespace std;

typedef int Node;
typedef vector<Node> NodeList;
typedef vector<NodeList> AdjacencyList ;


class Graph {
	int V;
	AdjacencyList adj;
	public:
	Graph(int nodes) {
		V = nodes;
		adj = vector<vector<int> >(nodes);
	}
	
	addEdge(int src, int dest) {
		adj[src].push_back(dest);
		adj[dest].push_back(src);
	}
	
	
	void printGraph() {
		cout<<"Graph is : "<<endl;
		for(AdjacencyList::iterator v = adj.begin(); v < adj.end(); ++v) {
			cout<<distance(adj.begin(), v)<<" : ";
			for(NodeList::iterator e = v->begin(); e < v->end(); ++e) {
				cout<<*e<<",";
			}
			cout<<endl;
		}
	}
};
//Path Compression in union
class UFApproach1 {
	vector<int> parent;
	
	public:
	
	UFApproach1(int nodes) {
		parent = vector<int>(nodes);
		for(vector<int>::iterator itr = parent.begin(); itr < parent.end(); ++itr) {
			(*itr) = distance(parent.begin(), itr);
		}
	}
	
	int findLeader(int node) {
		return parent[node];
	}
	// 0 -> 0
	// 1 -> 0
	// 2 -> 0
	void unionNodes(int node1, int node2) {
		while(parent[node1] != node1) {
			node1 = parent[node1];
		}
		parent[node2] = node1;	
	}
	
	void print() {
		cout<<"UFApproach1 : "<<endl;
		for(vector<int>::iterator itr = parent.begin(); itr < parent.end(); ++itr) {
			cout << "Node : "<<distance(parent.begin(), itr) <<", Leader : "<< (*itr) << endl;
		}
		cout<<endl;
	}
};

//Path Compression in Find
class UFApproach2 {
	vector<int> parents;
	vector<int> ranks;
	public:
	UFApproach2(int nodes) {
		parents = vector<int>(nodes);
		ranks = vector<int>(nodes);
		for(vector<int>::iterator itr = parents.begin(); itr < parents.end(); ++itr) {
			*itr = distance(parents.begin(), itr);
		}
		
		for(vector<int>::iterator itr = ranks.begin(); itr < ranks.end(); ++itr) {
			*itr = 0;
		}
	}
	
	void print() {
		cout<<"UFApproach2 : "<<endl;
		for(vector<int>::iterator itr = parents.begin(); itr < parents.end(); ++itr) {
			cout<<"Node : "<<distance(parents.begin(), itr)<<", Set : "<<*itr<<", Rank : "<<ranks[distance(parents.begin(), itr)]<<endl;
		}
		cout<<endl;
	}
	
	int findSet(int node) {
		int parent = parents[node];
		
		if(parent == node) {
			return parent;
		}
		
		return parents[node] = findSet(parent);
	}
	
	bool unionSet(int node1, int node2) {
		int set1 = findSet(node1);
		int set2 = findSet(node2);
		cout<<"Set1 : "<<set1<<", Set2 : "<<set2<<endl;
		if(set1 != set2) {
			if(ranks[set1] < ranks[set2]) {
				parents[set1] = set2;
			} else if(ranks[set2] < ranks[set1]) {
				parents[set2] = set1;	
			} else {
				parents[set1] = set2;
				ranks[set2]++;
			}
			return true;
		} else {
			return false;
		}
	}
};



int main() {
//	int V = 5;
//	Graph graph(V);
//	
//	graph.addEdge(0,4);
//	graph.printGraph();
	
	UFApproach1 uf1(5);
	
	uf1.print();
	if(uf1.findLeader(0) != uf1.findLeader(1)) {
		uf1.unionNodes(0, 1);	
	}
	uf1.print();
	if(uf1.findLeader(0) == uf1.findLeader(1)) {
		cout<<"Same Leader"<<endl;
	}
	uf1.unionNodes(1,2);
	uf1.print();
	uf1.unionNodes(2,4);
	uf1.print();
	
	UFApproach2 uf2(8);
	
	uf2.print();
	uf2.unionSet(1, 0);	
	cout<<"Set of 0 : "<<uf2.findSet(0)<<endl;
	cout<<"Set of 1 : "<<uf2.findSet(1)<<endl;
	uf2.print();
	uf2.unionSet(2, 1);	
	cout<<"Set of 1 : "<<uf2.findSet(1)<<endl;
	
	
	
	cout<<"Set of 2 : "<<uf2.findSet(2)<<endl;
	uf2.print();
	uf2.unionSet(2, 4);	
	cout<<"Set of 2 : "<<uf2.findSet(2)<<endl;
	cout<<"Set of 4 : "<<uf2.findSet(4)<<endl;
	uf2.print();
	
	uf2.unionSet(4, 6);	
	cout<<"Set of 4 : "<<uf2.findSet(4)<<endl;
	cout<<"Set of 6 : "<<uf2.findSet(6)<<endl;
	uf2.print();
	
	uf2.unionSet(5, 2);	
	cout<<"Set of 2 : "<<uf2.findSet(2)<<endl;
	cout<<"Set of 5 : "<<uf2.findSet(5)<<endl;
	uf2.print();
	
	uf2.unionSet(5, 7);	
	cout<<"Set of 5 : "<<uf2.findSet(5)<<endl;
	cout<<"Set of 7 : "<<uf2.findSet(7)<<endl;
	uf2.print();
	
	uf2.unionSet(1, 3);	
	cout<<"Set of 1 : "<<uf2.findSet(1)<<endl;
	cout<<"Set of 3 : "<<uf2.findSet(3)<<endl;
	uf2.print();
	
	cout<<uf2.findSet(0)<<endl;
	uf2.print();
	cout<<uf2.findSet(4)<<endl;
	uf2.print();
	cout<<uf2.findSet(6)<<endl;
	uf2.print();
	return 0;	
}
