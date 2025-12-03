#ifndef RECORRIDO_DFS_H
#define RECORRIDO_DFS_H

#include "Grafo.h"

// DFS clásico usando recursividad.
// Hecho simple, sin adornos, para que se entienda fácil.
void Grafo::DFS(int inicio) {
    if (inicio < 0 || inicio >= (int)numVertices()) {
        cout << "Nodo invalido.\n";
        return;
    }

    // arreglo de visitados
    vector<bool> visitado(numVertices(), false);

    cout << "\nRecorrido DFS desde " << inicio << ":\n";

    // función auxiliar recursiva
    function<void(int)> dfsRec = [&](int u) {
        visitado[u] = true;
        cout << u << " ";  // imprime el nodo actual

        // recorrer lista de adyacencia
        Arista* a = adj[u];
        while (a) {
            int v = a->nodoDestino;
            if (!visitado[v]) {
                dfsRec(v);
            }
            a = a->sig;
        }
    };

    dfsRec(inicio);
    cout << "\n";
}

#endif
