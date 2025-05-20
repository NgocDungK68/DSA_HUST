#include <iostream>

using namespace std;

class Node {
public:
    int key;
    Node *LP, *RP;
};

class BSearchTree {
private:
    Node *root;
public:
    BSearchTree() { root = nullptr; }
    Node* Search(int key) { Search(root, key); }
    Node* Insert(int key) { Insert(root, key); }
    void Delete(int key) { Delete(root, key); }
private:
    Node* Search(Node *root, int key);
    Node* Insert(Node *root, int key);
    void Delete(Node *root, int key);
};

Node* BSearchTree::Search(Node *root, int key) {
    if (root == nullptr) return nullptr;
    if (key == root->key) return root;
    else if (key < root->key) Search(root->LP, key);
    else Search(root->RP, key);
}

Node* BSearchTree::Insert(Node *root, int key) {
    if (root == nullptr) {
        Node *p = new Node;
        p->key = key;
        p->LP = p->RP = nullptr;
        root = p;
        return p;
    }

    if (key < root->key) Insert(root->LP, key);
    else if (key > root->key) Insert(root->RP, key);
    return nullptr;   // key == root->key
}

void BSearchTree::Delete(Node *root, int key) {
    if (root != nullptr) {
        if (key < root->key) Delete(root->LP, key);
        else if (key > root->key) Delete(root->RP, key);
        else {
            Node *p, *q;
            if (root->LP == nullptr) {         // Xóa nút có cây con phải
                p = root;
                root = root->RP;
            } else if (root->RP == nullptr) {  // Xóa nút có cây con trái
                p = root;
                root = root->LP;
            } else {                           // Xóa nút có hai cây con
                p = root->LP;
                if (p->RP == nullptr) {
                    root->key = p->key;
                    root->LP = p->LP;
                } else {
                    do {
                        q = p;
                        p = p->RP;
                    } while (p->RP != nullptr);
                    root->key = p->key;
                    q->RP = p->LP;
                }
            }
            delete p;
        }
    }
}
