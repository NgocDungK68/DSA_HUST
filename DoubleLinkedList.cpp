#include <iostream>
using namespace std;

class Node {
public:
    int data;
    Node *nextL, *nextR;
};

class DoubleLinkedList {
private:
    Node *head, *tail;
public:
    DoubleLinkedList() { head = tail = NULL; }
    // ~DoubleLinkedList();

    bool IsEmpty();
    Node* InsertLeft(Node *p, int x);
    Node* InsertRight(Node *p, int x);
    void Delete(Node *p);
    Node* Search(int x);
    void Traverse();
};

bool DoubleLinkedList::IsEmpty() {
    return head == NULL;
}

Node* DoubleLinkedList::InsertLeft(Node *p, int x) {
    Node *q = new Node;
    q->data = x;

    if (IsEmpty()) {
        head = tail = q;
        q->nextL = q->nextR = NULL;
    } else if (p == head) {          // Nếu p là node trái ngoài cùng
        q->nextL = NULL;
        q->nextR = p;
        p->nextL = q;
        head = q;
    } else {
        q->nextL = p->nextL;
        q->nextR = p;
        p->nextL->nextR = q;
        p->nextL = q;
    }

    return q;
}

Node* DoubleLinkedList::InsertRight(Node *p, int x) {
    Node *q = new Node;
    q->data = x;

    if (IsEmpty()) {
        head = tail = q;
        q->nextL = q->nextR = NULL;
    } else if (p == tail) {
        q->nextR = NULL;
        q->nextL = p;
        p->nextR = q;
        tail = q;
    } else {
        q->nextL = p;
        q->nextR = p->nextR;
        p->nextR->nextL = q;
        p->nextR = q;
    }

    return q;
}

void DoubleLinkedList::Traverse() {
    Node *p = head;
    while (p) {
        cout << p->data << ' ';
        p = p->nextR;
    }
    cout << endl;
}

int main() {
    DoubleLinkedList list;
    Node *Ele_1 = list.InsertRight(NULL, 1);
    Node *Ele_2 = list.InsertRight(Ele_1, 2);
    Node *Ele_3 = list.InsertRight(Ele_2, 3);
    Node *Ele_4 = list.InsertRight(Ele_3, 4);
    Node *Ele_5 = list.InsertRight(Ele_4, 5);
    Node *Ele_6 = list.InsertRight(Ele_5, 6);
    Node *Ele_7 = list.InsertRight(Ele_6, 7);
    list.Traverse();
    Node *Ele_8 = list.InsertLeft(Ele_4, 17);
    list.Traverse();
    Node *Ele_9 = list.InsertRight(Ele_8, 37);
    list.Traverse();
    Node *Ele_10 = list.InsertLeft(Ele_1, 89);
    list.Traverse();

    return 0;
}

