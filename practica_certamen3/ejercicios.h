#ifndef EJERCICIOS_H
#define EJERCICIOS_H

#include "algoritmos_base.h"
#include "colasp.h"

// ============================================================================
// EJERCICIOS DE GRAFOS (Usando tGrafo, tCola, DFS, BFS, Dijkstra, etc.)
// ============================================================================

// Ejercicio 1: Retorna el artículo (vértice) más citado en tiempo O(n + m)
tVertice masCitado(tGrafo &G);

// Ejercicio 5: Obtiene los amigos de v2 que NO sean amigos de v1 en O(n + m)
// Retorna un arreglo dinámico con los vértices (o puedes guardarlo y poner
// la cantidad encontrada en cantResultados).
tVertice* amigosNoComunes(tGrafo &G, tVertice v1, tVertice v2, int &cantResultados);

// Ejercicio 6: Cantidad mínima de rutas a construir para que no existan
// ciudades aisladas (todo el país quede conectado) en O(n + m).
int minimaCantRutas(tGrafo &G);

// Ejercicio 7: Retorna todos los vértices saturados (grado+(v) - grado-(v) < 0)
// en tiempo O(|V| + |E|). Guarda el tamaño del arreglo retornado en cantSaturados.
tVertice* saturados(tGrafo &G, int &cantSaturados);

// Ejercicio 8: Retorna la cantidad de componentes desconectadas de la red G
// en tiempo O(|V| + |E|). (Nota: firma exacta pedida en el enunciado con puntero).
int componentesDesconectadas(tGrafo *G);

// Ejercicio 18: Retorna el conductor disponible que se encuentra a menor
// distancia del nodo pasajero.
tVertice asignar_conductor(tVertice pasajero, tGrafo &G, tVertice *conductores, int nc);

// Ejercicio 21: Retorna los vértices infectados después de 'cd' días a partir
// de la persona 'infectada' en el día 0. Guarda la cantidad en cantInfectados.
tVertice* listar_infectados(tGrafo &G, tVertice infectada, int cd, int &cantInfectados);

// Ejercicio 24: Determina si se contagia toda la región o no a partir de
// comunaInicial. Un contagio de i a j ocurre si gradosVirus[i] / d_ij > 1.00
// (donde d_ij es el peso del arco entre i y j en G).
bool seContagiaTodaLaRegion(tGrafo &G, tVertice comunaInicial, float *gradosVirus);


// ============================================================================
// EJERCICIOS DE HEAPS / COLAS DE PRIORIDAD
// ============================================================================

// Ejercicio 9: Sustituye el valor actual del nodo i (su enumeración 1..n) por j
// preservando la estructura del max-heap H.
void modificarValorHeap(tColaP &H, int i, tipoElem j);

// Ejercicio 12: Modifica el min-heap en 'arreglo' (1-indexed, tamaño 'tamanno')
// in-place para dejar solamente los números pares. Actualiza 'tamanno' por
// referencia (o retorna el nuevo tamaño) y retorna el puntero al arreglo.
int* solo_pares(int *arreglo, int &tamanno);

// Ejercicio 17: TDA Stream para calcular la mediana dinámica en O(log n)
class Stream {
private:
    int *A;
    unsigned int n; // tamaño actual del arreglo A
    tColaPMax leftMaxHeap;  // heap de máximos (almacena los ceil(n/2) más pequeños)
    tColaPMin rightMinHeap; // heap de mínimos (almacena los floor(n/2) más grandes)
public:
    Stream(int maxCap = 1000);
    ~Stream();
    void cargarEstadoEjemplo(); // Carga el ejemplo del enunciado (n = 15)
    float insertAndGetMedian(int x); // <--- MÉTODO A IMPLEMENTAR
};

// Ejercicio 20: Repara in-place un min-heap donde algunos padres tienen valores
// más altos que alguno de sus hijos.
int* reparar(int *arreglo, int tamanno);

// Ejercicio 23: Retorna el costo mínimo total necesario para fusionar n pociones
// en una única poción usando una cola de prioridad.
int costoMinimoFusion(int energia[], int n);

#endif
