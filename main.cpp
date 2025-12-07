#ifndef MAIN
#define MAIN
#include "Grafo.h"
#include "TablasHash.h"
#include <windows.h>
using namespace std;

//variables globales
Grafo grafo(100, true);
HashVehiculos hash(100);

void red_Nodos_Hash();
void mostrar_Grafo();
void recorridos();
void vehiculos();

int main(){
    SetConsoleOutputCP(CP_UTF8);
    int opc;

    do{
        cout << "\n-----------------------------------------------";
        cout << u8"\n\t\t\t ===> MENÚ PRINCIPAL <====";
        cout << "\n\t [1] Opciones de Red, Nodos y tablas Hash.";
        cout << "\n\t [2] Matriz y Lista del Grafo.";
        cout << "\n\t [3] Recorridos del grafo.";
        cout << u8"\n\t [4] Opciones de vehículos.";
        cout << "\n\t [0] Salir del programa.";
        cout << u8"\n\n\t Elige una opción: ";
        cin >> opc;

        switch(opc){
            case 1: red_Nodos_Hash();
                break;
            case 2: mostrar_Grafo();
                break;
            case 3: recorridos();
                break;
            case 4: vehiculos();
                break;
            case 0: cout << "\n\t Saliendo del programa....";
                break;
        }
    }while(opc != 0);

    return 0;
}

void red_Nodos_Hash(){
    int opc;

    do{
        cout << "\n-----------------------------------------------";
        cout << u8"\n\t\t\t ===> Red, Nodos y Tablas Hash <====";
        cout << "\n\t [1] Cargar Red.";
        cout << "\n\t [2] Guardar Red.";
        cout << "\n\t [3] Alta de Nodo.";
        cout << "\n\t [4] Alta de Arista.";
        cout << "\n\t [5] Baja de Nodo.";
        cout << "\n\t [6] Baja de Arista.";
        cout << u8"\n\t [0] Volver al menú principal.";
        cout << u8"\n\n\t Elige una opción: ";
        cin >> opc;

        switch(opc){
            case 1: 
                string archivo;
                //mostrar archivos existentes
                cout << "\n\t Archivos de Redes de Nodos: ";
                for(int i=1; i<cont; i++){
                    if(i=1){
                        cout << "\n\t [" << i << "] red.csv";
                    }
                    cout << "\n\t [" << i << "] red" << i << ".csv";
                }
                cout << u8"\n\t Escriba nombre del archivo CSV: ";
                cin >> archivo;
            
                HashRed hashRed(100);
                vector<Arista> aristas;
                csvRed(archivo, hashRed, aristas);
                //reiniciamos el grafo
                grafo = Grafo(100, true);
            
                //insertamos los nodos en el grafo
                for (size_t i = 0; i < 100; i++) {
                    Nodo* n = hashRed.buscar(i);
                    if (n != nullptr) {
                        grafo.altaNodoConID(n->id, n->nombre);
                    }
                }
                //insertamos las aristas
                for (const auto& a : aristas) {
                    grafo.agregarArista(a.origen, a.destino, a.peso);
                }
                cout << u8"\n\t Red cargada correctamente desde " << archivo << "\n";
                break;
            case 2: 
                break;
            case 3: 
                string nombre;
                cout << "Nombre: "; 
                cin.ignore();
                getline(cin, nombre);
                grafo.altaNodo(nombre);
                break;
            case 4: 
                int u, v; float w;
                cout << "Nodo origen: "; cin >> u;
                cout << "Nodo destino: "; cin >> v;
                cout << "Peso: "; cin >> w;
                if (!grafo.existeNodo(u) || !grafo.existeNodo(v)){
                    cout << u8"\n\t Error: uno o ambos nodos no existen.\n";
                }else{
                    grafo.agregarArista(u, v, w);
                    cout << u8"\n\t Arista agregada correctamente.\n";
                }
                break;
            case 5:
                size_t id;
                cout << "ID del nodo a eliminar: ";
                cin >> id;
                if (!grafo.existeNodo(id)) {
                    cout << "Error: nodo " << id << " no existe o ya fue eliminado.\n";
                } else {
                    grafo.eliminarNodo(id); 
                    cout << "Nodo " << id << "eliminado correctamente.\n";
                }
                break;
            case 6:
                int u, v;
                cout << "Nodo origen: "; cin >> u;
                cout << "Nodo destino: "; cin >> v;
                if (grafo.eliminarArista(u, v)){
                    cout << u8"Arista eliminada.\n";
                }else{
                    cout << u8"No existía esa arista.\n";
                }    
                break;
            case 0: break;
            default: cout << u8"\n\n\t Opción invalida.\n";
                break;
        }
    }while(opc != 0);
}

