#include <iostream>

using namespace std;

class Node {
public:
    int data;
    Node *LP, *RP;
};

class BinaryTree {
private:
    Node *root;
public:
    BinaryTree() { root = nullptr; }

    void PreOrderTraversal(Node *p);
    void InOrderTraversal(Node *p);
    void PostOrderTraversal(Node *p);
};

void BinaryTree::PreOrderTraversal(Node *p) {
    if (p == nullptr) return;
    cout << p->data << " ";
    PreOrderTraversal(p->LP);
    PreOrderTraversal(p->RP);
}

void BinaryTree::InOrderTraversal(Node *p) {
    if (p == nullptr) return;
    InOrderTraversal(p->LP);
    cout << p->data << " ";
    InOrderTraversal(p->RP);
}

void BinaryTree::PostOrderTraversal(Node *p) {
    if (p == nullptr) return;
    PostOrderTraversal(p->LP);
    PostOrderTraversal(p->RP);
    cout << p->data << " ";
}

int main() {
    BinaryTree t;
    
}