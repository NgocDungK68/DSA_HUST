#include <iostream>
#include <vector>
#include <unordered_set>
#include <unordered_map>
#include <queue>
using namespace std;

template <class T>
class Vertex;

template <class T>
class Node {
public:
    Vertex<T> *vertex;
    int weight;
    Node<T> *next;

    Node<T>() { next = NULL; }
    Node<T>(Vertex<T> *vertex) : vertex(vertex) {
        this->weight = 0;
        this->next = NULL;
    }
    Node<T>(Vertex<T> *vertex, int weight) : vertex(vertex), weight(weight) {
        this->next = NULL;
    }
};

template <class T>
class Vertex {
public:
    T data;
    Node<T> *adjNode;
    Vertex<T> *nextVertex;

    Vertex<T>() {}
    Vertex<T>(T data) : data(data) {
        this->adjNode = NULL;
        this->nextVertex = NULL;
    }
};

template <class T>
class Graph {
private:
    Vertex<T> *head;
public:
    Graph() { head = NULL; }
    ~Graph();

    Vertex<T>* addVertex(T data);
    bool contains(Vertex<T> *v);
    Vertex<T>* findVertex(T data);
    void addEdge(Vertex<T> *v1, Vertex<T> *v2, int weight);
    void removeVertex(Vertex<T> *v);
    void removeEdge(Vertex<T> *v1, Vertex<T> *v2);
    void show();
    vector<T> BFS(Vertex<T> *v);
    vector<T> DFS(Vertex<T> *v);
    unordered_map<Vertex<T>*, int> dijkstra(Vertex<T> *v);
private:
    void removeNode(Vertex<T> *v1, Vertex<T> *v2);
    void DFSUtil(Vertex<T>* v, unordered_set<Vertex<T>*>& visited, vector<T>& result);
};

template <class T>
Graph<T>::~Graph() {
    
}

template <class T>
Vertex<T>* Graph<T>::addVertex(T data) {
    Vertex<T> *newVertex = new Vertex<T>(data);
    newVertex->nextVertex = head;
    head = newVertex;
    return newVertex;
}

template <class T>
bool Graph<T>::contains(Vertex<T> *v) {
    Vertex<T> *temp = head;

    while (temp) {
        if (temp == v) return true;
        temp = temp->nextVertex;
    }
    
    return false;
}

template <class T>
Vertex<T>* Graph<T>::findVertex(T data) {
    Vertex<T> *temp = head;
    while (temp) {
        if (temp->data == data) 
            return temp;
        temp = temp->nextVertex;
    }
    return nullptr;
}

template <class T>
void Graph<T>::addEdge(Vertex<T> *v1, Vertex<T> *v2, int weight) {
    if (!contains(v1) || !contains(v2)) return;    // Dừng thao tác nếu v1 hoặc v2 không thuộc graph

    Node<T> *node1 = new Node(v1, weight);
    Node<T> *node2 = new Node(v2, weight);

    node2->next = v1->adjNode;
    v1->adjNode = node2;
    node1->next = v2->adjNode;
    v2->adjNode = node1;
}

template <class T>
void Graph<T>::removeNode(Vertex<T> *v1, Vertex<T> *v2) {
    Node<T> *node = v1->adjNode;
    
    if (node->vertex == v2) {
        v1->adjNode = v1->adjNode->next;
        delete node;
        return;
    }

    while (node->next) {
        if (node->next->vertex == v2) {
            Node<T> *temp = node->next;
            node->next = node->next->next;
            delete temp;
            break;
        }
        node = node->next;
    }
}

template <class T>
void Graph<T>::removeVertex(Vertex<T> *v) {
    Vertex<T> *temp = head;

    if (temp == v) {
        Node<T> *node = temp->adjNode;
        while (node) {
            removeNode(node->vertex, v);    // xóa v khỏi danh sách đỉnh kề
            node = node->next;
        }

        head = temp->nextVertex;
        delete v;
        return;
    }
    
    while (temp->nextVertex) {
        if (temp->nextVertex == v) {
            Node<T> *node = v->adjNode;
            while (node) {
                removeNode(node->vertex, v);    // xóa v khỏi danh sách đỉnh kề
                node = node->next;
            }

            temp->nextVertex = temp->nextVertex->nextVertex;
            delete v;                           // xóa v
            return;
        }

        temp = temp->nextVertex;
    }
}

template <class T>
void Graph<T>::removeEdge(Vertex<T> *v1, Vertex<T> *v2) {
    if (!contains(v1) || !contains(v2)) return;    // Dừng thao tác nếu v1 hoặc v2 không thuộc graph
    removeNode(v1, v2);
    removeNode(v2, v1);
}

