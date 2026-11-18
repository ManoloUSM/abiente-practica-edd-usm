#include <iostream>
#include <algorithm>
#include <cmath>
#include "ejercicios.h"

using namespace std;

#define COLOR_GREEN "\033[1;32m"
#define COLOR_RED   "\033[1;31m"
#define COLOR_CYAN  "\033[1;36m"
#define COLOR_YELLOW "\033[1;33m"
#define COLOR_RESET "\033[0m"

void printResultado(const string &nombre, bool ok, const string &detalle = "") {
    if (ok) {
        cout << COLOR_GREEN << "[PASÓ] " << COLOR_RESET << nombre;
    } else {
        cout << COLOR_RED << "[PENDIENTE / FALLÓ] " << COLOR_RESET << nombre;
    }
    if (!detalle.empty()) {
        cout << " -> " << detalle;
    }
    cout << endl;
}

// ----------------------------------------------------------------------------
// Tests individuales
// ----------------------------------------------------------------------------

void testEjercicio1() {
    cout << COLOR_CYAN << "\n--- Test Ejercicio 1: masCitado ---" << COLOR_RESET << endl;
    // 5 artículos (0..4). Artículo 3 es citado por 0, 1, 2, 4 (4 citas).
    // Artículo 2 es citado por 0, 1 (2 citas).
    tGrafo G(5);
    G.setEdge(0, 3, 1);
    G.setEdge(1, 3, 1);
    G.setEdge(2, 3, 1);
    G.setEdge(4, 3, 1);
    G.setEdge(0, 2, 1);
    G.setEdge(1, 2, 1);
    G.setEdge(3, 1, 1);

    tVertice res = masCitado(G);
    printResultado("Ejercicio 1 (masCitado)", res == 3,
                   "Esperado: 3 | Obtenido: " + to_string(res));
}

void testEjercicio5() {
    cout << COLOR_CYAN << "\n--- Test Ejercicio 5: amigosNoComunes (Facebook) ---" << COLOR_RESET << endl;
    // Grafo de 6 personas.
    // Amigos de v1 (0): {1, 2, 3}
    // Amigos de v2 (4): {2, 3, 5, 0} -> Los que NO son amigos de v1(0) son {0, 5} o si se excluye v1 mismo, veamos ambos casos:
    // Para evitar ambigüedad de si v1 y v2 son amigos entre sí, hagamos que v1(0) y v2(4) no sean amigos directos:
    // Amigos de v1(0): {1, 2}
    // Amigos de v2(4): {2, 3, 5} -> Amigos de v2 que no son amigos de v1: {3, 5}
    tGrafo G(6);
    auto addUndirected = [&](int u, int v) {
        G.setEdge(u, v, 1);
        G.setEdge(v, u, 1);
    };
    addUndirected(0, 1);
    addUndirected(0, 2);
    addUndirected(4, 2);
    addUndirected(4, 3);
    addUndirected(4, 5);

    int cant = 0;
    tVertice *res = amigosNoComunes(G, 0, 4, cant);
    sort(res, res + cant);
    bool ok = (cant == 2 && res[0] == 3 && res[1] == 5);
    string obt = "{ ";
    for (int i = 0; i < cant; i++) obt += to_string(res[i]) + " ";
    obt += "}";
    printResultado("Ejercicio 5 (amigosNoComunes)", ok,
                   "Esperado: { 3 5 } | Obtenido: " + obt);
    delete[] res;
}

void testEjercicio6() {
    cout << COLOR_CYAN << "\n--- Test Ejercicio 6: minimaCantRutas ---" << COLOR_RESET << endl;
    // 7 ciudades, 3 componentes conexas: {0,1,2}, {3,4}, {5,6}
    // Mínima cantidad de rutas para conectar 3 componentes = 3 - 1 = 2.
    tGrafo G(7);
    G.setEdge(0, 1, 1); G.setEdge(1, 0, 1);
    G.setEdge(1, 2, 1); G.setEdge(2, 1, 1);
    G.setEdge(3, 4, 1); G.setEdge(4, 3, 1);
    G.setEdge(5, 6, 1); G.setEdge(6, 5, 1);

    int res = minimaCantRutas(G);
    printResultado("Ejercicio 6 (minimaCantRutas)", res == 2,
                   "Esperado: 2 | Obtenido: " + to_string(res));
}

