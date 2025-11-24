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

//falta agregar imprimirMatriz apartir de la lista de adyacencia
};


