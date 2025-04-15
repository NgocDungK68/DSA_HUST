#include <iostream>
using namespace std;

class Map {
public:
    int key;
    int value;
};

class List {
private:
    const static int size = 20;
    Map list[size];
};