template <class T>
void Graph<T>::show() {
    Vertex<T> *v = head;
    while (v) {
        cout << v->data << " :  ";
        Node<T> *node = v->adjNode;
        while (node) {
            cout << node->vertex->data << '(' << node->weight << ")\t";
            node = node->next;
        }
        cout << endl;
        v = v->nextVertex;
    }
}

template <class T>
vector<T> Graph<T>::BFS(Vertex<T> *v) {
    vector<T> result;
    if (!v) return result;
    
    unordered_set<Vertex<T>*> visited;
    queue<Vertex<T>*> q;
    visited.insert(v);
    q.push(v);

    while (!q.empty()) {
        Vertex<T> *current = q.front();
        q.pop();
        result.push_back(current->data);

        Node<T> *n = current->adjNode;
        while (n) {
            Vertex<T> *neighbor = n->vertex;
            if (visited.find(neighbor) == visited.end()) {              // neighbor không có trong visited
                visited.insert(neighbor);
                q.push(neighbor);
            }
            n = n->next;
        }
    }

    return result;
}

template <class T>
void Graph<T>::DFSUtil(Vertex<T>* v, unordered_set<Vertex<T>*>& visited, vector<T>& result) {
    if (!v) return;
    visited.insert(v);
    result.push_back(v->data);

    Node<T>* n = v->adjNode;
    while (n) {
        Vertex<T>* neighbor = n->vertex;
        if (visited.find(neighbor) == visited.end()) {
            DFSUtil(neighbor, visited, result);
        }
        n = n->next;
    }
}

template <class T>
vector<T> Graph<T>::DFS(Vertex<T> *v) {
    vector<T> result;
    unordered_set<Vertex<T>*> visited;
    DFSUtil(v, visited, result);
    return result;
}

template <class T>
unordered_map<Vertex<T>*, int> Graph<T>::dijkstra(Vertex<T>* start) {
    unordered_map<Vertex<T>*, int> dist;

    // Khởi tạo khoảng cách tất cả đỉnh = ∞
    for (Vertex<T>* v = head; v != nullptr; v = v->nextVertex) {
        dist[v] = INT_MAX;
    }
    dist[start] = 0;

    priority_queue<pair<int, Vertex<T>*>, vector<pair<int, Vertex<T>*>>, greater<>> pq;
    pq.push({0, start});

    while (!pq.empty()) {
        auto [currentDist, u] = pq.top(); pq.pop();
        if (currentDist > dist[u]) continue;

        Node<T>* neighbor = u->adjNode;
        while (neighbor) {
            Vertex<T>* v = neighbor->vertex;
            int weight = neighbor->weight;

            if (dist[v] > dist[u] + weight) {
                dist[v] = dist[u] + weight;
                pq.push({dist[v], v});
            }
            neighbor = neighbor->next;
        }
    }

    return dist;
}

int main() {
    Graph<int> graph;
    Vertex<int> *vertex_1 = graph.addVertex(1);
    Vertex<int> *vertex_2 = graph.addVertex(2);
    Vertex<int> *vertex_3 = graph.addVertex(3);
    Vertex<int> *vertex_4 = graph.addVertex(4);
    Vertex<int> *vertex_5 = graph.addVertex(5);
    Vertex<int> *vertex_6 = graph.addVertex(6);
    Vertex<int> *vertex_7 = graph.addVertex(7);
    Vertex<int> *vertex_8 = graph.addVertex(8);

    graph.addEdge(vertex_1, vertex_2, 10);
    graph.addEdge(vertex_1, vertex_3, 25);
    graph.addEdge(vertex_4, vertex_3, 6);
    graph.addEdge(vertex_7, vertex_1, 38);
    graph.addEdge(vertex_5, vertex_4, 19);
    graph.addEdge(vertex_6, vertex_3, 45);
    graph.addEdge(vertex_7, vertex_6, 13);
    graph.addEdge(vertex_5, vertex_2, 10);
    cout << "-------------------------------\n";
    graph.show();
    cout << "-------------------------------\n";

    graph.removeVertex(vertex_3);
    graph.show();
    cout << "-------------------------------\n";
    graph.removeEdge(vertex_5, vertex_2);
    graph.show();

    cout << "\nBFS from vertex 1: ";
    vector<int> bfs = graph.BFS(vertex_1);
    for (int i : bfs) cout << i << " ";

    cout << "\nDFS from vertex 1: ";
    vector<int> dfs = graph.DFS(vertex_1);
    for (int i : dfs) cout << i << " ";
    cout << endl;
    
    auto result = graph.dijkstra(vertex_1);

    for (auto& pair : result) {
        Vertex<int>* v = pair.first;
        int distance = pair.second;
        cout << "To " << v->data << ": ";
        if (distance == INT_MAX) cout << "INF";
        else cout << distance;
        cout << endl;
    }

    return 0;
}