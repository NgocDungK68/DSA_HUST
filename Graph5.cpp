#include <iostream>
#include <vector>
#include <unordered_set>
#include <unordered_map>
#include <queue>
#include <algorithm>
using namespace std;

template <class T>
class Vertex;

template <class T>
class Node {
public:
    Vertex<T> *vertex;
    int weight;
    Node<T> *next;

    Node() { next = NULL; }
    Node(Vertex<T> *vertex) : vertex(vertex) {
        this->weight = 0;
        this->next = NULL;
    }
    Node(Vertex<T> *vertex, int weight) : vertex(vertex), weight(weight) {
        this->next = NULL;
    }
};

template <class T>
class Vertex {
public:
    T data;
    Node<T> *adjNode;
    Vertex<T> *nextVertex;

    Vertex() {}
    Vertex(T data) : data(data) {
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

    void clear();
    Vertex<T>* addVertex(T data);
    bool contains(Vertex<T> *v);
    Vertex<T>* findVertex(T data);
    void addEdge(Vertex<T> *v1, Vertex<T> *v2, int weight);
    void removeVertex(Vertex<T> *v);
    void removeEdge(Vertex<T> *v1, Vertex<T> *v2);
    void updateData(Vertex<T> *v, T newData);
    void updateWeight(Vertex<T> *v1, Vertex<T> *v2, int newWeight);
    void show();
    vector<T> BFS(Vertex<T> *v);
    vector<T> DFS(Vertex<T> *v);
    vector<T> shortestPath(Vertex<T> *start, Vertex<T> *end);
private:
    void removeNode(Vertex<T> *v1, Vertex<T> *v2);
    void DFSUtil(Vertex<T>* v, unordered_set<Vertex<T>*>& visited, vector<T>& result);
    unordered_map<Vertex<T>*, Vertex<T>*> dijkstra(Vertex<T> *start);
};

template <class T>
void Graph<T>::clear() {
    Vertex<T> *temp;
    while (head) {
        temp = head;
        head = head->nextVertex;

        Node<T> *node = temp->adjNode;
        Node<T> *tempNode;
        while (node) {
            tempNode = node;
            node = node->next;
            delete tempNode;
        }

        delete temp;
    }
}

template <class T>
Graph<T>::~Graph() {
    clear();
}

template <class T>
Vertex<T>* Graph<T>::addVertex(T data) {
    Vertex<T> *newVertex = new Vertex(data);
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
    if (!contains(v1) || !contains(v2)) {                      // Dừng thao tác nếu v1 hoặc v2 không thuộc graph
        cout << "One or both vertices do not belong to the graph." << endl;
        return;
    }

    if (v1 == v2) {                                            // v1 trùng v2
        cout << "Cannot add an edge from a vertex to itself." << endl;
        return;
    }

    Node<T> *temp = v1->adjNode;                               // Kiểm tra đã tồn tại cạnh giữa v1 và v2 chưa
    while (temp) {
        if (temp->vertex == v2) {
            cout << "Edge already exists." << endl;
            return;
        }
        temp = temp->next;
    }

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
    if (!contains(v1) || !contains(v2)) {                      // Dừng thao tác nếu v1 hoặc v2 không thuộc graph
        cout << "One or both vertices do not belong to the graph." << endl;
        return;
    }

    if (v1 == v2) {                                            // v1 trùng v2
        cout << "Cannot remove an edge from a vertex to itself." << endl;
        return;
    }

    removeNode(v1, v2);
    removeNode(v2, v1);
}

template <class T>
void Graph<T>::updateData(Vertex<T> *v, T newData) {
    if (!contains(v)) {
        cout << "Vertex does not belong to the graph." << endl;
        return;
    }

    v->data = newData;
}

template <class T>
void Graph<T>::updateWeight(Vertex<T> *v1, Vertex<T> *v2, int newWeight) {
    if (!contains(v1) || !contains(v2)) {                      // Dừng thao tác nếu v1 hoặc v2 không thuộc graph
        cout << "One or both vertices do not belong to the graph." << endl;
        return;
    }

    if (v1 == v2) {                                            // v1 trùng v2
        cout << "Cannot update an edge from a vertex to itself." << endl;
        return;
    }

    Node<T> *temp = v1->adjNode;
    while (temp) {
        if (temp->vertex == v2) {
            temp->weight = newWeight;
            break;
        }
            
        temp = temp->next;
    }

    if (temp == nullptr) {
        cout << "Edge not exists" << endl;
        return;
    }

    temp = v2->adjNode;
    while (temp) {
        if (temp->vertex == v1) {
            temp->weight = newWeight;
            break;
        }

        temp = temp->next;
    }
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
    if (!contains(v)) {
        cout << "Starting vertex does not belong to the graph." << endl;
        return {};
    }
    
    vector<T> result;
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
    if (!contains(v)) {
        cout << "Starting vertex does not belong to the graph." << endl;
        return {};
    }

    vector<T> result;
    unordered_set<Vertex<T>*> visited;
    DFSUtil(v, visited, result);
    return result;
}

template <class T>
unordered_map<Vertex<T>*, Vertex<T>*> Graph<T>::dijkstra(Vertex<T>* start) {
    if (!contains(start)) {
        cout << "Starting vertex does not belong to the graph." << endl;
        return {};
    }

    unordered_map<Vertex<T>*, int> dist;
    unordered_map<Vertex<T>*, Vertex<T>*> previous;


    // Khởi tạo khoảng cách tất cả đỉnh = ∞
    for (Vertex<T>* v = head; v != nullptr; v = v->nextVertex) {
        dist[v] = INT_MAX;
        previous[v] = nullptr;
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
                previous[v] = u;
                pq.push({dist[v], v});
            }
            neighbor = neighbor->next;
        }
    }

    return previous;
}

template <class T>
vector<T> Graph<T>::shortestPath(Vertex<T> *start, Vertex<T> *end) {
    unordered_map<Vertex<T>*, Vertex<T>*> prev = dijkstra(start);
    vector<T> path;
    for (Vertex<T>* v = end; v != nullptr; v = prev[v]) {
        path.push_back(v->data);
    }

    reverse(path.begin(), path.end());
    return path;
}

int main() {
    Graph<string> graph;
    Vertex<string> *vertex_1 = graph.addVertex("HaNoi");
    Vertex<string> *vertex_2 = graph.addVertex("HaiPhong");
    Vertex<string> *vertex_3 = graph.addVertex("Vinh");
    Vertex<string> *vertex_4 = graph.addVertex("QuangNinh");
    Vertex<string> *vertex_5 = graph.addVertex("ThaiBinh");
    Vertex<string> *vertex_6 = graph.addVertex("ThanhHoa");
    Vertex<string> *vertex_7 = graph.addVertex("PhuQuoc");
    Vertex<string> *vertex_8 = graph.addVertex("NamDinh");

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

    return 0;
}