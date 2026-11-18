#ifndef ALGORITMOS_BASE_H
#define ALGORITMOS_BASE_H

#include "../grafos/grafo.h"
#include "../grafos/cola.h"
#include <iostream>

using namespace std;

#define INFINITO 999999

// ============================================================================
// Algoritmos vistos en clases (puedes usarlos directamente en tus ejercicios
// tal como dicen las notas del certamen: "puede emplearlos suponiendo que ya
// están implementados").
// ============================================================================

void resetearMarcas(tGrafo &G);

// Búsqueda en Profundidad (DFS)
void DFS(tGrafo &G, tVertice v);

// Búsqueda en Anchura (BFS)
void BFS(tGrafo &G, tVertice s);

// Vértice no visitado con menor distancia en D
int minVertex(tGrafo &G, int *D);

// Algoritmo de Dijkstra: calcula las distancias mínimas desde 's' hacia todos
// los demás vértices y las guarda en el arreglo D (de tamaño G.nVertex()).
// Nota: Inicializa internamente D[i] = INFINITO, D[s] = 0 y resetea marcas.
void Dijkstra(tGrafo &G, int *D, tVertice s);

// Algoritmo de Prim
void Prim(tGrafo &G, int *D, tVertice s);

#endif
