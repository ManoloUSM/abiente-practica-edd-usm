#ifndef COLAP_H
#define COLAP_H

#include <iostream>

using namespace std;

typedef int tipoElem;

// ============================================================================
// Max-Heap (tColaP / tColaPMax) - Basado exactamente en colasp/heap.cpp
// ============================================================================
class tColaP {
public: // Dejamos Heap, maxSize y n accesibles para el Ejercicio 9 ("Puede asumir que tiene acceso a la estructura que representa al heap")
    tipoElem *Heap;
    int maxSize;
    int n;
    void flotar(int pos);
    void hundir(int pos);

    tColaP(int max = 1000);
    ~tColaP();
    void clearColaP();
    tipoElem findMax();
    int sizeColaP();
    void removeMax();
    void insertColaP(tipoElem item);
    void printHeap();
};

// Alias usado en el Ejercicio 17 (TDA Stream)
typedef tColaP tColaPMax;

// ============================================================================
// Min-Heap (tColaPMin) - Análogo a tColaP pero para mínimos (Ejercicios 17 y 23)
// ============================================================================
class tColaPMin {
public:
    tipoElem *Heap;
    int maxSize;
    int n;
    void flotar(int pos);
    void hundir(int pos);

    tColaPMin(int max = 1000);
    ~tColaPMin();
    void clearColaP();
    tipoElem findMin();
    int sizeColaP();
    void removeMin();
    void insertColaP(tipoElem item);
    void printHeap();
};

// ============================================================================
// Funciones auxiliares de arreglo para Min-Heap (Ejercicios 12 y 20)
// ============================================================================
// En los ejercicios 12 y 20 se indica que puede suponer como implementadas:
//   flotar(arreglo, tamanno, indice)
//   hundir(arreglo, tamanno, indice)
// para un min-heap basado en arreglo (indexado desde 1 hasta tamanno).
void flotar(int *arreglo, int tamanno, int indice);
void hundir(int *arreglo, int tamanno, int indice);

#endif
