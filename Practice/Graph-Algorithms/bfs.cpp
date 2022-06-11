#include <iostream>
#include <cstdlib>
#include <vector>
using namespace std;

class Queue {
	struct Node {
		int data;
		Node *next;
	};
	Node *front, *back;
	
	public:
	Queue() {
		front = back = NULL;
	}
	int frontEle() {
		if(front != NULL)
			return front->data;
		return -1;
	}
	int pop_front()	 {
		if(front != NULL) {
			int data = front->data;
			Node *next = front->next;
			delete front;
			if(front == back) {
				front = back = NULL;
			} else {
				front = next;	
			}
			return data;
		}
	}
	
	void push_back(int data) {
		Node *newNode = new Node();
		newNode->data = data;
		newNode->next = NULL;
		
		if(front == NULL) {
			front = newNode;
		}
		if(back != NULL) {
			back -> next = newNode;
		}
		back = newNode;
	}
	
	void print() {
		cout<<"Queue Internals : "<<endl;
		
		if(front == NULL && back == NULL) {
			cout<<"Queue Empty";
		} else {
			if(front == NULL) {
				cout<<"Front is NULL"<<endl;
			} else {
				cout<<"Front is pointing to "<<front->data<<endl;
			}
		
			if(back == NULL) {
				cout<<"Back is NULL"<<endl;
			} else {
				cout<<"Back is pointing to "<<back->data<<endl;
			}
			Node *itr = front;
			while(itr != NULL) {
				cout<<itr->data<<"|";
				itr = itr->next;
			}	
		}
		
		cout<<endl;
	}
	
	bool isEmpty() {
		if(back == NULL && front == NULL) {
			return true;
		}
		return false;
	}
	
	~Queue() {
		Node *itr = front;
		Node *temp;
		while(itr != back) {
			temp = itr->next;
			delete itr;
			itr = temp;
		}
		front = NULL;
		back = NULL;		
	}
};

class GraphWithEdgeList {
	int V;
	
	public:
		struct Edge {
			int src, dest;
		};
		typedef Edge ListItem;
		typedef vector<ListItem> EdgeList;
		typedef vector<int> VertexList;
	
		GraphWithEdgeList(int vertices) {
			V = vertices;
			list = EdgeList();
		}
		
		void print() {
			cout<<"Graph has following edges : "<<endl;
			
			for(EdgeList::iterator itr = list.begin(); itr < list.end(); ++itr) {
				cout<<itr->src<<" -> "<<itr->dest;
				cout<<endl;
			}
		}
		
		void addEdge(int src, int dest) {
			ListItem edge;
			edge.src = src;
			edge.dest = dest;
			list.push_back(edge);
		}
		
		Edge getEdgeByIndex(int index) {
			return list[index];
		}
		
		VertexList getNeighborFor(int vertex) {
			vector<int> neigbors;
			
			for(EdgeList::iterator itr = list.begin(); itr < list.end(); ++itr) {
				if(itr->src == vertex) {
					neigbors.push_back(itr->dest);
				}
				
				if(itr->dest == vertex) {
					neigbors.push_back(itr->src);
				}
			}
			return neigbors;
		}
	private:
	EdgeList list;
};

class GraphWithAdjancencyList {
	typedef vector<int> ListItem;
	typedef vector<ListItem> AdjancencyList;
	AdjancencyList list;
	public:
		GraphWithAdjancencyList(int vertices) {
			list = AdjancencyList(vertices, ListItem());
		}
		
		void print() {
			cout<<"Graph is "<<endl;
			
			for(AdjancencyList::iterator itr = list.begin(); itr < list.end(); ++itr) {
				cout<<"List for "<<distance(list.begin(), itr)<<" is : ";
				for(ListItem::iterator item = itr->begin(); item < itr->end(); ++item) {
					cout<<*item<<",";
				}
				cout<<endl;
			}
		}
		
		void addEdge(int src, int dest) {
			ListItem::iterator srcStartItr = list[src].begin();
			ListItem::iterator srcEndItr = list[src].end();

			bool edgeExists = false;
			
			while(srcStartItr < srcEndItr) {
				if(*srcStartItr == dest) {
					edgeExists = true;
				}
				++srcStartItr;
			}
			if(!edgeExists) {
				list[src].push_back(dest);
				list[dest].push_back(src);
			}
		}
};

int main() {
	//Test Queue
	Queue queue;
	queue.print();
	queue.pop_front();
	queue.print();
	queue.push_back(1);
	queue.print();
	queue.pop_front();
	queue.print();
	queue.pop_front();
	queue.print();
	queue.push_back(2);
	queue.print();
	queue.push_back(3);
	queue.print();
	queue.pop_front();
	queue.print();
	queue.pop_front();
	queue.print();
	
	for(int i = 0; i < 10; ++i) {
		queue.push_back(i);
	}
	queue.print();
	
	queue.pop_front();
	queue.print();
	queue.push_back(10);
	queue.print();
	for(int i = 0; i < 10; ++i) {
		queue.pop_front();
	}
	queue.print();
	queue.pop_front();
	queue.print();


	//Test Graph
	
	GraphWithEdgeList graph(10);
	graph.print();
	graph.addEdge(0, 3);
	graph.addEdge(0, 1);
	graph.addEdge(1, 2);
	graph.print();
	//Run BFS
	
	Queue bfsQueue;
	vector<int> visited(10, -1);
	int connectedComp = 0;
	for(int i = 0; i < 10; ++i) {
		
		if(visited[i] == -1) {
		
			bfsQueue.push_back(i);
			while(!bfsQueue.isEmpty()) {
				GraphWithEdgeList::VertexList list = graph.getNeighborFor(bfsQueue.frontEle());
				visited[bfsQueue.frontEle()] = connectedComp;
				bfsQueue.pop_front();
				
				for(GraphWithEdgeList::VertexList::iterator itr = list.begin(); itr != list.end(); ++itr) {
					if(visited[*itr] == -1)
						bfsQueue.push_back(*itr);
				}
				bfsQueue.print();
			}
			++connectedComp;
		}
	}
	
	cout<<"Number of connected components : "<<connectedComp<<endl;

	return 0;
	
}
