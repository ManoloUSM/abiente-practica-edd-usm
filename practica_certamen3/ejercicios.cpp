#include "ejercicios.h"

// ============================================================================
// EJERCICIO 1: Artículo más citado
// ============================================================================
/*
 * Enunciado:
 * Un grafo dirigido G representa una base de datos con artículos científicos.
 * Existe un arco dirigido desde v1 a v2 sii v1 referencia a v2.
 * Retornar el artículo que sea más referenciado dentro de la base de datos.
 * Tiempo esperado: O(n + m).
 */
tVertice masCitado(tGrafo &G) {
    // TODO: Implementa tu código aquí
    int* A= new int[G.nVertex()];
    for(int i=0;i<G.nVertex();i++){
        A[i]=0;
    }
    for(int i=0;i<G.nVertex();i++){
        for(tVertice w=G.first(i);w<G.nVertex();w=G.next(i,w)){
            A[w]+=1;
        }
    }
    int max=-9999, retorno=0;
    for(int i=0;i<G.nVertex();i++){
        if(A[i]>max){
            max=A[i];
            retorno=i;
        }
    }

    return retorno;
}

// ============================================================================
// EJERCICIO 5: Amigos de v2 que no son amigos de v1 (Facebook)
// ============================================================================
/*
 * Enunciado:
 * Obtener los amigos de v2 que NO sean amigos de v1.
 * Si v1 tiene n amigos y v2 tiene m amigos, el tiempo debe ser O(n + m).
 * Hint: Puedes usar las marcas del grafo (G.setMark / G.getMark) para lograr
 * O(n + m) sin tener que buscar linealmente cada amigo.
 * Guarda en 'cantResultados' cuántos encontraste y retorna un arreglo con ellos.
 */
tVertice* amigosNoComunes(tGrafo &G, tVertice v1, tVertice v2, int &cantResultados) {
    cantResultados = 0;
    tVertice *resultado = new tVertice[G.nVertex()];

    // TODO: Implementa tu código aquí
    /*
    for(tVertice w=G.first(v2);w<G.nVertex();w=G.next(v2,w)){
        for(tVertice o=G.first(v1);o<G.nVertex();o=G.next(v1,w)){
            if(o==w){
                G.setMark()
            }
        }
    }
    return resultado;
    */
}

// ============================================================================
// EJERCICIO 6: Mínima cantidad de rutas para conectar ciudades
// ============================================================================
/*
 * Enunciado:
 * Un país con n ciudades y m > 0 rutas bidireccionales que las conectan.
 * Retornar un entero indicando la cantidad mínima de rutas que deben construirse
 * para que no existan ciudades aisladas (es decir, que todo el grafo sea conexo).
 * Tiempo esperado: O(n + m).
 * Nota: Puedes usar DFS o BFS (ya incluidos en algoritmos_base.h).
 */
int minimaCantRutas(tGrafo &G) {
    // TODO: Implementa tu código aquí
    int n=G.nVertex();
    for(int i=0;i<n;i++){
        G.setMark(i,NOVISITADO);
    }
    int islas=0;
    for(int i=0;i<n;i++){
        if(G.getMark(i)==0){
            islas++;
            DFS(G,i);
        }
    }
    return islas-1;
}

// ============================================================================
// EJERCICIO 7: Vértices saturados en un digrafo
// ============================================================================
/*
 * Enunciado:
 * Dado un digrafo G = (V, E), un vértice v está saturado si:
 *   grado+(v) - grado-(v) < 0   (es decir, gradoSalida(v) < gradoEntrada(v))
 * Retornar todos los vértices saturados del grafo en tiempo O(|V| + |E|).
 * Guarda la cantidad de vértices saturados en 'cantSaturados'.
 */
