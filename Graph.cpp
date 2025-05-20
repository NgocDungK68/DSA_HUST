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
struct DijkstraResult {
    unordered_map<Vertex<T>*, int> dist;
    unordered_map<Vertex<T>*, Vertex<T>*> previous;
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
    vector<Vertex<T>*> shortestPath(Vertex<T> *start, Vertex<T> *end);
    int shortestDistance(Vertex<T> *start, Vertex<T> *end);
private:
    void removeNode(Vertex<T> *v1, Vertex<T> *v2);
    void DFSUtil(Vertex<T>* v, unordered_set<Vertex<T>*>& visited, vector<T>& result);
    DijkstraResult<T> dijkstra(Vertex<T> *start);
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
DijkstraResult<T> Graph<T>::dijkstra(Vertex<T>* start) {
    DijkstraResult<T> result;
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
    
    result.dist = dist;
    result.previous = previous;

    return result;
}

template <class T>
vector<Vertex<T>*> Graph<T>::shortestPath(Vertex<T> *start, Vertex<T> *end) {
    if (!contains(start)) {
        cout << "Starting vertex does not belong to the graph." << endl;
        return {};
    }

    if (!contains(end)) {
        cout << "Ending vertex does not belong to the graph." << endl;
        return {};
    }

    DijkstraResult<T> result = dijkstra(start);
    unordered_map<Vertex<T>*, Vertex<T>*> prev = result.previous;
    vector<Vertex<T>*> path;

    if (prev[end] == nullptr && end != start) {           // xử lý đỉnh lẻ
        cout << "No path exists" << endl;
        return {};
    }
        
    for (Vertex<T>* v = end; v != nullptr; v = prev[v]) {
        path.push_back(v);
    }

    reverse(path.begin(), path.end());
    return path;
}

template <class T>
int Graph<T>::shortestDistance(Vertex<T> *start, Vertex<T> *end) {
    if (!contains(start)) {
        cout << "Starting vertex does not belong to the graph." << endl;
        return {};
    }

    if (!contains(end)) {
        cout << "Ending vertex does not belong to the graph." << endl;
        return {};
    }

    DijkstraResult<T> result = dijkstra(start);
    unordered_map<Vertex<T>*, int> dist = result.dist;

    if (dist[end] == INT_MAX) {          // Kiểm tra tồn tại đường đi từ start đến end không
        cout << "No path exists." << endl;
        return -1;  
    }

    return dist[end];
}

int main() {
    // Khởi tạo đồ thị
    Graph<string> graph;

    // Thêm đỉnh
    Vertex<string> *v1 = graph.addVertex("HaNoi");
    Vertex<string> *v2 = graph.addVertex("VinhPhuc");
    Vertex<string> *v3 = graph.addVertex("HoaBinh");
    Vertex<string> *v4 = graph.addVertex("HaNam");
    Vertex<string> *v5 = graph.addVertex("NamDinh");
    Vertex<string> *v6 = graph.addVertex("BacNinh");
    Vertex<string> *v7 = graph.addVertex("ThaiBinh");
    Vertex<string> *v8 = graph.addVertex("HaiDuong");
    Vertex<string> *v9 = graph.addVertex("HaiPhong");
    Vertex<string> *v10 = graph.addVertex("QuanhNinh");
    
    // Thêm cạnh
    graph.addEdge(v1, v2, 55);
    graph.addEdge(v1, v3, 75);
    graph.addEdge(v1, v4, 50);
    graph.addEdge(v1, v5, 90);
    graph.addEdge(v1, v6, 30);
    graph.addEdge(v1, v7, 120);
    graph.addEdge(v1, v8, 60);
    graph.addEdge(v1, v9, 100);
    graph.addEdge(v1, v10, 130);
    graph.addEdge(v3, v4, 90);
    graph.addEdge(v4, v5, 30);
    graph.addEdge(v5, v7, 30);
    graph.addEdge(v5, v8, 90);
    graph.addEdge(v7, v6, 100);
    graph.addEdge(v7, v9, 35);
    graph.addEdge(v9, v10, 110);
    graph.addEdge(v10, v8, 150);

    // Kiểm tra đỉnh có tồn tại trong đồ thị không
    if (graph.contains(v1)) cout << "Vertex exists" << endl;
    else cout << "Vertex not exists" << endl;

    cout << "---------------------------------------------\n";

    // Duyệt theo chiều rộng
    cout << "BFS from Ha Noi: ";
    vector<string> bfs = graph.BFS(v1);
    for (string i : bfs) cout << i << "   ";
    cout << endl;

    cout << "---------------------------------------------\n";

    // Duyệt theo chiều sâu
    cout << "DFS from HaNoi: ";
    vector<string> dfs = graph.DFS(v1);
    for (string i : dfs) cout << i << "   ";
    cout << endl;

    cout << "---------------------------------------------\n";

    // Đường đi ngắn nhất
    cout << "Shortest path from Nam Dinh to Quanh Ninh: ";
    for (Vertex<string> *v : graph.shortestPath(v5, v10))     // Nam Dinh - Quanh Ninh
        cout << v->data << "   ";
    cout << endl;

    cout << "---------------------------------------------\n";

    // Khoảng cách ngắn nhất
    cout << "Shortest distance from Nam Dinh to Quanh Ninh: " << graph.shortestDistance(v5, v10);
    cout << endl;

    cout << "---------------------------------------------\n";

    graph.findVertex("HaNoi");         // Tìm đỉnh
    graph.removeVertex(v4);            // Xóa đỉnh
    graph.removeEdge(v1, v7);          // Xóa cạnh
    graph.updateData(v10, "LangSon");  // Cập nhật nội dung một đỉnh
    graph.updateWeight(v1, v10, 300);  // Cập nhật trọng số một cạnh

    // Giải phóng bộ nhớ
    graph.clear();

    cout << "---------------------------------------------\n";

    return 0;
}