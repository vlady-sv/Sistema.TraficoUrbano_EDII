#ifndef MAIN
#define MAIN
#include <ctime>
#include "Grafo.h"
#include "modificarCSV.h"
#include <windows.h>


using namespace std;

//variables globales
Grafo grafo(100, true);
HashVehiculos hash(100);

void red_Nodos_Hash();
void mostrar_Grafo();
void recorridos();
void vehiculos();
void nombreArchivo(string&, bool&, const string);
void nombreArchivoVehiculos(string&, bool&, const string);

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
        cout << "\n\t [2] Crear nueva Red.";
        cout << "\n\t [3] Alta de Nodos.";
        cout << "\n\t [4] Alta de Aristas.";
        cout << "\n\t [5] Baja de Nodos.";
        cout << "\n\t [6] Baja de Aristas.";
        cout << u8"\n\t [0] Volver al menú principal.";
        cout << u8"\n\n\t Elige una opción: ";
        cin >> opc;

        switch(opc){
            case 1:{ 
                string archivo;
                bool saveAs;
                int cont;
                nombreArchivoRed(archivo, saveAs, "cargar");
            
                HashRed hashRed(100);
                vector<Arista> aristas;
                csvRed(archivo, hashRed, aristas);
                //reiniciamos el grafo
                grafo = Grafo(100, true);
            
                //insertamos los nodos en el grafo
                for (size_t i = 0; i < 100; i++) {
                    Nodo* n = hashRed.buscar(i);
                    if (n != nullptr) {
                        grafo.altaNodo(n->id, n->nombre);
                    }
                }
                //insertamos las aristas
                for (const auto& a : aristas) {
                    grafo.agregarAristas(a.origen, a.destino, a.peso);
                }
                cout << u8"\n\t Red cargada correctamente desde " << archivo << "\n";
                }
                break;
            case 2:{
                    guardarRed();
                } 
                break;
            case 3:{
                    string nombre;
                    bool saveAs;
                    nombreArchivoRed(nombre, saveAs, "agregar");
                    distribuirRed(nombre, false, saveAs, "agregar","nodos");
                }
                break;
            case 4:{
                    string nombre;
                    bool saveAs;
                    nombreArchivoRed(nombre, saveAs, "agregar");
                    distribuirRed(nombre, false, saveAs, "agregar","aristas");
                }
                break;
            case 5:{
                    string nombre;
                    bool saveAs;
                    nombreArchivoRed(nombre, saveAs, "eliminar");
                    distribuirRed(nombre, false, saveAs, "eliminar","nodos");
                }   
                break;
            case 6:{
                    string nombre;
                    bool saveAs;
                    nombreArchivoRed(nombre, saveAs, "eliminar");
                    distribuirRed(nombre, false, saveAs, "eliminar","aristas");    
                }
                break;
            case 0: cout << u8"\n\t Regresando al menú principal...\n\n";
                break;
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
                grafo.imprimirMatriz();
                break;
            case 2: 
                grafo.imprimirLista();
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
            case 1:{ 
                int origen, destino;
                cout << "\n\t Ingresa el origen: "; cin >> origen;
                cout << "\n\t Ingresa el destino: "; cin >> destino;
                if (!grafo.existeNodo(origen) || !grafo.existeNodo(destino)){
                    cout << u8"Error: Nodo(s) no existen.\n";
                    break;
                }
                vector<float> dist;
                vector<int> parent;
                //medir tiempo de ejecucion
                clock_t inicio = clock();
                grafo.dijkstra(origen, dist, parent);
                clock_t fin = clock();
                double tiempo = double(fin - inicio) / CLOCKS_PER_SEC;
                cout << "\n\t Tiempo de ejecución de Dijkstra: "<< tiempo << " segundos\n";
                }
                break;
            case 2:{
                int inicio;
                cout << "\n\t Ingresa el nodo inicial: ";
                cin >> inicio;
                if (!grafo.existeNodo(inicio)){
                    cout << u8"\n\t Error: El nodo no existe.\n";
                }else{
                    cout << u8"\n\t Recorrido BFS:\n";
                    grafo.BFS(inicio);
                }
                }
                break;
            case 3:{
                int inicio;
                cout << "\n\t Ingresa el nodo inicial: ";
                cin >> inicio;
                if (!grafo.existeNodo(inicio)) {
                    cout << u8"Error: El nodo no existe.\n";
                } else {
                    cout << u8"\nRecorrido DFS:\n";
                    grafo.DFS(inicio);
                    cout << "\n";
                }
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
        cout << u8"\n\t [4] Crear nuevo archivo de vehículos.";
        cout << "\n\t [0] Salir del programa.";
        cout << u8"\n\n\t Elige una opción: ";
        cin >> opc;

        switch(opc){
            case 1:{
                string nomArchivo;
                nombreArchivoVehiculos(nomArchivo);
                agregarVehiculos(nomArchivo);
                }
                break;
            case 2:{
                string nomArchivo;
                nombreArchivoVehiculos(nomArchivo);
                buscarVehiculos(nomArchivo);
                }
                break;
            case 3:{
                string nomArchivo;
                nombreArchivoVehiculos(nomArchivo);
                eliminarVehiculos(nomArchivo);
                }
                break;
            case 4:{
                crearNuevoVehiculos();
                }
                break;
            case 0: cout << "\n\t Saliendo del programa....";
                break;
            default: cout << u8"\n\n\t Opción invalida.\n";
                break;
        }
    }while(opc != 0);
}

void nombreArchivoRed(string &nomArchivo, bool& saveAs, const string accion){
    if(!verificarCRed){
        crearContRed();
    }
    int cont = contRed(false);

    cout << "\n\t Archivos de Redes de Nodos: ";
    for(int i=1; i<cont; i++){
        if(i==1){
            cout << "\n\t [" << i << "] red.csv";
        }
        cout << "\n\t [" << i << "] red" << i << ".csv";
    }

    int opc;
    do{
        cout << u8"\n\t Qué archivo desea " << accion << ": ";
        cin >> opc;
    }while(opc < 0 && opc >= cont);

    //Construir el nombre del archivo de la red seleccionado por el usuario
    if(opc == 1)
        nomArchivo = "red.csv";
    else
        nomArchivo = "red" + to_string(opc) + ".csv";

    if(accion == "agregar" || accion == "eliminar"){
        do{
            cout << "\n\t [1] Modificar archivo y guardar.";
            cout << "\n\t [2] Modificar archivo y guardar como uno nuevo.";
            cout << u8"\n\n\t Escoja una opción para guardar las modificaciones: ";
            cin >> opc;
        }while(opc < 1 && opc > 2);

        if(opc == 1) saveAs = false;
        else saveAs = true;
    }

    
}

void nombreArchivoVehiculos(string &nomArchivo){
    if(!verificarCVehiculos()){
        crearContVehiculos();
    }
    int cont = contVehiculos(false);

    cout << u8"\n\t Archivos de Vehículos: ";
    for(int i=1; i<cont; i++){
        if(i==1){
            cout << "\n\t [" << i << "] vehiculos.csv";
        }
        cout << "\n\t [" << i << "] vehiculos" << i << ".csv";
    }

    int opc;
    do{
        cout << u8"\n\t Elija un archivo para trabajar con él: ";
        cin >> opc;
    }while(opc < 0 && opc >= cont);

    //Construir el nombre del archivo de la red seleccionado por el usuario
    if(opc == 1)
        nomArchivo = "vehiculos.csv";
    else
        nomArchivo = "vehiculos" + to_string(opc) + ".csv";
}
#endif
