//Grafo dinamico
//agregando recorridos para evitar multidependencia
#ifndef GRAFO_H
#define GRAFO_H
#include <bits/stdc++.h>
using namespace std;


struct Aristas {
    int nodoDestino;
    float peso;
    Aristas* sig;
};


// Min-heap para Dijkstra
class MinHeap {
private:
    struct HeapItem {
        float dist;
        size_t nodo;
    };

    HeapItem data[5000];
    int size = 0;

    void siftUp(int i){
        while(i > 0){
            int p = (i-1)/2;
            if(data[i].dist >= data[p].dist) break;
            swap(data[i], data[p]);
            i = p;
        }
    }

    void siftDown(int i){
        while(true){
            int l = 2*i+1, r = 2*i+2;
            int smallest = i;

            if(l < size && data[l].dist < data[smallest].dist)
                smallest = l;
            if(r < size && data[r].dist < data[smallest].dist)
                smallest = r;

            if(smallest == i) break;

            swap(data[i], data[smallest]);
            i = smallest;
        }
    }

public:
    bool empty() const { return size == 0; }

    void push(float dist, size_t nodo){
        data[size] = {dist, nodo};
        siftUp(size);
        size++;
    }

    HeapItem pop(){
        if(size == 0) return {1e9, (size_t)-1};

        HeapItem minVal = data[0];
        data[0] = data[size-1];
        size--;
        if(size > 0) siftDown(0);

        return minVal;
    }
};

//CLASE GRAFO
class Grafo {
private:
    vector<Aristas*> adj;       // lista de adyacencia
    vector<string> nombres;    // nombre de los nodos
    vector<bool> activo;       // TRUE = nodo existe
    bool esDirigido;

public:

    Grafo(size_t n, bool dirigido = true) : adj(n, nullptr), nombres(n, ""), activo(n, true), esDirigido(dirigido) {}

    size_t numVertices() const { return adj.size(); }

    bool existeNodo(size_t id) const {
        return id < adj.size() && activo[id];
    }

    //crear nuevo nodo
    void altaNodo(const string& nombre){
        adj.push_back(nullptr);
        nombres.push_back(nombre);
        activo.push_back(true);

        cout << "Nodo creado con ID = " << adj.size()-1 << endl;
    }

    // asignar nombre al nodo (opcional para archivos)
    void altaNodo(size_t id, const string& nombre){
        if(existeNodo(id))
            nombres[id] = nombre;
    }

    // eliminar nodo/baja
    void eliminarNodo(size_t u){
        if(!existeNodo(u)) return;

        //borrar Aristas salientes
        Aristas* a = adj[u];
        while(a){
            Aristas* tmp = a;
            a = a->sig;
            delete tmp;
        }
        adj[u] = nullptr;

        //borrar Aristas entrantes
        for(size_t i = 0; i < adj.size(); i++){
            if(activo[i])
                eliminarAristas(i, u);
        }
        activo[u] = false;
        nombres[u].clear();
        cout << "Nodo " << u << " eliminado.\n";
    }

    // agregar Aristas
    void agregarAristas(size_t u, size_t v, float w){
        if(!existeNodo(u) || !existeNodo(v)) return;

        Aristas* nueva = new Aristas{(int)v, w, adj[u]};
        adj[u] = nueva;

        if(!esDirigido){
            Aristas* rev = new Aristas{(int)u, w, adj[v]};
            adj[v] = rev;
        }
    }

    // eliminar Aristas (u, v)
    void eliminarAristas(size_t u, size_t v){
        if(!existeNodo(u) || !existeNodo(v)) return;

        Aristas* a = adj[u];
        Aristas* prev = nullptr;

        while(a){
            if(a->nodoDestino == (int)v){
                if(prev) prev->sig = a->sig;
                else adj[u] = a->sig;
                delete a;
                break;
            }
            prev = a;
            a = a->sig;
        }

        if(!esDirigido){
            a = adj[v];
            prev = nullptr;
            while(a){
                if(a->nodoDestino == (int)u){
                    if(prev) prev->sig = a->sig;
                    else adj[v] = a->sig;
                    delete a;
                    break;
                }
                prev = a;
                a = a->sig;
            }
        }
    }

    // verificar si existe Aristas u->v
    bool existeAristas(size_t u, size_t v) const {
        if(!existeNodo(u) || !existeNodo(v)) return false;

        Aristas* a = adj[u];
        while(a){
            if(a->nodoDestino == (int)v)
                return true;
            a = a->sig;
        }
        return false;
    }


