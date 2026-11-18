#include "algoritmos_base.h"

void resetearMarcas(tGrafo &G) {
    for (int i = 0; i < G.nVertex(); i++) {
        G.setMark(i, NOVISITADO);
    }
}

void DFS(tGrafo &G, tVertice v) {
    tVertice w;
    G.setMark(v, VISITADO);
    for (w = G.first(v); w < G.nVertex(); w = G.next(v, w)) {
        if (G.getMark(w) == NOVISITADO) {
            DFS(G, w);
        }
    }
}

void BFS(tGrafo &G, tVertice s) {
    tCola Q;
    tVertice v, w;
    Q.enqueue(s);
    G.setMark(s, VISITADO);
    while (Q.size() != 0) {
        v = Q.frontValue();
        Q.dequeue();
        for (w = G.first(v); w < G.nVertex(); w = G.next(v, w)) {
            if (G.getMark(w) == NOVISITADO) {
                G.setMark(w, VISITADO);
                Q.enqueue(w);
            }
        }
    }
}

int minVertex(tGrafo &G, int *D) {
    tVertice v = -1;
    for (int i = 0; i < G.nVertex(); i++) {
        if (G.getMark(i) == NOVISITADO) {
            if (v == -1 || D[i] < D[v]) {
                v = i;
            }
        }
    }
    return v;
}

void Dijkstra(tGrafo &G, int *D, tVertice s) {
    tVertice v, w;
    for (int i = 0; i < G.nVertex(); i++) {
        D[i] = INFINITO;
        G.setMark(i, NOVISITADO);
    }
    D[s] = 0;
    for (int i = 0; i < G.nVertex(); i++) {
        v = minVertex(G, D);
        if (v == -1 || D[v] == INFINITO)
            return;
        G.setMark(v, VISITADO);
        for (w = G.first(v); w < G.nVertex(); w = G.next(v, w)) {
            if (D[w] > (D[v] + G.weight(v, w))) {
                D[w] = D[v] + G.weight(v, w);
            }
        }
    }
}

void Prim(tGrafo &G, int *D, tVertice s) {
    tVertice *V = new tVertice[G.nVertex()];
    tVertice v, w;
    for (int i = 0; i < G.nVertex(); i++) {
        D[i] = INFINITO;
        G.setMark(i, NOVISITADO);
    }
    D[s] = 0;
    for (int i = 0; i < G.nVertex(); i++) {
        v = minVertex(G, D);
        if (v == -1 || D[v] == INFINITO) break;
        G.setMark(v, VISITADO);
        for (w = G.first(v); w < G.nVertex(); w = G.next(v, w)) {
            if (G.getMark(w) == NOVISITADO && D[w] > G.weight(v, w)) {
                D[w] = G.weight(v, w);
                V[w] = v;
            }
        }
    }
    delete[] V;
}
