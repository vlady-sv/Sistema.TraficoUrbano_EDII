#ifndef RECORRIDO_BFS_H
#define RECORRIDO_BFS_H

#include "Grafo.h"

void Grafo::BFS(int inicio) {
    if (inicio < 0 || inicio >= n) {
        cout << "Nodo invalido.\n";
        return;
    }
    bool visitado[MAX] = { false };
    int cola[MAX];
    int frente = 0, fin = 0;

    cola[fin++] = inicio;
    visitado[inicio] = true;

    cout << "\nRecorrido BFS desde " << inicio << ":\n";

    while (frente < fin) {
        int u = cola[frente++];  
        cout << u << " ";

        for (int v = 0; v < n; v++) {
            if (adj[u][v] == 1 && !visitado[v]) {
                visitado[v] = true;
                cola[fin++] = v;
            }
        }
    }

    cout << "\n";
}

#endif

