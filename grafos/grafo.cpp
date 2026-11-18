#include "grafo.h"

tGrafo::tGrafo(int n) {
    listaAd = new tLista[n];
    marcas = new int[n];
    nVertices = n;
    nArcos = 0;
    for (int i = 0; i < n; i++) {
        marcas[i] = NOVISITADO;
    }
}

tGrafo::~tGrafo() {
    delete[] listaAd;
    delete[] marcas;
}

int tGrafo::nVertex() {
    return nVertices;
}

int tGrafo::nEdges() {
    return nArcos;
}

tVertice tGrafo::first(tVertice v) {
    listaAd[v].moveToStart();
    if (listaAd[v].length() == 0) {
        return nVertices;
    }
    tElemLista auxEdge = listaAd[v].getValue();
    return auxEdge.vertex;
}

tVertice tGrafo::next(tVertice v, tVertice w) {
    for (listaAd[v].moveToStart(); listaAd[v].currPos() < listaAd[v].length(); listaAd[v].next()) {
        tElemLista auxEdge = listaAd[v].getValue();
        if (auxEdge.vertex > w) {
            return auxEdge.vertex;
        }
    }
    return nVertices;
}

void tGrafo::setEdge(tVertice v1, tVertice v2, int peso) {
    for (listaAd[v1].moveToStart(); listaAd[v1].currPos() < listaAd[v1].length(); listaAd[v1].next()) {
        tElemLista auxEdge = listaAd[v1].getValue();
        //Si existe actualizamos el peso borrando el elemento de la lista e insertando el nuevo
        if (auxEdge.vertex == v2) {
            listaAd[v1].erase();
            listaAd[v1].insert({v2, peso});
            return;
        }
        //Si visitamos un arco con un vértice mayor, significa que no está
        if (auxEdge.vertex > v2) {
            break;
        }
    }
    listaAd[v1].insert({v2, peso});
    nArcos++;
}

void tGrafo::deleteEdge(tVertice v1, tVertice v2) {
    for (listaAd[v1].moveToStart(); listaAd[v1].currPos() < listaAd[v1].length(); listaAd[v1].next()) {
        tElemLista auxEdge = listaAd[v1].getValue();
        if (auxEdge.vertex == v2) {
            listaAd[v1].erase();
            nArcos --;
            return;
        }
    }
}

int tGrafo::isEdge( tVertice v1, tVertice v2) {
    for (listaAd[v1].moveToStart(); listaAd[v1].currPos() < listaAd[v1].length(); listaAd[v1].next()) {
        tElemLista auxEdge = listaAd[v1].getValue();
        if (auxEdge.vertex == v2) {
            return 1;
        }
        if (auxEdge.vertex > v2) {
            break;
        }
    }
    return 0;
}

int tGrafo::weight(tVertice v1, tVertice v2) {
    for (listaAd[v1].moveToStart(); listaAd[v1].currPos() < listaAd[v1].length(); listaAd[v1].next()) {
        tElemLista auxEdge = listaAd[v1].getValue();
        if (auxEdge.vertex == v2) {
            return auxEdge.weight;
        }
        if (auxEdge.vertex > v2) {
            break;
        }
    }
    return 0;
}

int tGrafo::getMark(tVertice v) {
    return marcas[v];
}

void tGrafo::setMark(tVertice v, int marca) {
    marcas[v] = marca;
}

void tGrafo::printEdges() {
    for(int i = 0; i < nVertices; i++) {
        cout << "Vértice " << i << ":" ;
        listaAd[i].print();
        cout << listaAd[i].length() << endl;
    }
}




