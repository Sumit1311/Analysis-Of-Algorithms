#include <bits/stdc++.h>

using namespace std;

class Stack {
	int *arr;
	int top;
	int MAX_STACK_SIZE = 255;
	public:
		Stack() {
			top = -1;
			arr = new int[MAX_STACK_SIZE];
		}
		
		void push(int data) {
			if((top + 1) != MAX_STACK_SIZE)
				arr[++top] = data;
		}
		
		int pop() {
			if(top < 0) {
				return -1;
			}
			int data = arr[top];
			top--;
			return data;
		}
		
		void print() {
			if(top == -1) {
				cout<<"Stack is empty"<<endl;
			}
			for(int i = 0; i <= top; ++i) {
				cout<<arr[i]<<"|";
			}
			cout<<endl;
		}
		
		bool isEmpty() {
			return top == -1 ? true : false;
		}
};

class GraphWithAdjList {
	public:
		typedef vector<int> NodeList;
		typedef vector<NodeList> AdjList;
	private:
		AdjList graph;
	public:
		GraphWithAdjList(int nodes) {
			graph = AdjList(nodes, NodeList());
		}
		
		bool checkIfEdgeExist(int src, int dest) {
			NodeList::iterator itr = graph[src].begin();
			while(itr != graph[src].end()) {
				if(*itr == dest) {
					return true;
				}
				++itr;
			}
			return false;
		}
		
		void addEdge(int src, int dest) {
			if(!checkIfEdgeExist(src, dest)) {
				graph[src].push_back(dest);
				graph[dest].push_back(src);
			}
		}
		
		NodeList getNeighbors(int node) {
			return graph[node];
		}
		
		void print() {
			cout<<"Graph in Adjacency List representation : "<<endl;
			for(AdjList::iterator adj = graph.begin(); adj != graph.end(); ++adj) {
				cout<<"Neighbors of node "<<distance(graph.begin(), adj)<<" : ";
				for(NodeList::iterator n = (*adj).begin(); n != (*adj).end(); ++n) {
					cout<<*n<<"|";
				}
				cout<<endl;
			}
		}
};

void dfs(GraphWithAdjList graph, int node, int visited[]) {
	if(visited[node] == 0) {
		visited[node] = 1;
		GraphWithAdjList::NodeList neighbors = graph.getNeighbors(node);
		for(GraphWithAdjList::NodeList::iterator n = neighbors.begin(); n != neighbors.end(); ++n) {
			dfs(graph, *n, visited);
		}	
	}
}

void dfs_non_recursive(GraphWithAdjList g, int visited[], Stack& s) {
	s.push(0);
	while(!s.isEmpty()) {
		int node = s.pop();
		if(visited[node] == 0) {
			visited[node] = 1;
			GraphWithAdjList::NodeList neighbors = g.getNeighbors(node);
			for(GraphWithAdjList::NodeList::iterator n = neighbors.begin(); n != neighbors.end(); ++n) {
				s.push(*n);
			}
		}
	}
}

bool dfs_to_detect_cycle(GraphWithAdjList graph, int node, int visited[], int parent) {
	visited[node] = 1;
	GraphWithAdjList::NodeList neighbors = graph.getNeighbors(node);
	for(GraphWithAdjList::NodeList::iterator n = neighbors.begin(); n != neighbors.end(); ++n) {
		if(visited[*n] == 0 ) {
			return dfs_to_detect_cycle(graph, *n, visited, node);	
		} else if(parent != *n) {
			return true;
		}
	}	
	return false;
}

bool dfs_to_detect_cycle_non_recursive(GraphWithAdjList graph, int node, int visited[], Stack& s) {
	int parent = -1;
	s.push(node);
	s.push(parent);
//	s.print();
	while(!s.isEmpty()) {
		parent = s.pop();
		int node = s.pop();
		
		//if(visited[node] == 0) {
			visited[node] = 1;
			GraphWithAdjList::NodeList neighbors = graph.getNeighbors(node);
			for(GraphWithAdjList::NodeList::iterator n = neighbors.begin(); n != neighbors.end(); ++n) {
				if(visited[*n] == 1 && parent != *n){
					return true;
				}
				s.push(*n);
				s.push(node);
			}
//			s.print();
		//}
	}
	return false;
}


int main() {
	//test stack
	Stack s;
	
	s.push(4);
	s.print();
	s.push(5);
	s.print();
	s.push(6);
	s.print();
	s.push(7);
	s.print();
	s.pop();
	s.print();
	s.pop();
	s.print();
	s.pop();
	s.print();
	s.push(8);
	s.print();
	s.push(9);
	s.print();
	s.pop();
	s.print();
	s.pop();
	s.print();
	s.pop();
	s.print();
	
	//test graph basic dfs
	GraphWithAdjList g(10);
	
	g.addEdge(0, 1);
	g.addEdge(0, 3);
	g.addEdge(1, 2);
	g.print();
	
	int visited[10] = {0};

	dfs_non_recursive(g, visited, s);
	cout<<"Visited is : ";
	for(int i = 0; i < 10; ++i) {
		cout<<visited[i]<<"|";
	}
	cout<<endl;
	for(int i = 0; i < 10; ++i) {
		visited[i] = 0;
	}
	
	dfs(g, 0, visited);
	cout<<"Visited is : ";
	for(int i = 0; i < 10; ++i) {
		cout<<visited[i]<<"|";
	}
	cout<<endl;
	for(int i = 0; i < 10; ++i) {
		visited[i] = 0;
	}
	
	g.addEdge(2, 3);
	g.print();
	bool cycleFound = dfs_to_detect_cycle(g, 0, visited, -1);
	cout<<(cycleFound ? " Cycle Found" : "Cycle Not Found")<<endl;
	for(int i = 0; i < 10; ++i) {
		visited[i] = 0;
	}
	cout<<endl;
	
	cycleFound = dfs_to_detect_cycle_non_recursive(g, 0, visited, s);
	cout<<(cycleFound ? " Cycle Found" : "Cycle Not Found")<<endl;
	for(int i = 0; i < 10; ++i) {
		visited[i] = 0;
	}
	cout<<endl;
}
