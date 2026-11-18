#include <iostream>

using namespace std;

typedef int tipoElem;

class tColaP {
private:
    tipoElem *Heap;
    int maxSize; //Potencia de 2 idealmente
    int n;
    void flotar(int pos);
    void hundir(int pos);
public:
    tColaP(int max);
    ~tColaP();
    // elimina todos los elementos de una cola de prioridad, dejándola vacía
    void clearColaP();
    // encuentra el máximo elemento del conjunto
    tipoElem findMax();
    // cantidad de elementos en la cola prioridad
    int sizeColaP();
    // elimina el máximo elemento del conjunto
    void removeMax();
    // inserta un elemento “item” en la cola de prioridad
    void insertColaP(tipoElem item);
};

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
    maxSize = max+1;
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
    if (n > 0) {
        return Heap[1];
    }
    else {
        return -1;
    }
    
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
    hundir(1); // Restaurar la propiedad del heap
}

int main() {
    int maxSize;
    cout << "Tamaño máximo del Heap: ";
    cin >> maxSize;
    tColaP cola(maxSize);
    tipoElem elemento;
    int opcion;

    do {
        cout << "\nMenu:" << endl;
        cout << "1. Insertar elemento" << endl;
        cout << "2. Eliminar máximo elemento" << endl;
        cout << "3. Encontrar máximo elemento" << endl;
        cout << "4. Mostrar tamaño" << endl;
        cout << "5. Limpiar"<< endl;
        cout << "6. Salir" << endl;
        cout << "Ingrese su opción: ";
        cin >> opcion;

        switch (opcion) {
            case 1:
                cout << "Ingrese el elemento a insertar: ";
                cin >> elemento;
                cola.insertColaP(elemento);
                break;
            case 2:
                cola.removeMax();
                cout << "Máximo elemento eliminado." << endl;
                break;
            case 3:
                elemento = cola.findMax();
                if (elemento != -1)
                    cout << "El máximo elemento es: " << elemento << endl;
                else
                    cout << "La cola está vacía." << endl;
                break;
            case 4:
                cout << "Tamaño de la cola de prioridad: " << cola.sizeColaP() << endl;
                break;
            case 5:
                cola.clearColaP();
                cout << "Cola de prioridad limpiada." << endl;
                break;
            case 6:
                cout << "Saliendo del programa." << endl;
                break;
            default:
                cout << "Opción inválida. Por favor, ingrese una opción válida." << endl;
        }
    } while (opcion != 6);

}