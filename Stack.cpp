#include <iostream>
using namespace std;

class Stack {
private:
    const static int size = 10;      // default size
    int arr[size];
    int n;                           // number of elements
public:
    Stack() { n = 0; }

    bool isEmpty();
    bool isFull();
    void push(int x);
    int pop();
    int top();
    void show();
};

bool Stack::isEmpty() {
    return n == 0;
}

bool Stack::isFull() {
    return n == size;
}

void Stack::push(int x) {
    if (isFull()) {
        cout << "Stack is full";
        return;
    }
    arr[n] = x;
    n++;
}

int Stack::pop() {
    if (isEmpty()) {
        cout << "Stack is Empty";
        return -1;
    }

    n--;
    return arr[n];
}

int Stack::top() {
    if (isEmpty()) {
        cout << "Stack is Empty";
        return -1;
    }
    return arr[n - 1];
}

void Stack::show() {
    for (int i = 0; i < n; i++) {
        cout << arr[i] << ' ';
    }
    cout << endl;
}

int main() {
    Stack st;
    for (int i = 1; i < 9; i++)
        st.push(i);
    st.show();
    cout << st.top() << endl;

    st.pop();
    st.pop();
    st.show();
}