tVertice* saturados(tGrafo &G, int &cantSaturados) {
    cantSaturados = 0;
    tVertice *resultado = new tVertice[G.nVertex()];
    // TODO: Implementa tu código aquí
    int* entra=new int[G.nVertex()];
    int* sale=new int[G.nVertex()];
    for(int i=0;i<G.nVertex();i++){
        entra[i]=0;
    }
    for(int i=0;i<G.nVertex();i++){
        int contador=0;
        for(tVertice w=G.first(i);w<G.nVertex();w=G.next(i,w)){
            entra[w]++;
            contador++;
        }
        sale[i]=contador;
    }
    for(int i=0;i<G.nVertex();i++){
        if(sale[i]-entra[i]<0){
            resultado[cantSaturados]=i;
            cantSaturados++;
        }
    }
    return resultado;
}

// ============================================================================
// EJERCICIO 8: Componentes desconectadas de una red telefónica
// ============================================================================
/*
 * Enunciado:
 * Grafo no dirigido G con todos los vértices marcados como NOVISITADO inicialmente.
 * Implementar int componentesDesconectadas(tGrafo *G) que retorna la cantidad
 * de componentes conexas (desconectadas entre sí) de la red G en O(|V| + |E|).
 * Nota: Ojo que G se recibe como puntero (usa G->nVertex() o (*G)).
 */
/* NO FUNCIONA LO SIGUIENTE
int componentesDesconectadas(tGrafo *G) {
    int desconectados=0;
    int* entradas= new int[G->nVertex()];
    int* salidas= new int[G->nVertex()];
    for(int i=0; i<G->nVertex(); i++){
        int contador=0;
        for(tVertice w=G->first(i);w<G->nVertex();w=G->next(i,w)){
            entradas[w]++;
            contador++;
        }
        salidas[i]=contador;
    }
    for(int i=0; i<G->nVertex(); i++){
        if(entradas[i]==0 && salidas[i]==0){
            desconectados++;
        }
    }
    return desconectados;
}
    */
int componentesDesconectadas(tGrafo *G) {
    if(G==nullptr) return 0;
    int componentes=0;
    for(int i=0; i<G->nVertex(); i++){
        if(G->getMark(i)==NOVISITADO){
            DFS(*G,i);
            componentes++;
        }
    }
    return componentes;
}
// ============================================================================
// EJERCICIO 9: Modificar valor en un Max-Heap
// ============================================================================
/*
 * Enunciado:
 * Recibe un max-heap H, un nodo i (índice 1..H.n) y un nuevo valor j.
 * Debe sustituir el valor actual del nodo i por j y preservar la propiedad de
 * max-heap de H.
 * Recordatorio: Tienes acceso directo a H.Heap[i], H.n, H.flotar(i) y H.hundir(i).
 */
void modificarValorHeap(tColaP &H, int i, tipoElem j) {
    // TODO: Implementa tu código aquí
    if(i<0 || i>=H.sizeColaP()){
        return;
    }
    if(H.Heap[i]>j){
        H.Heap[i]=j;
        H.hundir(i);
    }
    else if(H.Heap[i]<j){
        H.Heap[i]=j;
        H.flotar(i);
    }
    return;
}

// ============================================================================
// EJERCICIO 12: Solo pares en un Min-Heap (in-place)
// ============================================================================
/*
 * Enunciado:
 * Recibe un arreglo de enteros que representa un min-heap (indexado de 1 a tamanno)
 * y su tamaño. Debe retornar el min-heap que incluye solamente los números pares
 * del min-heap original, sin usar estructuras adicionales (directamente en 'arreglo').
 * Tienes disponibles las funciones:
 *   flotar(arreglo, tamanno, indice)
 *   hundir(arreglo, tamanno, indice)
 * Actualiza 'tamanno' con la nueva cantidad de elementos pares para que el test
 * pueda verificar el arreglo resultante.
 */
int* solo_pares(int *arreglo, int &tamanno) {
    // TODO: Implementa tu código aquí
    int aux=0;
    int i=1;
    while(i<tamanno){
        if(arreglo[i]%2!=0){
            aux=arreglo[i];
            arreglo[i]=arreglo[tamanno];
            arreglo[tamanno]=aux;
            tamanno--;
        }
        else{
            i++;
        }
    }
    for(int i=1;i<tamanno;i++){
        hundir(arreglo, tamanno, i);
    }
    return arreglo;
}

