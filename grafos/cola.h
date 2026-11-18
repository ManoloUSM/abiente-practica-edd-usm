#include <iostream>

using namespace std;

typedef int tVertice;
typedef tVertice tElemCola;

#define MAXSIZE 1000

class tCola {
private:
    int frente, final;
    int tam;
    int maxSize;
    tElemCola* queueArray;
public:
    tCola();
    ~tCola();
    void clear();// reinicializa una cola como vacía
    int enqueue(tElemCola item);// inserta un elemento al final de la cola
    void dequeue();// elimina el elemento que está en el frente cola
    tElemCola frontValue();// retorna una copia del elemento que está en el frente de la cola
    int size();// retorna el tamaño de una cola
};