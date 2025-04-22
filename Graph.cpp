#include <iostream>
using namespace std;

class Node {
public:
    int data;
    Node *next;

    Node() { next = NULL; }
    Node(int data, Node *next) : data(data), next(next) {}
};

class Vertex {
public:
    int data;
    Node *adjNode;
    Vertex *nextVertex;
};

class Graph {
private:
    Vertex *head;
public:
    Graph() { head = NULL; }

    Vertex* addVertex(int data);
    void addEdge(Vertex *v1, Vertex *v2);
    void show();
    void BFS();
};

Vertex* Graph::addVertex(int data) {
    Vertex *newVertex = new Vertex;
    newVertex->data = data;
    newVertex->adjNode = NULL;
    newVertex->nextVertex = NULL;
    
    if (head == NULL)
        head = newVertex;
    else {
        Vertex *v = head;
        while (v->nextVertex)
            v = v->nextVertex;
        v->nextVertex = newVertex;
    }

    return newVertex;
}

void Graph::addEdge(Vertex *v1, Vertex *v2) {
    Node *node1 = new Node(v1->data, NULL);
    Node *node2 = new Node(v2->data, NULL);
    Node *n;

    if (v1->adjNode == NULL) v1->adjNode = node2;
    else {
        n = v1->adjNode;
        while (n->next) n = n->next;
        n->next = node2;
    }
    if (v2->adjNode == NULL) v2->adjNode = node1;
    else {
        n = v2->adjNode;
        while (n->next) n = n->next;
        n->next = node1;
    }
}

void Graph::show() {
    Vertex *v = head;
    while (v) {
        cout << v->data << " : [ ";
        Node *node = v->adjNode;
        while (node) {
            cout << node->data << " ";
            node = node->next;
        }
        cout << "]" << endl;
        v = v->nextVertex;
    }
}

void Graph::BFS() {
    
}

int main() {
    Graph graph;
    Vertex *vertex_1 = graph.addVertex(1);
    Vertex *vertex_2 = graph.addVertex(2);
    Vertex *vertex_3 = graph.addVertex(3);
    Vertex *vertex_4 = graph.addVertex(4);
    Vertex *vertex_5 = graph.addVertex(5);
    Vertex *vertex_6 = graph.addVertex(6);
    Vertex *vertex_7 = graph.addVertex(7);
    graph.addEdge(vertex_1, vertex_2);
    graph.addEdge(vertex_1, vertex_3);
    graph.addEdge(vertex_4, vertex_3);
    graph.addEdge(vertex_7, vertex_1);
    graph.addEdge(vertex_5, vertex_4);
    graph.addEdge(vertex_6, vertex_3);
    graph.addEdge(vertex_7, vertex_6);
    graph.addEdge(vertex_5, vertex_2);
    graph.show();

    return 0;
}