// ============================================================================
// EJERCICIO 17: TDA Stream - insertAndGetMedian en O(log n)
// ============================================================================
Stream::Stream(int maxCap) : leftMaxHeap(maxCap), rightMinHeap(maxCap) {
    A = new int[maxCap];
    n = 0;
}

Stream::~Stream() {
    delete[] A;
}

void Stream::cargarEstadoEjemplo() {
    int datos[15] = {1, 4, 22, 37, 39, 40, 42, 50, 61, 71, 73, 88, 90, 91, 93};
    n = 15;
    leftMaxHeap.clearColaP();
    rightMinHeap.clearColaP();
    for (int i = 0; i < 15; i++) {
        A[i] = datos[i];
        if (i < 8) leftMaxHeap.insertColaP(datos[i]);
        else rightMinHeap.insertColaP(datos[i]);
    }
}

/*
 * Enunciado:
 * Inserta x en el arreglo A de n elementos y retorna la mediana de todos los
 * elementos almacenados incluyendo a x, en tiempo O(log n).
 * Propiedades que deben mantenerse:
 * - leftMaxHeap (tColaPMax): almacena los ceil(n/2) elementos más pequeños.
 * - rightMinHeap (tColaPMin): almacena los floor(n/2) elementos más grandes.
 * Métodos disponibles:
 * - leftMaxHeap: insertColaP(v), findMax(), removeMax(), sizeColaP()
 * - rightMinHeap: insertColaP(v), findMin(), removeMin(), sizeColaP()
 */
float Stream::insertAndGetMedian(int x) {
    // TODO: Implementa tu código aquí

    return 0.0f;
}

// ============================================================================
// EJERCICIO 18: Asignar conductor de Uber más cercano
// ============================================================================
/*
 * Enunciado:
 * Retornar el conductor disponible (del arreglo 'conductores' de tamaño 'nc')
 * que se encuentra a menor distancia del nodo 'pasajero' en el digrafo G.
 * Nota: Puedes emplear Dijkstra(G, D, s) de algoritmos_base.h.
 */
tVertice asignar_conductor(tVertice pasajero, tGrafo &G, tVertice *conductores, int nc) {
    // TODO: Implementa tu código aquí
    int *D= new int[G.nVertex()];
    for(int i=0; i<G.nVertex();i++){
        D[i]=0;
    }
    int min=100000;
    tVertice conduc=0;
    for(int i=0; i<nc;i++){
        Dijkstra(G,D,conductores[i]);
        if(D[pasajero]<min){
            min=D[pasajero];
            conduc=conductores[i];
        }
    }
    
    return conduc;
}

// ============================================================================
// EJERCICIO 20: Reparar un Min-Heap con datos erróneos
// ============================================================================
/*
 * Enunciado:
 * En un min-heap (indexado 1..tamanno) algunos nodos padres poseen valores más
 * altos que alguno de sus hijos. Implementar 'reparar' sin estructuras adicionales
 * usando flotar(arreglo, tamanno, indice) y/o hundir(arreglo, tamanno, indice).
 * (Nota: En el PDF la Figura 5 tiene 7 elementos por un copy-paste del enunciado,
 * pero el test verificará que tu arreglo resultante cumpla la propiedad de min-heap
 * con todos sus elementos).
 */
int* reparar(int *arreglo, int tamanno) {
    // TODO: Implementa tu código aquí

    return arreglo;
}

// ============================================================================
// EJERCICIO 21: Listar infectados después de 'cd' días
// ============================================================================
/*
 * Enunciado:
 * Grafo no dirigido de personas. El día 0 la persona 'infectada' tiene el virus.
 * Cada día el virus se transmite a los contactos habituales de los infectados.
 * Retornar la lista de personas infectadas después de 'cd' días (es decir, todos
 * los vértices a distancia <= cd de 'infectada').
 * Guarda en 'cantInfectados' el total de infectados.
 */
tVertice* listar_infectados(tGrafo &G, tVertice infectada, int cd, int &cantInfectados) {
    cantInfectados = 0;
    tVertice *resultado = new tVertice[G.nVertex()];

    // TODO: Implementa tu código aquí

    return resultado;
}

