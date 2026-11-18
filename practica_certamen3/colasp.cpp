#include "colasp.h"

// ============================================================================
// Implementación de tColaP (Max-Heap)
// ============================================================================
void tColaP::flotar(int pos) {
    while (pos > 1 && Heap[pos] > Heap[pos/2]) {
        tipoElem aux = Heap[pos];
        Heap[pos] = Heap[pos/2];
        Heap[pos/2] = aux;
        pos = pos/2;
    }
}

void tColaP::hundir(int pos) {
    while (2 * pos <= n) {
        int hijoIzq = 2*pos;
        int mayor = hijoIzq;
        if (hijoIzq < n && Heap[hijoIzq+1] > Heap[hijoIzq]) {
            mayor += 1;
        }
        if (Heap[pos] >= Heap[mayor]) {
            break;
        }
        tipoElem aux = Heap[pos];
        Heap[pos] = Heap[mayor];
        Heap[mayor] = aux;
        pos = mayor;
    }
}

tColaP::tColaP(int max) {
    maxSize = max + 1;
    n = 0;
    Heap = new tipoElem[maxSize];
}

tColaP::~tColaP() {
    delete[] Heap;
}

void tColaP::clearColaP() {
    n = 0;
}

tipoElem tColaP::findMax() {
    if (n > 0) return Heap[1];
    return -1;
}

int tColaP::sizeColaP() {
    return n;
}

void tColaP::insertColaP(tipoElem item) {
    if (n == maxSize - 1) {
        cout << "Heap lleno" << endl;
        return;
    }
    n++;
    Heap[n] = item;
    flotar(n);
}

void tColaP::removeMax() {
    if (n == 0) return;
    Heap[1] = Heap[n];
    n--;
    hundir(1);
}

void tColaP::printHeap() {
    cout << "[ X ";
    for (int i = 1; i <= n; i++) {
        cout << Heap[i] << " ";
    }
    cout << "]" << endl;
}

// ============================================================================
// Implementación de tColaPMin (Min-Heap)
// ============================================================================
void tColaPMin::flotar(int pos) {
    while (pos > 1 && Heap[pos] < Heap[pos/2]) {
        tipoElem aux = Heap[pos];
        Heap[pos] = Heap[pos/2];
        Heap[pos/2] = aux;
        pos = pos/2;
    }
}

void tColaPMin::hundir(int pos) {
    while (2 * pos <= n) {
        int hijoIzq = 2*pos;
        int menor = hijoIzq;
        if (hijoIzq < n && Heap[hijoIzq+1] < Heap[hijoIzq]) {
            menor += 1;
        }
        if (Heap[pos] <= Heap[menor]) {
            break;
        }
        tipoElem aux = Heap[pos];
        Heap[pos] = Heap[menor];
        Heap[menor] = aux;
        pos = menor;
    }
}

tColaPMin::tColaPMin(int max) {
    maxSize = max + 1;
    n = 0;
    Heap = new tipoElem[maxSize];
}

tColaPMin::~tColaPMin() {
    delete[] Heap;
}

void tColaPMin::clearColaP() {
    n = 0;
}

tipoElem tColaPMin::findMin() {
    if (n > 0) return Heap[1];
    return -1;
}

int tColaPMin::sizeColaP() {
    return n;
}

void tColaPMin::insertColaP(tipoElem item) {
    if (n == maxSize - 1) {
        cout << "Heap lleno" << endl;
        return;
    }
    n++;
    Heap[n] = item;
    flotar(n);
}

void tColaPMin::removeMin() {
    if (n == 0) return;
    Heap[1] = Heap[n];
    n--;
    hundir(1);
}

void tColaPMin::printHeap() {
    cout << "[ X ";
    for (int i = 1; i <= n; i++) {
        cout << Heap[i] << " ";
    }
    cout << "]" << endl;
}

// ============================================================================
// Funciones libres flotar y hundir sobre arreglo para Min-Heap (Ej. 12 y 20)
// ============================================================================
void flotar(int *arreglo, int tamanno, int indice) {
    (void)tamanno;
    while (indice > 1 && arreglo[indice] < arreglo[indice / 2]) {
        int aux = arreglo[indice];
        arreglo[indice] = arreglo[indice / 2];
        arreglo[indice / 2] = aux;
        indice = indice / 2;
    }
}

void hundir(int *arreglo, int tamanno, int indice) {
    while (2 * indice <= tamanno) {
        int hijoIzq = 2 * indice;
        int menor = hijoIzq;
        if (hijoIzq < tamanno && arreglo[hijoIzq + 1] < arreglo[hijoIzq]) {
            menor += 1;
        }
        if (arreglo[indice] <= arreglo[menor]) {
            break;
        }
        int aux = arreglo[indice];
        arreglo[indice] = arreglo[menor];
        arreglo[menor] = aux;
        indice = menor;
    }
}
