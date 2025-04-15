#include <iostream>
using namespace std;

class Node {
public:
    int data;
    Node *LP, *RP, *PP;
};

class BinaryTree {
private:
    Node *T;
public:
    BinaryTree() { T = NULL; }

    void PreOrderTraversal();
    void InOrderTraversal();
    void PostOrderTraversal();
};
