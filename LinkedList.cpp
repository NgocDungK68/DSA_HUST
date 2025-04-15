#include <iostream>
using namespace std;

class Node {
public:
    int data;
    Node *next;
};

class LinkedList {
private:
    Node *head;
public:
    LinkedList() { head = NULL; }
    ~LinkedList();

    bool IsEmpty();
    int Length();
    Node* Insert(int x);                            // Thêm vào cuối
    Node* InsertAfter(Node *p, int x);
    Node* InsertBefore(Node *p, int x);       
    void Delete(Node *p);                        // Xóa phần tử
    int Search(int x);                        // Tìm kiếm phần tử 
    void Traverse();                          // duyệt danh sách
};

LinkedList::~LinkedList() {
    Node *p = head;
    while (head) {
        head = head->next;
        delete p;
        p = head;
    }
}

bool LinkedList::IsEmpty() {
    return head == NULL;
}

int LinkedList::Length() {
    Node *p = head;
    int len = 0;
    while (p) {
        len++;
        p = p->next;
    }
    return len;
}

Node* LinkedList::Insert(int x) {
    Node *node = new Node;
    node->data = x;
    node->next = NULL;
    
    if (IsEmpty()) {
        head = node;
    } else {
        Node *p = head;
        for (int i = 0; i < Length() - 1; i++)
            p = p->next;                           // dịch p đến node cuối
        p->next = node;
    }

    return node;
}

Node* LinkedList::InsertAfter(Node *p, int x) {
    if (p == NULL) {
        cout << "Null pointer" << endl;
        return NULL;
    }

    Node *q = new Node;
    q->data = x;
        
    if (IsEmpty()) {
        head = q;
        q->next = NULL;
    } else {
        q->next = p->next;
        p->next = q;
    }

    return q;
}

Node* LinkedList::InsertBefore(Node *p, int x) {
    if (p == NULL) {
        cout << "Null pointer" << endl;
        return NULL;
    }

    Node *q = new Node;
    q->data = x;

    if (IsEmpty()) {
        head = q;
        q->next = NULL;
    } else if (p == head) {
        q->next = p;
        head = q;
    } else {
        Node *node = head;
        while (node->next != p)                 // dịch node đến trước p
            node = node->next;
        q->next = node->next;
        node->next = q;
    }

    return q;
}

void LinkedList::Traverse() {
    Node *p = head;
    while (p) {
        cout << p->data << ' ';
        p = p->next;
    }
    cout << endl;
}

void LinkedList::Delete(Node *p) {
    if (p == NULL || head == NULL) {
        cout << "Cannot delete" << endl;
        return;
    }

    if (p == head) {
        head = p->next;
        delete p;
    } else {
        Node *node = head;
        while (node->next != p) 
            node = node->next;
        node->next = p->next;
        delete p;
    }
}

int main() {
    LinkedList list;
    Node *Ele_1 = list.Insert(1);
    Node *Ele_2 = list.Insert(2);
    Node *Ele_3 = list.Insert(3);
    Node *Ele_4 = list.Insert(4);
    Node *Ele_5 = list.Insert(5);
    list.Traverse();

    Node *Ele_6 = list.InsertAfter(Ele_2, 37);
    list.Traverse();
    Node *Ele_7 = list.InsertBefore(Ele_5, 14);
    list.Traverse();
    Node *Ele_8 = list.InsertBefore(Ele_1, 68);
    list.Traverse();
    Node *Ele_9 = list.InsertBefore(Ele_4, 55);
    list.Traverse();
    list.Delete(Ele_4);
    list.Traverse();
    Node *ele_10 = list.InsertAfter(Ele_9, 28);
    list.Traverse();
    cout << list.Length();

    return 0;
}