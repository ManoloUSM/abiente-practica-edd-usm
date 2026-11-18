
# Ambiente de Práctica — Certamen 3 (INF-134 Estructuras de Datos)

Este ambiente está diseñado para que implementes en **código C++ real** todos los ejercicios programables de la guía *Ejercicios de Certamen 3 de Años Anteriores*, utilizando exactamente los mismos TDAs de tus carpetas (`grafos/` y `colasp/`) sin modificar ninguno de tus archivos originales.

---

## Cómo compilar y ejecutar

Abre una terminal en esta carpeta (`practica_certamen3/`) y ejecuta:

```bash
make
./test_certamen
```

O en un solo comando:

```bash
g++ -std=c++11 main.cpp ejercicios.cpp algoritmos_base.cpp colasp.cpp ../grafos/grafo.cpp ../grafos/lista.cpp ../grafos/cola.cpp -o test_certamen && ./test_certamen
```

---

## Estructura de archivos

1. **`ejercicios.cpp` (¡AQUÍ TRABAJAS TÚ!)**: Contiene las plantillas de los **13 problemas de código** de la guía. Busca los bloques `// TODO: Implementa tu código aquí`.
2. **`ejercicios.h`**: Declaraciones y firmas de los 13 ejercicios (incluyendo la clase `Stream` del Ejercicio 17).
3. **`algoritmos_base.h` / `algoritmos_base.cpp`**: Implementaciones listas para usar de `DFS`, `BFS`, `Dijkstra`, `Prim` y `resetearMarcas`, tal como indican las notas de los ejercicios (*"Si necesita emplear algún algoritmo visto en clases, puede emplearlos suponiendo que ya están implementados"*).
4. **`colasp.h` / `colasp.cpp`**:
   - `tColaP` (y su alias `tColaPMax`): Tu TDA de Max-Heap de `colasp/heap.cpp`.
   - `tColaPMin`: Versión Min-Heap con `insertColaP`, `findMin`, `removeMin`, `sizeColaP`.
   - `flotar(arreglo, tamanno, indice)` y `hundir(arreglo, tamanno, indice)`: Funciones libres para Min-Heap basadas en arreglo (para los Ejercicios 12 y 20).
5. **`main.cpp`**: Menú interactivo con casos de prueba automáticos para cada ejercicio.

---

## Guía Rápida de Referencia de los TDAs (Formulario de Clases)

### 1. TDA `tGrafo` (`../grafos/grafo.h`)
- `int G.nVertex()`: Retorna cantidad de vértices $|V|$ (numerados de `0` a `G.nVertex() - 1`).
- `int G.nEdges()`: Retorna cantidad de arcos $|E|$.
- `tVertice G.first(tVertice v)`: Primer vecino de `v` (o `G.nVertex()` si no tiene).
- `tVertice G.next(tVertice v, tVertice w)`: Siguiente vecino de `v` después de `w` (o `G.nVertex()` si no hay más).
- `void G.setEdge(tVertice v1, tVertice v2, int peso)`: Agrega/actualiza arco dirigido `(v1, v2)`.
- `int G.isEdge(tVertice v1, tVertice v2)`: Retorna `1` si existe el arco, `0` si no (*ojo: toma tiempo $O(\text{grado}(v_1))$ en lista de adyacencia*).
- `int G.weight(tVertice v1, tVertice v2)`: Retorna el peso del arco `(v1, v2)`.
- `int G.getMark(tVertice v)` / `void G.setMark(tVertice v, int marca)`: Lee o asigna marca (`NOVISITADO` = 0, `VISITADO` = 1, o cualquier entero).

**Patrón clásico para recorrer los vecinos de `v` en $O(\text{grado}(v))$:**
```cpp
for (tVertice w = G.first(v); w < G.nVertex(); w = G.next(v, w)) {
    // procesar arco (v, w)
}
```

### 2. TDA `tCola` (`../grafos/cola.h`)
- `Q.enqueue(tVertice item)`
- `Q.dequeue()`
- `tVertice Q.frontValue()`
- `int Q.size()`

### 3. TDA `tColaP` / `tColaPMax` y `tColaPMin` (`colasp.h`)
- **Max-Heap (`tColaP` / `tColaPMax`)**:
  - `H.insertColaP(item)`, `H.findMax()`, `H.removeMax()`, `H.sizeColaP()`
  - Acceso interno (Ej. 9): `H.Heap[i]` (indexado de `1` a `H.n`), `H.flotar(i)`, `H.hundir(i)`.
- **Min-Heap (`tColaPMin`)**:
  - `H.insertColaP(item)`, `H.findMin()`, `H.removeMin()`, `H.sizeColaP()`

---

## Lista de Ejercicios Implementables Incluidos

| Ejercicio | Tema | Función a implementar en `ejercicios.cpp` | Complejidad objetivo |
| :---: | :--- | :--- | :---: |
| **1** | Grafos (Digrafo) | `masCitado(tGrafo &G)` | $O(n + m)$ |
| **5** | Grafos (Red social) | `amigosNoComunes(tGrafo &G, tVertice v1, tVertice v2, int &cant)` | $O(n + m)$ |
| **6** | Grafos (Conectividad) | `minimaCantRutas(tGrafo &G)` | $O(n + m)$ |
| **7** | Grafos (Grados en digrafo) | `saturados(tGrafo &G, int &cantSaturados)` | $O(\|V\| + \|E\|)$ |
| **8** | Grafos (Componentes) | `componentesDesconectadas(tGrafo *G)` | $O(\|V\| + \|E\|)$ |
| **9** | Max-Heap | `modificarValorHeap(tColaP &H, int i, tipoElem j)` | $O(\log n)$ |
| **12** | Min-Heap (Arreglo) | `solo_pares(int *arreglo, int &tamanno)` | In-place ($O(1)$ mem) |
| **17** | Dos Heaps (Mediana) | `Stream::insertAndGetMedian(int x)` | $O(\log n)$ |
| **18** | Grafos (Camino más corto) | `asignar_conductor(tVertice pasajero, tGrafo &G, tVertice *cond, int nc)` | Dijkstra |
| **20** | Min-Heap (Arreglo) | `reparar(int *arreglo, int tamanno)` | In-place ($O(1)$ mem) |
| **21** | Grafos (BFS por niveles) | `listar_infectados(tGrafo &G, tVertice infectada, int cd, int &cant)` | $O(\|V\| + \|E\|)$ |
| **23** | Cola de Prioridad | `costoMinimoFusion(int energia[], int n)` | $O(n \log n)$ |
| **24** | Grafos (Recorrido condicional) | `seContagiaTodaLaRegion(tGrafo &G, tVertice comunaInicial, float *grados)` | $O(\|V\| + \|E\|)$ |

*(Los ejercicios 2, 3, 4, 10, 11, 13, 14, 15, 16, 19 y 22 de la guía son de simulación manual de tablas de Hashing, inserción paso a paso en AVL/Heaps o Verdadero y Falso).*

