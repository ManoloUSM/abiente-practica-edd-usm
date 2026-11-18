#include <iostream>

using namespace std;

typedef int tVertice;

struct edge {
    tVertice vertex;
    int weight;
};

typedef edge tElemLista;

struct tNodo{
    tElemLista info;
    tNodo* sig;
};

class tLista {
private:
    tNodo* head;
    tNodo* tail;
    tNodo* curr;
    unsigned int listSize;
    unsigned int pos; // posicion actual en la lista
public:
    tLista();
    ~tLista();
    void clear();
    int insert(tElemLista item);
    tElemLista erase();
    void moveToStart();
    void moveToEnd();
    void prev();
    void next();
    int length();
    int currPos();
    void moveToPos(int pos);
    tElemLista getValue();
    void print();
    void printConInfo();
};