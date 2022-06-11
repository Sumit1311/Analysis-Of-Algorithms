#include<cstdlib>
#include<iostream>
#include<vector>
#include<algorithm>

using namespace std;

class Queue {
	private:
		struct Node {
			int data;
			Node *next;
		} *front, *back;
	public:
		Queue() {
			front = back = NULL;
		}
		
		void push_back(int data) {
			Node *new_node = new Node();
			new_node->data = data;
			new_node->next = NULL;
			
			if(back == NULL && front == NULL) {
				front = new_node;
			} else {
				back->next = new_node;
			}
			back = new_node;
		}
		
		void pop_front() {
			if(back == NULL && front == NULL) {
				return;
			}
			
			if(back == front) {
				delete back;
				back = front = NULL;
			} else {
				Node *next = front->next;
				delete front;
				front = next;
			}
		}
		
		int frontEle()	{
			if(front != NULL) {
				return front->data;
			} else {
				return -1;
			}
		}
		
		void print() {
			Node *next = front;
			if(back == NULL && front == NULL) {
				cout<<"Queue is empty"<<endl;
				return;
			}
			cout<<"Queue is : ";
			do{
				cout<<next->data<<"|";
				next = next->next;
			}
			while(next != NULL);
			cout<<endl;
		}
		
		bool isEmpty() {
			return ((front == NULL && back == NULL) ? true : false);
		}
};

class GraphWithAdjacencyList {
	public:
		typedef vector<int> NodeList;
		typedef vector<NodeList> AdjList;
	private:
		AdjList graph;
	public:
		GraphWithAdjacencyList(int nodes) {
			graph = AdjList(nodes, NodeList(0));
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
			AdjList::iterator adjG = graph.begin();
			
			while(adjG != graph.end()) {
				cout<<"Neighbors for "<<distance(graph.begin(), adjG)<<" : ";
				NodeList::iterator nodeItr = (*adjG).begin();
				while(nodeItr != (*adjG).end()) {
					cout<<*nodeItr<<"|";
					++nodeItr;
				}
				++adjG;
				cout<<endl;
			}
		}
};

int main() {
	//Test Queue
	Queue bfsQueue;
	bfsQueue.print();
	bfsQueue.pop_front();
	bfsQueue.print();
	bfsQueue.push_back(1);
	bfsQueue.print();
	bfsQueue.push_back(2);
	bfsQueue.print();
	bfsQueue.push_back(3);
	bfsQueue.print();
	bfsQueue.pop_front();
	bfsQueue.print();
	bfsQueue.push_back(4);
	bfsQueue.print();
	bfsQueue.pop_front();
	bfsQueue.print();
	bfsQueue.pop_front();
	bfsQueue.print();
	bfsQueue.pop_front();
	bfsQueue.print();
	bfsQueue.pop_front();
	//Test Graph
	GraphWithAdjacencyList g(10);
	
	g.addEdge(0,1);
	g.print();
	g.addEdge(0,3);
	g.print();
	g.addEdge(1,2);
	g.print();
	
	
	//Run bfs to find path from s to d
	vector<bool> visited(10);
	int s = 0, d = 2;
	vector<int> parent(10, -1);
	
	bfsQueue.push_back(s);
	visited[s] = true;
	int par;
	bool foundPath = false;
	while(!bfsQueue.isEmpty()) {
		GraphWithAdjacencyList::NodeList neighbors = g.getNeighbors(bfsQueue.frontEle());
		par = bfsQueue.frontEle();
		bfsQueue.pop_front();
		for(GraphWithAdjacencyList::NodeList::iterator n = neighbors.begin(); n != neighbors.end(); ++n) {
			
			if(visited[*n] == false){
				bfsQueue.push_back(*n);
				visited[*n] = true;
				parent[*n] = par;
			} /*else {
				cout<<*n<<endl;
				cout<<"Cycle Detected"<<endl;
				return 1;
			}*/
			if(*n == d) {
				foundPath = true;
				break;
			}
		}
		if(foundPath == true) {
			break;
		}
	}
	cout<<"Path "<<(foundPath ? "Found" : "Not Found")<<endl;
	
	if(foundPath) {
		vector<int> path;
		int node = d;
		do {
			path.push_back(node);
			node = parent[node];
		} while(node != -1);
		cout<<"Shortest Path with distance "<< path.size() - 2 << " is : ";
		for(vector<int>::reverse_iterator itr = path.rbegin(); itr != path.rend(); ++itr) {
			cout<<*itr<<"->";
		}
	}
}
