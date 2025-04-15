#include <iostream>
using namespace std;

class Node {
public:
    int data;
    Node *next;
};

class Queue {
private:
    Node *head;
    Node *tail;
public:
    Queue() { head = tail = NULL; }
    ~Queue();

    bool empty();       // check if the queue is empty or not
    void push(int x);   // add element in tail
    int pop();          // delete element
    int front();        // return head element
    int back();         // return tail element
    int size();         // number of element
    void show();
};

Queue::~Queue() {
    Node *p = head;

    while (head) {
        head = head->next;
        delete p;
        p = head;
    }
}

bool Queue::empty() {
    return head == NULL;
}

void Queue::push(int x) {
    Node *p = new Node;
    p->data = x;
    p->next = NULL;

    if (empty()) 
        head = tail = p;
    else {
        tail->next = p;
        tail = tail->next;     // tail = p
    }
}

int Queue::pop() {
    if (empty()) {
        cout << "Queue is empty" << endl;
        return -1;
    }

    Node *node = head;
    int x = node->data;     
    head = head->next;      // lùi head sau 1 node
    delete node;

    if (head == NULL)       // nếu ban đầu có 1 phần tử thì sau khi xóa phần tử đó => head == NULL => tail == NULL
        tail = NULL;
    return x;
}

int Queue::front() {
    if (empty()) {
        cout << "Queue is empty" << endl;
        return -1;
    }
    return head->data;
}

int Queue::back() {
    if (empty()) {
        cout << "Queue is empty" << endl;
        return -1;
    }
    return tail->data;
}

int Queue::size() {
    Node *p = head;

    int size = 0;
    while (p) {
        size++;
        p = p->next;
    }

    return size;
}

void Queue::show() {
    Node *p = head;

    while (p) {
        cout << p->data << ' ';
        p = p->next;
    }
    cout << endl;
}

int main() {
    Queue q;
    q.pop();
    for (int i = 1; i < 10; i++) {
        q.push(i);
    }

    cout << q.size() << endl;

    q.pop();
    q.pop();
    q.show();
    cout << "Front: " << q.front() << endl;
    cout << "Back: " << q.back() << endl;
}