void mostrar_Grafo(){
    int opc;

    do{
        cout << "\n-----------------------------------------------";
        cout << "\n\t\t\t ===> Matriz y Lista del Grafo <====";
        cout << "\n\t [1] Mostrar Matriz.";
        cout << "\n\t [2] Mostrar Lista de Adyacencia.";
        cout << "\n\t [0] Salir del programa.";
        cout << u8"\n\n\t Elige una opción: ";
        cin >> opc;

        switch(opc){
            case 1: 
                grafo.imprimirMatriz(); break;
                break;
            case 2: 
                grafo.imprimirLista(); break;
                break;
            case 0: cout << "\n\t Saliendo del programa....";
                break;
            default: cout << u8"\n\n\t Opción invalida.\n";
                break;
        }
    }while(opc != 0);
}

void recorridos(){
    int opc;

    do{
        cout << "\n-----------------------------------------------";
        cout << "\n\t\t\t ===> Recorridos del Grafo <====";
        cout << "\n\t [1] Dijkstra.";
        cout << "\n\t [2] BFS.";
        cout << "\n\t [3] DFS.";
        cout << "\n\t [0] Salir del programa.";
        cout << u8"\n\n\t Elige una opción: ";
        cin >> opc;

        switch(opc){
            case 1: 
                int origen, destino;
                cout << "\nOrigen: "; cin >> origen;
                cout << "Destino: "; cin >> destino;
                if (!grafo.existeNodo(origen) || !grafo.existeNodo(destino)){
                    cout << u8"Error: nodo(s) no existen.\n";
                    break;
                }
                vector<float> dist;
                vector<int> parent;
                grafo.dijkstra(origen, dist, parent);
                grafo.imprimirCamino(origen, destino, parent, dist);
                break;
            case 2: 
                int inicio;
                cout << "\nNodo inicial: ";
                cin >> inicio;
                if (!grafo.existeNodo(inicio)){
                    cout << u8"Error: nodo no existe.\n";
                }else{
                    cout << u8"\nRecorrido BFS:\n"
                    grafo.BFS(inicio);
                }
                break;
            case 3: 
                int inicio;
                cout << "\nNodo inicial: ";
                cin >> inicio;
                if (!grafo.existeNodo(inicio)) {
                    cout << u8"Error: nodo no existe.\n";
                } else {
                    cout << u8"\nRecorrido DFS:\n";
                    grafo.DFS(inicio);
                    cout << "\n";
                }
                break;
            case 0: cout << "\n\t Saliendo del programa....";
                break;
            default: cout << u8"\n\n\t Opción invalida.\n";
                break;
        }
    }while(opc != 0);
}

void vehiculos(){
    int opc;

    do{
        cout << "\n-----------------------------------------------";
        cout << u8"\n\t\t\t ===> Opciones de Vehículos <====";
        cout << u8"\n\t [1] Alta de Vehículo.";
        cout << u8"\n\t [2] Buscar Vehículo.";
        cout << u8"\n\t [3] Baja de Vehículo.";
        cout << "\n\t [0] Salir del programa.";
        cout << u8"\n\n\t Elige una opción: ";
        cin >> opc;

        switch(opc){
            case 1: 
                break;
            case 2: 
                break;
            case 3: 
                break;
            case 0: cout << "\n\t Saliendo del programa....";
                break;
            default: cout << u8"\n\n\t Opción invalida.\n";
                break;
        }
    }while(opc != 0);
}

#endif
