#include "grafo.h"
#include <iostream>

using namespace std;

//Valor lo suficientemente grande
#define INFINITO 9999

void visitar(tGrafo &G, tVertice v) {
    cout << "Visité el vértice " << v << endl;
}

void DFS(tGrafo& G, tVertice v) {
    tVertice w;
    visitar(G, v);
    G.setMark(v, VISITADO);
    for (w = G.first(v); w < G.nVertex(); w = G.next(v, w))
        if (G.getMark(w) == NOVISITADO) 
            DFS(G, w);
}

int minVertex(tGrafo &G, int* D) {
    tVertice v = -1;
    for(int i = 0; i < G.nVertex(); i++) {
        if (G.getMark(i) == NOVISITADO) {
            if (v == -1 || D[i] < D[v]) {
                v = i;
            }
        }
    }
    return v;
}

void Dijkstra(tGrafo& G, int *D, tVertice s) {
    tVertice v, w;
    int i;
    D[s] = 0; //asume D[i != s] = INFINITO
    for (int i = 0; i < 5; i++) {
        cout << D[i] << " ";
    }
    cout << endl;
    for (i = 0; i < G.nVertex(); i++) {
        v = minVertex(G, D); // obtiene vértice no visitado con mínima distancia a s
        if (D[v] == INFINITO)     // sólo vértices inalcanzables por procesar
            return;               
        G.setMark(v, VISITADO);  // marca vértice actual como visitado
        for (w = G.first(v); w < G.nVertex(); w = G.next(v, w))
            if (D[w] > (D[v] + G.weight(v, w))) 
                D[w] = D[v] + G.weight(v, w);
        
        for (int i = 0; i < 5; i++) {
            cout << D[i] << " ";
        }
        cout << endl;
    }
}

void AgregarArcoArbol(tVertice v1, tVertice v2) {
    cout << "Se añade arco (" << v1 << ", " << v2 << ")" << endl;
}

void Prim(tGrafo& G, int *D, tVertice s) {
    tVertice* V = new tVertice[G.nVertex()];       // almacena el vértice más cercano
    tVertice v, w;
    D[s] = 0; //asume D[i != s] = INFINITO
    for (int i = 0; i < G.nVertex(); i++) {
        v = minVertex(G, D);      // vértice no visitado con mínima distancia a s
        G.setMark(v, VISITADO);  // marca vértice actual como visitado
        if (v != s) AgregarArcoArbol(V[v], v);
        if (D[v] == INFINITO) return;
        for (w = G.first(v); w < G.nVertex(); w = G.next(v, w))
            if (D[w] > G.weight(v, w)) {
                D[w] = G.weight(v, w); V[w] = v;
            }
    }
    delete[] V;
}

int main() {
    // Crear un grafo con 6 nodos
    tGrafo grafo(6);

    // Agregar arcos al grafo
    grafo.setEdge(0, 2, 1);
    grafo.setEdge(2, 0, 1);
    grafo.setEdge(0, 4, 1);
    grafo.setEdge(4, 0, 1);
    grafo.setEdge(1, 2, 1);
    grafo.setEdge(2, 1, 1);
    grafo.setEdge(1, 5, 1);
    grafo.setEdge(5, 1, 1);
    grafo.setEdge(2, 3, 1);
    grafo.setEdge(3, 2, 1);
    grafo.setEdge(2, 5, 1);
    grafo.setEdge(5, 2, 1);
    grafo.setEdge(3, 5, 1);
    grafo.setEdge(5, 3, 1);
    grafo.setEdge(4, 5, 1);
    grafo.setEdge(5, 4, 1);

    grafo.printEdges();

    DFS(grafo, 0);
    /*
     * Implementar BFS
     */
    
    tGrafo grafo2(5);
    grafo2.setEdge(0,1,10);
    grafo2.setEdge(0,2,3);
    grafo2.setEdge(0,3,20);
    grafo2.setEdge(1,3,5);
    grafo2.setEdge(2,1,2);
    grafo2.setEdge(2,4,15);
    grafo2.setEdge(3,4,11);

    int* D = new int[5];
    for (int i = 0; i < 5; i++) {
        D[i] = INFINITO;
    }
    Dijkstra(grafo2, D, 1);
    for (int i = 0; i < 5; i++) {
        cout << D[i] << " ";
    }
    cout << endl;
    delete[] D;
    
    tGrafo grafo3(6);
    //Prim
    grafo3.setEdge(0, 1, 4);
    grafo3.setEdge(1, 0, 4);
    grafo3.setEdge(0, 2, 8);
    grafo3.setEdge(2, 0, 8);
    grafo3.setEdge(0, 3, 6);
    grafo3.setEdge(3, 0, 6);
    grafo3.setEdge(0, 5, 4);
    grafo3.setEdge(5, 0, 4);
    grafo3.setEdge(1, 2, 3);
    grafo3.setEdge(2, 1, 3);
    grafo3.setEdge(2, 3, 5);
    grafo3.setEdge(3, 2, 5);
    grafo3.setEdge(2, 5, 5);
    grafo3.setEdge(5, 2, 5);
    grafo3.setEdge(3, 4, 9);
    grafo3.setEdge(4, 3, 9);
    grafo3.setEdge(3, 5, 3);
    grafo3.setEdge(5, 3, 3);
    grafo3.setEdge(4, 5, 3);
    grafo3.setEdge(5, 4, 3);
    //Kruskal
    /*
    grafo3.setEdge(0, 1, 6);
    grafo3.setEdge(1, 0, 6);
    grafo3.setEdge(0, 2, 8);
    grafo3.setEdge(2, 0, 8);
    grafo3.setEdge(0, 3, 6);
    grafo3.setEdge(3, 0, 6);
    grafo3.setEdge(0, 5, 3);
    grafo3.setEdge(5, 0, 3);
    grafo3.setEdge(1, 2, 5);
    grafo3.setEdge(2, 1, 5);
    grafo3.setEdge(2, 3, 7);
    grafo3.setEdge(3, 2, 7);
    grafo3.setEdge(2, 5, 6);
    grafo3.setEdge(5, 2, 6);
    grafo3.setEdge(3, 4, 2);
    grafo3.setEdge(4, 3, 2);
    grafo3.setEdge(3, 5, 5);
    grafo3.setEdge(5, 3, 5);
    grafo3.setEdge(4, 5, 4);
    grafo3.setEdge(5, 4, 4);
    */
    grafo3.printEdges();

    int* D2 = new int[6];
    for (int i = 0; i < 6; i++) {
        D2[i] = INFINITO;
    }
    Prim(grafo3, D2, 4);
    for (int i = 0; i < 6; i++) {
        cout << D2[i] << " ";
    }
    cout << endl;
    delete[] D2;
    
    return 0;
}