    // imprimir lista de adyacencia   
    void imprimirLista() const {
        cout << "\nLista de adyacencia\n";

        for(size_t u = 0; u < numVertices(); u++){
            if(!activo[u]) continue;

            cout << u << " [" << nombres[u] << "] : ";

            Aristas* a = adj[u];
            while(a){
                if(activo[a->nodoDestino])
                    cout << "(" << a->nodoDestino << ", peso=" << a->peso << ") ";
                a = a->sig;
            }
            cout << "\n";
        }
    }

 
    //imprimir matriz de adyacencia           
    void imprimirMatriz() const {
        const float INF = 1e9;

        cout << "\nMatriz de adyacencia:\n";

        cout << setw(8) << "";
        for(size_t j = 0; j < numVertices(); j++){
            if(activo[j]) cout << setw(8) << j;
        }
        cout << "\n";

        for(size_t i = 0; i < numVertices(); i++){
            if(!activo[i]) continue;

            cout << setw(3) << i << " | ";

            for(size_t j = 0; j < numVertices(); j++){
                if(!activo[j]) continue;

                float val = INF;

                Aristas* a = adj[i];
                while(a){
                    if(a->nodoDestino == (int)j){
                        val = a->peso;
                        break;
                    }
                    a = a->sig;
                }

                if(i == j) val = 0;

                if(val == INF) cout << setw(8) << "INF";
                else cout << setw(8) << val;
            }
            cout << "\n";
        }
    }


    //algoritmo de Dijkstra para caminos minimos desde un nodo origen        
    void dijkstra(size_t origen, vector<float>& dist, vector<int>& parent) const {

        const float INF = 1e9;
        size_t n = numVertices();

        dist.assign(n, INF);
        parent.assign(n, -1);

        if(!existeNodo(origen)) return;

        dist[origen] = 0;

        MinHeap pq;
        pq.push(0, origen);

        while(!pq.empty()){
            auto t = pq.pop();
            float distU = t.dist;
            size_t u = t.nodo;

            if(!activo[u]) continue;

            if(distU != dist[u]) continue;

            Aristas* a = adj[u];
            while(a){
                size_t v = a->nodoDestino;
                float w = a->peso;

                if(activo[v] && dist[u] + w < dist[v]){
                    dist[v] = dist[u] + w;
                    parent[v] = u;
                    pq.push(dist[v], v);
                }
                a = a->sig;
            }
        }
    }
    
    //imprimir camino (bonito)
    void imprimirCamino(size_t origen, size_t destino, const vector<int>& parent,const vector<float>& dist) const {

        if(destino >= numVertices() || !activo[destino]){
            cout << "Destino inválido.\n";
            return;
        }

        if(dist[destino] == 1e9){
            cout << "No existe camino.\n";
            return;
        }

        vector<size_t> camino;
        for(int u = destino; u != -1; u = parent[u])
            camino.push_back(u);

        reverse(camino.begin(), camino.end());

        cout << "\nCamino mínimo " << origen
             << " -> " << destino << ": ";

        for(size_t i = 0; i < camino.size(); i++){
            cout << camino[i];
            if(i + 1 < camino.size()) cout << " -> ";
        }

        cout << "\nCosto total: " << dist[destino] << "\n";
    }

    // Recorrido DFS
    void DFS(size_t inicio) const {
        if (!existeNodo(inicio)) {
            cout << "Nodo " << inicio << " no existe o fue eliminado.\n";
            return;
        }

        vector<bool> visitado(numVertices(), false);
        cout << "\nRecorrido DFS desde " << inicio << " (" << nombres[inicio] << "):\n";

        function<void(size_t)> dfsRec = [&](size_t u) {
            visitado[u] = true;
            cout << u << " (" << nombres[u] << ") ";

            for (Aristas* a = adj[u]; a; a = a->sig) {
                size_t v = a->nodoDestino;
                if (existeNodo(v) && !visitado[v]) {
                    dfsRec(v);
                }
            }
        };

        dfsRec(inicio);
        cout << "\n";
    }

    // Recorrido BFS 
    void BFS(size_t inicio) const {
        if (!existeNodo(inicio)) {
            cout << "Nodo " << inicio << " no existe o fue eliminado.\n";
            return;
        }

        const int MAXN = 5000; 
        static bool visitado[MAXN] = {false};
        static size_t cola[MAXN];
        int frente = 0, fin = 0;

        // Inicializar visitado
        for (size_t i = 0; i < numVertices(); ++i)
            visitado[i] = false;

        cola[fin++] = inicio;
        visitado[inicio] = true;

        cout << "\nRecorrido BFS desde " << inicio << " (" << nombres[inicio] << "):\n";

        while (frente < fin) {
            size_t u = cola[frente++];
            cout << u << " (" << nombres[u] << ") ";

            for (Aristas* a = adj[u]; a; a = a->sig) {
                size_t v = a->nodoDestino;
                if (existeNodo(v) && !visitado[v]) {
                    visitado[v] = true;
                    cola[fin++] = v;
                }
            }
        }
        cout << "\n";
    }
};

#endif
