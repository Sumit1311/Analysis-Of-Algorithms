#include<vector>
#include<iostream>
#include<cstdlib>
#include<ctime>

using namespace std;

class Graph {
	public:
		struct Edge {
		int src;
		int dest;
	};
		
	Graph(int V, int E = 0) {
		this->V = V;
		this->edges = vector<Edge>(E);
	}
	
	int getNumberVertices() {
		return V;	
	}
	
	int getNumberEdges() {
		return edges.size();
	}
	
	Edge getEdge(int i) {
		return edges[i];
	}
	
	void addEdge(int src, int dest) {
		Edge e;
		e.src = src;
		e.dest = dest;
		edges.push_back(e);
	}
	
	void print() {
		cout<<"Edges of the graphs are : "<<endl;
		for(vector<Edge>::iterator edge = edges.begin(); edge < edges.end(); ++edge) {
			cout<<"Endpoints of edge are "<<edge->src<<" -> "<<edge->dest<<endl;
		}
	}
	
	private:
		int V;
		vector<Edge> edges;
};

class UF {
	vector<int> parent;
	vector<int> rank;
	
	public:
		UF(int numberOfSets) {
			parent = vector<int>(numberOfSets);
			
			for(vector<int>::iterator itr = parent.begin(); itr < parent.end(); ++itr) {
				*itr = distance(parent.begin(), itr);
			}
			
			rank = vector<int>(numberOfSets, 0);
		}
		
		int find(int node) {
			if(parent[node] == node) {
				return node;
			}
			return parent[node] = find(parent[node]);
		}
		
		bool unionSet(int node1, int node2) {
			int set1 = find(node1);
			int set2 = find(node2);
			
			if(set1 != set2) { 
				if(rank[set1] > rank[set2]) {
					parent[node2] = set1;
				} else if(rank[set1] < rank[set2]) {
					parent[node1] = set2;
				} else {
					parent[node2] = set1;
					rank[set1]++;
				}
				return true;
			}else {
				return false;
			}
		}
};


int main() {
	Graph g(5);
	
	g.addEdge(0,1);
	g.addEdge(0,3);
	g.addEdge(0,2);
	g.addEdge(1,3);
	g.addEdge(2,3);
	
	srand(time(0));

	
	int vertices = g.getNumberVertices();
	UF uf(vertices);
	int edges = g.getNumberEdges();
	
	cout<<"Vertices : "<<vertices<<" , "<<"Edges : "<<edges<<endl;
	while( vertices > 2 ) {
		int chosenEdge = rand() % edges;
		Graph::Edge edge = g.getEdge(chosenEdge);
		cout<<"Edge "<<edge.src<<" -> "<<edge.dest<<endl;
		int set1 = uf.find(edge.src);
		int set2 = uf.find(edge.dest);
		cout<<"Sets "<<set1<<" , "<<set2<<endl;
		if(set1 == set2) {
			continue;
		}
		cout<<"Contracting edge "<<edge.src<<" -> "<<edge.dest<<endl;
		uf.unionSet(edge.src,edge.dest);
		
		vertices--;
		
		
	}
	
	cout<<"Vertices : "<<vertices<<" , "<<"Edges : "<<edges<<endl;
	
	//uf.print();
	
	int cutedges = 0;
	for(int i = 0; i < edges; ++i) {
		Graph::Edge edge = g.getEdge(i);
		cout<<"Edge "<<edge.src<<" -> "<<edge.dest<<endl;
		int set1 = uf.find(edge.src);
		int set2 = uf.find(edge.dest);
		cout<<"Sets "<<set1<<" , "<<set2<<endl;
		if(set1 != set2) {
			cutedges++;
		}
	}
	cout<<"Cut of the graph is "<<cutedges<<endl;
	return 0;
}
