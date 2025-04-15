#include <iostream>
using namespace std;

class Node {
public:
    int data;
    Node *next;
};

class Stack {
private:
    Node *Top;
public:
    Stack() { Top = NULL; }

    bool isEmpty();
    void push(int x);
    int pop();
};

bool Stack::isEmpty() {
    return Top == NULL;
}

void Stack::push(int x) {
    Node *p = new Node;
    p->data = x;
    p->next = NULL;

    if (isEmpty()) 
        Top = p;
    else {
        p->next = Top;
        Top = p;
    }
}

int Stack::pop() {
    if (isEmpty()) {
        cout << "Empty stack" << endl;
        return -1;
    }
    Node *p = Top;
    int x = p->data;
    Top = Top->next;
    delete p;
    return x;
}