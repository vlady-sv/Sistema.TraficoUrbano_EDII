
/*#ifndef RECORRIDO_BFS_H
#define RECORRIDO_BFS_H

#include "Grafo.h"

void Grafo::BFS(size_t inicio){
    size_t n = numVertices();

    if(inicio >= n){
        cout << "Nodo inválido.\n";
        return;
    }

    bool visitado[5000] = { false };   // tamaño suficientemente grande
    size_t cola[5000];                 // cola manual
    int frente = 0, fin = 0;

    cola[fin++] = inicio;
    visitado[inicio] = true;

    cout << "\nRecorrido BFS desde " << inicio << ":\n";

    while(frente < fin){
        size_t u = cola[frente++];
        cout << u << " ";

        // recorrer lista enlazada de u
        Arista* a = adj[u];
        while(a){
            size_t v = a->nodoDestino;

            if(!visitado[v]){
                visitado[v] = true;
                cola[fin++] = v;
            }

            a = a->sig;
        }
    }

    cout << "\n";
}

#endif*/
