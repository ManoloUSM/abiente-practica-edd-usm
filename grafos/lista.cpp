#include "lista.h"

tLista::tLista() {
    head = tail = curr = new tNodo;
    head->sig = NULL;
    listSize = 0; pos = 0;
}

void tLista::clear() {
    tNodo *temp = head;
    while (temp != NULL) {
        tNodo *next = temp->sig;
        delete temp;
        temp = next;
    }
    head = tail = curr = NULL;
    listSize = 0;
    pos = 0;
}

// inserta un elemento en la posición actual de la lista
int tLista::insert(tElemLista item) {
    tNodo* aux = curr->sig;
    curr->sig = new tNodo;
    curr->sig->info = item;
    curr->sig->sig = aux;
    if (curr == tail) tail = curr->sig;
    listSize++;
    return pos;
}

tElemLista tLista::erase() {
    /*
     * Modificamos la función para retornar un edge
     * inválido
     */
    if (curr->sig == NULL) {
        return {-1, -1};
    }
    tNodo* aux = curr->sig;
    tElemLista valor = aux->info;
    curr->sig = curr->sig->sig;
    if (tail == aux) {
        tail = curr;
    }
    delete aux;    
    listSize--;
    return valor;
}

void tLista::moveToStart() { 
    curr = head; 
    pos = 0; 
}
void tLista::moveToEnd() { 
    curr = tail; 
    pos = listSize; 
}
void tLista::prev() {
    tNodo* temp;
    if (curr == head) return;
    temp = head;
    while (temp->sig != curr) temp = temp->sig;
    curr = temp;
    pos--;
}

void tLista::next() { if (curr != tail) { curr = curr->sig; pos++; } }
// destructor, libera la memoria asociada
tLista::~tLista() { 
    clear();
}

int tLista::length() {
    return listSize;
}

int tLista::currPos() {
    return pos;
}

void tLista::moveToPos(int position) {
    if (position >= 0 && position <= listSize) {
        curr = head;
        for(int i = 0; i < position; i++) {
            curr = curr->sig;
        }
    }
    pos = position;
}

tElemLista tLista::getValue() {
    if (curr->sig != NULL)
        return curr->sig->info;
    /*
     * Modificamos la función para retornar un edge
     * inválido
     */
    return {-1, -1};
}

/*
 * Modificamos el print para imprimir el vértice y su peso
 */
void tLista::print() {
    tNodo* temp = head->sig;
    while (temp != NULL) {

        cout << "[" <<temp->info.vertex << "|" << temp->info.weight << "] ";

        temp = temp->sig;
    }
    if (curr == tail) {
        cout << "[]";
    }
    cout << endl;
}