void testEjercicio7() {
    cout << COLOR_CYAN << "\n--- Test Ejercicio 7: saturados ---" << COLOR_RESET << endl;
    // Digrafo de 4 vértices:
    // 0 -> 1, 0 -> 2 (grado+(0)=2, grado-(0)=0 -> 2 - 0 = 2 >= 0)
    // 1 -> 2         (grado+(1)=1, grado-(1)=2 -> 1 - 2 = -1 < 0 -> SATURADO)
    // 3 -> 1, 3 -> 2 (grado+(3)=2, grado-(3)=0 -> 2 >= 0)
    // Vértice 2:     (grado+(2)=0, grado-(2)=3 -> 0 - 3 = -3 < 0 -> SATURADO)
    tGrafo G(4);
    G.setEdge(0, 1, 1);
    G.setEdge(0, 2, 1);
    G.setEdge(1, 2, 1);
    G.setEdge(3, 1, 1);
    G.setEdge(3, 2, 1);

    int cant = 0;
    tVertice *res = saturados(G, cant);
    sort(res, res + cant);
    bool ok = (cant == 2 && res[0] == 1 && res[1] == 2);
    string obt = "{ ";
    for (int i = 0; i < cant; i++) obt += to_string(res[i]) + " ";
    obt += "}";
    printResultado("Ejercicio 7 (saturados)", ok,
                   "Esperado: { 1 2 } | Obtenido: " + obt);
    delete[] res;
}

void testEjercicio8() {
    cout << COLOR_CYAN << "\n--- Test Ejercicio 8: componentesDesconectadas ---" << COLOR_RESET << endl;
    // 8 nodos en 4 componentes conexas: {0,1}, {2,3,4}, {5}, {6,7}
    tGrafo G(8);
    G.setEdge(0, 1, 1); G.setEdge(1, 0, 1);
    G.setEdge(2, 3, 1); G.setEdge(3, 2, 1);
    G.setEdge(3, 4, 1); G.setEdge(4, 3, 1);
    G.setEdge(6, 7, 1); G.setEdge(7, 6, 1);

    int res = componentesDesconectadas(&G);
    printResultado("Ejercicio 8 (componentesDesconectadas)", res == 4,
                   "Esperado: 4 | Obtenido: " + to_string(res));
}

void testEjercicio9() {
    cout << COLOR_CYAN << "\n--- Test Ejercicio 9: modificarValorHeap ---" << COLOR_RESET << endl;
    // Max-Heap del ejercicio 10: <51, 36, 30, 33, 29, 27, 28, 13, 25, 21>
    tColaP H(20);
    int vals[] = {51, 36, 30, 33, 29, 27, 28, 13, 25, 21};
    for (int v : vals) H.insertColaP(v);

    // Caso 1: Aumentar el nodo i=5 (valor 29) a j=60 -> debe flotar hasta la raíz (pos 1)
    modificarValorHeap(H, 5, 60);
    int maxTrasSubir = H.findMax();
    bool ok1 = (maxTrasSubir == 60);

    // Caso 2: Disminuir la raíz i=1 (valor 60) a j=10 -> debe hundirse y el nuevo max debe ser 51
    modificarValorHeap(H, 1, 10);
    int maxTrasBajar = H.findMax();
    bool ok2 = (maxTrasBajar == 51);

    printResultado("Ejercicio 9 (modificarValorHeap)", ok1 && ok2,
                   "Esperado: 60 y luego 51 | Obtenido: " + to_string(maxTrasSubir) + " y luego " + to_string(maxTrasBajar));
}

