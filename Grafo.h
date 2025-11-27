struct Arista {
    int nodoDestino;
    float peso;
    Arista* sig;
};

class Grafo {
private:
    vector<Arista*> adj;     // lista de adyacencia, considerando pesos
    vector<string> nombres;  // nombre de los nodos
    bool esDirigido;

public:
    Grafo(size_t n, bool dirigido = true) : adj(n, nullptr), nombres(n, ""), esDirigido(dirigido) {}

    size_t numVertices() const { return adj.size(); }

    //asignar nombre al nodo
    void altaNodo(size_t id, const string& nombre){
        if(id < numVertices()) nombres[id] = nombre;
    }

    //agregarArista(u, v)
    void agregarArista(size_t u, size_t v, float w){
        if(u >= numVertices() || v >= numVertices()) return;

        //insertar al inicio de la lista enlazada
        Arista* nueva = new Arista{(int)v, w, adj[u]};
        adj[u] = nueva;

        //si no es dirigido, agregar arista inversa
        if(!esDirigido){
            Arista* rev = new Arista{(int)u, w, adj[v]};
            adj[v] = rev;
        }
    }

    //eliminarArista(u, v)
    void eliminarArista(size_t u, size_t v){
        if(u >= numVertices() || v >= numVertices()) return;

        Arista* aristActual = adj[u];
        Arista* aristAnterior = nullptr;

        while(aristActual){
            if(aristActual->nodoDestino == (int)v){
                if(aristAnterior) aristAnterior->sig = aristActual->sig;
                else adj[u] = aristActual->sig;
                delete aristActual;
                break;
            }
            aristAnterior = aristActual;
            aristActual = aristActual->sig;
        }

        // si es no dirigido, eliminar la arista inversa
        if(!esDirigido){
            aristActual = adj[v];
            aristAnterior = nullptr;

            while(aristActual){
                if(aristActual->nodoDestino == (int)u){
                    if(aristAnterior) aristAnterior->sig = aristActual->sig;
                    else adj[v] = aristActual->sig;
                    delete aristActual;
                    break;
                }
                aristAnterior = aristActual;
                aristActual = aristActual->sig;
            }
        }
    }

    //verificar si existe arista u->v
    bool existeArista(size_t u, size_t v) const {
        if(u >= numVertices() || v >= numVertices()) return false;

        Arista* aristActual = adj[u];
        while(aristActual){
            if(aristActual->nodoDestino == (int)v)
                return true;
            aristActual = aristActual->sig;
        }
        return false;
    }

    //imprimir lista de adyacencia
    void imprimirLista() const {
        cout << "\nLista de adyacencia (" << (esDirigido ? "dirigido" : "no dirigido") << ")\n";

        for(size_t u = 0; u < numVertices(); u++){
            cout << u << " [" << nombres[u] << "] : ";
            Arista* aristActual = adj[u];
            while(aristActual){
                cout << "(" << aristActual->nodoDestino << ", peso=" << aristActual->peso << ") ";
                aristActual = aristActual->sig;
            }
            cout << "\n";
        }
    }

//imprimir matriz apartir de la lista de adyacencia
    void imprimirMatriz() const {
        //tambien se puede usar -1, 9999 o 1e9 para representar "infinito"
        const float INF = 1e9; //se usa para decir no hay arista de un nodo a otro

        vector<vector<float>> M(numVertices(), vector<float>(numVertices(), INF));

        for(size_t i = 0; i < numVertices(); i++)
            M[i][i] = 0;

        //llenar matriz segun la lista
        for(size_t u = 0; u < numVertices(); u++){
            Arista* aristActual = adj[u];
            while(aristActual){
                M[u][aristActual->nodoDestino] = aristActual->peso;
                aristActual = aristActual->sig;
            }
        }

        cout << "\nMatriz de adyacencia:\n";

        //encabezado para que se va bonito
        cout << setw(8) << "";
        for(size_t j = 0; j < numVertices(); j++)
            cout << setw(8) << j;
        cout << "\n";

        for(size_t i = 0; i < numVertices(); i++){
            cout << setw(3) << i << " | ";
            for(size_t j = 0; j < numVertices(); j++){
                if(M[i][j] == INF) cout << setw(8) << "INF";
                else cout << setw(8) << M[i][j];
            }
            cout << "\n";
        }
    }

//----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
//algoritmo de Dijkstra para caminos minimos desde un nodo origen

    void dijkstra(size_t origen, vector<float>& dist, vector<int>& parent) const {
        const float INF = 1e9;
        size_t n = numVertices();

        dist.assign(n, INF);
        parent.assign(n, -1);

        if(origen >= n) return;

        dist[origen] = 0;

        // Min-heap: (distancia acumulada, nodo)
        using P = pair<float, size_t>;
        priority_queue<P, vector<P>, greater<P>> pq;

        pq.push({0, origen});

        while(!pq.empty()) {
            auto [distU, u] = pq.top();
            pq.pop();

            //si este par esta "viejo", lo ignoramos
            if(distU != dist[u])
                continue;

            //recorrer todas las aristas del nodo u
            Arista* a = adj[u];
            while(a) {
                size_t v = a->nodoDestino;
                float w = a->peso;

                if(dist[u] + w < dist[v]) {
                    dist[v] = dist[u] + w;
                    parent[v] = (int)u;
                    pq.push({dist[v], v});
                }

                a = a->sig; //avanzar en la lista enlazada
            }
        }
    }

//falta agregar la impresion usando el algoritmo
};