// ============================================================================
// EJERCICIO 23: Costo mínimo de fusión de pociones (Alquimista)
// ============================================================================
/*
 * Enunciado:
 * Fusionar dos pociones con energías a y b cuesta (a + b) y genera una nueva
 * poción de energía (a + b). Retornar el costo mínimo total para obtener una
 * única poción a partir del arreglo 'energia' de tamaño 'n'.
 * Restricciones: Usar una cola de prioridad (ej: tColaPMin de colasp.h).
 */
int costoMinimoFusion(int energia[], int n) {
    // TODO: Implementa tu código aquí

    return -1;
}

// ============================================================================
// EJERCICIO 24: Contagio de virus entre comunas de una región
// ============================================================================
/*
 * Enunciado:
 * Determinar si se contagia toda la región o no a partir de 'comunaInicial'.
 * Una comuna j adyacente a una comuna contagiada i se contagia si y solo si:
 *   gradosVirus[i] / d_ij > 1.00
 * donde d_ij es la distancia entre i y j (peso del arco G.weight(i, j)).
 */
bool seContagiaTodaLaRegion(tGrafo &G, tVertice comunaInicial, float *gradosVirus) {
    // TODO: Implementa tu código aquí
    int valor=0;
    int n= G.nVertex();
    for(int i=0;i<n;i++){
        G.setMark(i,0);
    }
    G.setMark(comunaInicial,1);
    valor++;
    for(int i=0;i<n;i++){
        for(tVertice w=G.first(i);w<G.nVertex();w=G.next(i,w)){
            if(gradosVirus[i]/G.weight(i,w)>1.00 && G.getMark(w)==0){
                G.setMark(w,1);
                valor++;
            }
        }
    }
    if(valor==n){
        return true;
    }
    else{
        return false;
    }
   /*
    tCola Q;
    tVertice v, w;
    int valor=0;
    int n= G.nVertex();
    for(int i=0;i<n;i++){
        G.setMark(i,0);
    }
    Q.enqueue(comunaInicial);
    G.setMark(comunaInicial, VISITADO);
    valor++;
    while (Q.size() != 0) {
        v = Q.frontValue();
        Q.dequeue();
        for (w = G.first(v); w < G.nVertex(); w = G.next(v, w)) {
            if (G.getMark(w) == NOVISITADO && gradosVirus[v]/G.weight(v,w)>1.00) {
                G.setMark(w, VISITADO);
                Q.enqueue(w);
                valor++;
            }
        }
    }
    if(valor==n){
        return true;
    }
    else{
        return false;
    }
        */
}

// ============================================================================
// EJERCICIO BONUS 1: Centro del grafo (el_centro)
// ============================================================================
/*
 * Enunciado:
 * Para un grafo no dirigido con pesos y conexo, se define la centralidad de un
 * nodo como la suma de todos los caminos más cortos partiendo de dicho nodo.
 * Implemente en C++ la función el_centro, la cual al recibir un grafo determina
 * cuál es el nodo que representa el centro del grafo, es decir, el nodo cuya
 * centralidad es la menor de todas.
 * Nota: Puedes emplear Dijkstra(G, D, s) de algoritmos_base.h.
 */
tVertice el_centro(tGrafo &G) {
    // TODO: Implementa tu código aquí
    
    return -1;
}

// ============================================================================
// EJERCICIO BONUS 2: Cantidad de puentes (cantidad_de_puentes)
// ============================================================================
/*
 * Enunciado:
 * Un puente es un arco de un grafo no dirigido, tal que al eliminarlo del grafo,
 * éste se vuelve desconexo.
 * Implemente en C++ la función cantidad_de_puentes, la cual al recibir un grafo
 * retorna la cantidad de puentes que posee el grafo.
 * Nota: Puedes emplear DFS(G, v) o BFS(G, s), además de G.deleteEdge / G.setEdge
 * y G.weight (recuerda que en un grafo no dirigido cada arista entre v y w está
 * representada como (v, w) y (w, v)).
 */
int cantidad_de_puentes(tGrafo &G) {
    // TODO: Implementa tu código aquí

    return -1;
}