void testEjercicio12() {
    cout << COLOR_CYAN << "\n--- Test Ejercicio 12: solo_pares (Min-Heap) ---" << COLOR_RESET << endl;
    // Figura 1 del PDF: [X, 5, 7, 9, 10, 8, 12, 15, 20] (tamanno = 8)
    // Figura 2 esperada: [X, 8, 10, 12, 20] (tamanno = 4, o cualquier min-heap válido con {8, 10, 12, 20})
    int arr[9] = {0, 5, 7, 9, 10, 8, 12, 15, 20};
    int tam = 8;
    int *res = solo_pares(arr, tam);

    bool esMinHeap = (tam == 4 && res[1] == 8);
    int paresCount = 0;
    for (int i = 1; i <= tam && i <= 8; i++) {
        if (res[i] % 2 == 0) paresCount++;
        if (2 * i <= tam && res[i] > res[2 * i]) esMinHeap = false;
        if (2 * i + 1 <= tam && res[i] > res[2 * i + 1]) esMinHeap = false;
    }
    bool ok = esMinHeap && (paresCount == 4);
    string obt = "[ X ";
    for (int i = 1; i <= tam && i <= 8; i++) obt += to_string(res[i]) + " ";
    obt += "]";
    printResultado("Ejercicio 12 (solo_pares)", ok,
                   "Esperado: [ X 8 10 12 20 ] | Obtenido: " + obt);
}

void testEjercicio17() {
    cout << COLOR_CYAN << "\n--- Test Ejercicio 17: Stream::insertAndGetMedian ---" << COLOR_RESET << endl;
    // Ejemplo exacto de la página 7 del PDF:
    // A = {1, 4, 22, 37, 39, 40, 42, 50, 61, 71, 73, 88, 90, 91, 93}, n = 15
    // Al llamar insertAndGetMedian(49), debe retornar 49.5
    Stream st(50);
    st.cargarEstadoEjemplo();
    float med1 = st.insertAndGetMedian(49); // n pasa a 16, elementos centrales 49 y 50 -> 49.5
    float med2 = st.insertAndGetMedian(100); // n pasa a 17, elemento central es 50 -> 50.0

    bool ok = (fabs(med1 - 49.5f) < 1e-4) && (fabs(med2 - 50.0f) < 1e-4);
    printResultado("Ejercicio 17 (insertAndGetMedian)", ok,
                   "Esperado: 49.5 y luego 50.0 | Obtenido: " + to_string(med1) + " y " + to_string(med2));
}

void testEjercicio18() {
    cout << COLOR_CYAN << "\n--- Test Ejercicio 18: asignar_conductor (Uber) ---" << COLOR_RESET << endl;
    // Digrafo de 6 esquinas:
    // Pasajero en esquina 0. Conductores disponibles en esquinas {3, 4, 5}.
    // Distancias desde pasajero (0) -> a 3 es 12, a 4 es 7, a 5 es 9.
    // (Y también ponemos arcos en ambos sentidos por si calculas desde pasajero).
    tGrafo G(6);
    auto addCalle = [&](int u, int v, int peso) {
        G.setEdge(u, v, peso);
        G.setEdge(v, u, peso);
    };
    addCalle(0, 1, 3);
    addCalle(1, 2, 2);
    addCalle(2, 4, 2); // dist(0, 4) = 3 + 2 + 2 = 7
    addCalle(1, 5, 6); // dist(0, 5) = 3 + 6 = 9
    addCalle(0, 3, 12); // dist(0, 3) = 12

    tVertice conductores[] = {3, 4, 5};
    tVertice res = asignar_conductor(0, G, conductores, 3);
    printResultado("Ejercicio 18 (asignar_conductor)", res == 4,
                   "Esperado: 4 (distancia 7) | Obtenido: " + to_string(res));
}

