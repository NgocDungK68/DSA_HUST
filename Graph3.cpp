#include <iostream>
#include <vector>
#include <unordered_set>
#include <unordered_map>
#include <queue>
using namespace std;

class Vertex;

class Node {
public:
    Vertex *vertex;
    int weight;
    Node *next;

    Node() { next = NULL; }
    Node(Vertex *vertex) : vertex(vertex) {
        this->weight = 0;
        this->next = NULL;
    }
    Node(Vertex *vertex, int weight) : vertex(vertex), weight(weight) {
        this->next = NULL;
    }
};

class Vertex {
public:
    int data;
    Node *adjNode;
    Vertex *nextVertex;

    Vertex() {}
    Vertex(int data) : data(data) {
        this->adjNode = NULL;
        this->nextVertex = NULL;
    }
};

class Graph {
private:
    Vertex *head;
public:
    Graph() { head = NULL; }

    Vertex* addVertex(int data);
    void addEdge(Vertex *v1, Vertex *v2, int weight);
    void show();
    vector<int> BFS(Vertex *v);
    vector<int> DFS(Vertex *v);
    unordered_map<Vertex*, int> dijkstra(Vertex *v);
private:
    void DFSUtil(Vertex* v, unordered_set<Vertex*>& visited, vector<int>& result);
};

Vertex* Graph::addVertex(int data) {
    Vertex *newVertex = new Vertex(data);
    newVertex->nextVertex = head;
    head = newVertex;
    return newVertex;
}

void Graph::addEdge(Vertex *v1, Vertex *v2, int weight) {
    // Kiểm tra xem v1 và v2 có tồn tại trong đồ thị không ?
    Vertex *v = head;
    bool v1Exists = false, v2Exists = false;

    while (v) {
        if (v == v1) v1Exists = true;
        if (v == v2) v2Exists = true;
        v = v->nextVertex;
    }

    // Nếu một trong hai đỉnh không tồn tại, dừng thao tác và không thực hiện thêm cạnh
    if (!v1Exists || !v2Exists) {
        return;
    }

    Node *node1 = new Node(v1, weight);
    Node *node2 = new Node(v2, weight);

    node2->next = v1->adjNode;
    v1->adjNode = node2;
    node1->next = v2->adjNode;
    v2->adjNode = node1;
}

void Graph::show() {
    Vertex *v = head;
    while (v) {
        cout << v->data << " :  ";
        Node *node = v->adjNode;
        while (node) {
            cout << node->vertex->data << '(' << node->weight << ")\t";
            node = node->next;
        }
        cout << endl;
        v = v->nextVertex;
    }
}

vector<int> Graph::BFS(Vertex *v) {
    vector<int> result;
    if (!v) return result;
    
    unordered_set<Vertex*> visited;
    queue<Vertex*> q;
    visited.insert(v);
    q.push(v);

    while (!q.empty()) {
        Vertex *current = q.front();
        q.pop();
        result.push_back(current->data);

        Node *n = current->adjNode;
        while (n) {
            Vertex *neighbor = n->vertex;
            if (visited.find(neighbor) == visited.end()) {              // neighbor không có trong visited
                visited.insert(neighbor);
                q.push(neighbor);
            }
            n = n->next;
        }
    }

    return result;
}

void Graph::DFSUtil(Vertex* v, unordered_set<Vertex*>& visited, vector<int>& result) {
    if (!v) return;
    visited.insert(v);
    result.push_back(v->data);

    Node* n = v->adjNode;
    while (n) {
        Vertex* neighbor = n->vertex;
        if (visited.find(neighbor) == visited.end()) {
            DFSUtil(neighbor, visited, result);
        }
        n = n->next;
    }
}

vector<int> Graph::DFS(Vertex *v) {
    vector<int> result;
    unordered_set<Vertex*> visited;
    DFSUtil(v, visited, result);
    return result;
}

unordered_map<Vertex*, int> Graph::dijkstra(Vertex* start) {
    unordered_map<Vertex*, int> dist;

    // Khởi tạo khoảng cách tất cả đỉnh = ∞
    for (Vertex* v = head; v != nullptr; v = v->nextVertex) {
        dist[v] = INT_MAX;
    }
    dist[start] = 0;

    priority_queue<pair<int, Vertex*>, vector<pair<int, Vertex*>>, greater<>> pq;
    pq.push({0, start});

    while (!pq.empty()) {
        auto [currentDist, u] = pq.top(); pq.pop();
        if (currentDist > dist[u]) continue;

        Node* neighbor = u->adjNode;
        while (neighbor) {
            Vertex* v = neighbor->vertex;
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
    Graph graph;
    Vertex *vertex_1 = graph.addVertex(1);
    Vertex *vertex_2 = graph.addVertex(2);
    Vertex *vertex_3 = graph.addVertex(3);
    Vertex *vertex_4 = graph.addVertex(4);
    Vertex *vertex_5 = graph.addVertex(5);
    Vertex *vertex_6 = graph.addVertex(6);
    Vertex *vertex_7 = graph.addVertex(7);
    Vertex *vertex_8 = graph.addVertex(8);

    graph.addEdge(vertex_1, vertex_2, 10);
    graph.addEdge(vertex_1, vertex_3, 25);
    graph.addEdge(vertex_4, vertex_3, 6);
    graph.addEdge(vertex_7, vertex_1, 38);
    graph.addEdge(vertex_5, vertex_4, 19);
    graph.addEdge(vertex_6, vertex_3, 45);
    graph.addEdge(vertex_7, vertex_6, 13);
    graph.addEdge(vertex_5, vertex_2, 10);
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
        Vertex* v = pair.first;
        int distance = pair.second;
        cout << "To " << v->data << ": ";
        if (distance == INT_MAX) cout << "∞";
        else cout << distance;
        cout << endl;
    }


    return 0;
}