void testEjercicio20() {
    cout << COLOR_CYAN << "\n--- Test Ejercicio 20: reparar (Min-Heap) ---" << COLOR_RESET << endl;
    // Figura 4 del PDF: [X, 5, 12, 7, 10, 20, 13, 6, 15, 18] (tamanno = 9)
    int arr[10] = {0, 5, 12, 7, 10, 20, 13, 6, 15, 18};
    int tam = 9;
    int *res = reparar(arr, tam);

    bool esMinHeap = true;
    for (int i = 1; i <= tam; i++) {
        if (2 * i <= tam && res[i] > res[2 * i]) esMinHeap = false;
        if (2 * i + 1 <= tam && res[i] > res[2 * i + 1]) esMinHeap = false;
    }
    string obt = "[ X ";
    for (int i = 1; i <= tam; i++) obt += to_string(res[i]) + " ";
    obt += "]";
    printResultado("Ejercicio 20 (reparar)", esMinHeap,
                   "Propiedad Min-Heap cumplida: " + string(esMinHeap ? "SÍ" : "NO") + " | Arreglo: " + obt);
}

void testEjercicio21() {
    cout << COLOR_CYAN << "\n--- Test Ejercicio 21: listar_infectados ---" << COLOR_RESET << endl;
    // Red de 7 personas (0..6):
    // Día 0: persona 0
    // Día 1 (vecinos de 0): 1, 2
    // Día 2 (vecinos de 1 y 2): 3, 4
    // Día 3 (vecinos de 4): 5
    // Persona 6 aislada.
    // Si cd = 2, infectados deben ser {0, 1, 2, 3, 4} (o {1, 2, 3, 4} si no incluyes al paciente 0; aceptamos ambos!)
    tGrafo G(7);
    auto addContacto = [&](int u, int v) {
        G.setEdge(u, v, 1);
        G.setEdge(v, u, 1);
    };
    addContacto(0, 1);
    addContacto(0, 2);
    addContacto(1, 3);
    addContacto(2, 4);
    addContacto(4, 5);

    int cant = 0;
    tVertice *res = listar_infectados(G, 0, 2, cant);
    sort(res, res + cant);

    bool okCon0 = (cant == 5 && res[0] == 0 && res[1] == 1 && res[2] == 2 && res[3] == 3 && res[4] == 4);
    bool okSin0 = (cant == 4 && res[0] == 1 && res[1] == 2 && res[2] == 3 && res[3] == 4);

    string obt = "{ ";
    for (int i = 0; i < cant; i++) obt += to_string(res[i]) + " ";
    obt += "}";
    printResultado("Ejercicio 21 (listar_infectados, cd=2)", okCon0 || okSin0,
                   "Esperado: { 0 1 2 3 4 } | Obtenido: " + obt);
    delete[] res;
}

void testEjercicio23() {
    cout << COLOR_CYAN << "\n--- Test Ejercicio 23: costoMinimoFusion ---" << COLOR_RESET << endl;
    // Ejemplo del PDF: energías = {4, 3, 2, 6} -> costo mínimo = 29
    int energias[] = {4, 3, 2, 6};
    int res = costoMinimoFusion(energias, 4);
    printResultado("Ejercicio 23 (costoMinimoFusion)", res == 29,
                   "Esperado: 29 | Obtenido: " + to_string(res));
}

void testEjercicio24() {
    cout << COLOR_CYAN << "\n--- Test Ejercicio 24: seContagiaTodaLaRegion ---" << COLOR_RESET << endl;
    // 4 comunas (0..3).
    // gradosVirus = {10.0, 6.0, 8.0, 5.0}
    // Comuna 0 -> Comuna 1 con distancia 8 (10.0 / 8 = 1.25 > 1.0 -> CONTAGIA)
    // Comuna 1 -> Comuna 2 con distancia 5 (6.0 / 5 = 1.20 > 1.0 -> CONTAGIA)
    // Comuna 2 -> Comuna 3 con distancia 7 (8.0 / 7 = 1.14 > 1.0 -> CONTAGIA)
    tGrafo G1(4);
    G1.setEdge(0, 1, 8); G1.setEdge(1, 0, 8);
    G1.setEdge(1, 2, 5); G1.setEdge(2, 1, 5);
    G1.setEdge(2, 3, 7); G1.setEdge(3, 2, 7);
    float grados1[] = {10.0f, 6.0f, 8.0f, 5.0f};
    bool res1 = seContagiaTodaLaRegion(G1, 0, grados1);

    // Ahora aumentamos la distancia entre 2 y 3 a 10 (8.0 / 10 = 0.8 <= 1.0 -> NO CONTAGIA a 3)
    tGrafo G2(4);
    G2.setEdge(0, 1, 8); G2.setEdge(1, 0, 8);
    G2.setEdge(1, 2, 5); G2.setEdge(2, 1, 5);
    G2.setEdge(2, 3, 10); G2.setEdge(3, 2, 10);
    bool res2 = seContagiaTodaLaRegion(G2, 0, grados1);

    bool ok = (res1 == true && res2 == false);
    printResultado("Ejercicio 24 (seContagiaTodaLaRegion)", ok,
                   "Esperado: true y false | Obtenido: " + string(res1 ? "true" : "false") + " y " + string(res2 ? "true" : "false"));
}

void ejecutarTodos() {
    testEjercicio1();
    testEjercicio5();
    testEjercicio6();
    testEjercicio7();
    testEjercicio8();
    testEjercicio9();
    testEjercicio12();
    testEjercicio17();
    testEjercicio18();
    testEjercicio20();
    testEjercicio21();
    testEjercicio23();
    testEjercicio24();
}

int main() {
    int opcion;
    do {
        cout << COLOR_YELLOW << "\n=======================================================" << endl;
        cout << "   AMBIENTE DE PRÁCTICA - CERTAMEN 3 (INF-134 UTFSM)   " << endl;
        cout << "=======================================================" << COLOR_RESET << endl;
        cout << "  0. Ejecutar TODOS los tests" << endl;
        cout << "  1. Probar Ejercicio 1  (Grafo: masCitado)" << endl;
        cout << "  5. Probar Ejercicio 5  (Grafo: amigosNoComunes - Facebook)" << endl;
        cout << "  6. Probar Ejercicio 6  (Grafo: minimaCantRutas)" << endl;
        cout << "  7. Probar Ejercicio 7  (Grafo: saturados)" << endl;
        cout << "  8. Probar Ejercicio 8  (Grafo: componentesDesconectadas)" << endl;
        cout << "  9. Probar Ejercicio 9  (Heap:  modificarValorHeap)" << endl;
        cout << " 12. Probar Ejercicio 12 (Heap:  solo_pares)" << endl;
        cout << " 17. Probar Ejercicio 17 (Heap:  Stream::insertAndGetMedian)" << endl;
        cout << " 18. Probar Ejercicio 18 (Grafo: asignar_conductor - Uber)" << endl;
        cout << " 20. Probar Ejercicio 20 (Heap:  reparar)" << endl;
        cout << " 21. Probar Ejercicio 21 (Grafo: listar_infectados)" << endl;
        cout << " 23. Probar Ejercicio 23 (Heap:  costoMinimoFusion)" << endl;
        cout << " 24. Probar Ejercicio 24 (Grafo: seContagiaTodaLaRegion)" << endl;
        cout << " 99. Salir" << endl;
        cout << "Seleccione una opción: ";
        if (!(cin >> opcion)) break;

        switch (opcion) {
            case 0:  ejecutarTodos(); break;
            case 1:  testEjercicio1(); break;
            case 5:  testEjercicio5(); break;
            case 6:  testEjercicio6(); break;
            case 7:  testEjercicio7(); break;
            case 8:  testEjercicio8(); break;
            case 9:  testEjercicio9(); break;
            case 12: testEjercicio12(); break;
            case 17: testEjercicio17(); break;
            case 18: testEjercicio18(); break;
            case 20: testEjercicio20(); break;
            case 21: testEjercicio21(); break;
            case 23: testEjercicio23(); break;
            case 24: testEjercicio24(); break;
            case 99: cout << "¡Mucho éxito en el certamen!" << endl; break;
            default: cout << "Opción no válida." << endl;
        }
    } while (opcion != 99);

    return 0;
}
