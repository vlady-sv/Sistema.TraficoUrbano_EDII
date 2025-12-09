#ifndef MAIN
#define MAIN
#include <windows.h>
#include <ctime>
#include <limits>
#include <chrono>
#include "Grafo.h"
#include "modificarCSV.h"
using namespace std;

//variables globales

void iniciarPorDefecto(const string, HashRed&, vector<Arista>&, Grafo&);
void red_Nodos_Hash(HashRed&, vector<Arista>&, Grafo&);
void redArchivo();
void redGrafo(Grafo&);
void mostrar_Grafo(Grafo&);
void recorridos(Grafo&);
void vehiculos();
void nombreArchivoRed(string&, bool&, const string);
void nombreArchivoVehiculos(string&);

int main(){
    SetConsoleOutputCP(CP_UTF8);
    HashRed hashRed(10);
    vector<Arista> aristas;
    Grafo grafo(10, true);

    iniciarPorDefecto("red.csv", hashRed, aristas, grafo);

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
            case 1: red_Nodos_Hash(hashRed, aristas, grafo);
                break;
            case 2: mostrar_Grafo(grafo);
                break;
            case 3: recorridos(grafo);
                break;
            case 4: vehiculos();
                break;
            case 0: cout << "\n\t Saliendo del programa....";
                break;
        }
    }while(opc != 0);

    return 0;
}

/* Iniciar por defecto con una red cuando se abre el programa */
void iniciarPorDefecto(const string nomArchivo, HashRed& hashRed, vector<Arista>& aristas, Grafo& grafo){
    csvRed(nomArchivo, hashRed, aristas);
    //Inserción de los nodos en el grafo
    for (size_t i = 0; i < 10; i++) {
        Nodo* n = hashRed.buscar(i);
        if (n != nullptr) {
            grafo.altaNodo(n->id, n->nombre);
        }
    }
    //Inserción de las aristas
    for (const auto& a : aristas) {
        grafo.agregarAristas(a.origen, a.destino, a.peso);
    }

    if(!verificarCRed()){
        crearContRed();
    }
    if(!verificarCVehiculos()){
        crearContVehiculos();
    }
}

/* Opciones para Red: Nodos, aristas, archivos de tablas hash*/
void red_Nodos_Hash(HashRed& hashRed, vector<Arista>& aristas, Grafo& grafo){
    int opc;

    do{
        cout << "\n-----------------------------------------------";
        cout << u8"\n\t\t\t ===> Red, Nodos y Tablas Hash <====";
        cout << "\n\t [1] Cargar Red.";
        cout << "\n\t [2] Opciones de Red usando Archivo.";
        cout << "\n\t [3] Opciones de Red usando Grafo.";
        cout << u8"\n\t [0] Volver al menú principal.";
        cout << u8"\n\n\t Elige una opción: ";
        cin >> opc;

        switch(opc){
            case 1:{ 
                string archivo;
                bool saveAs;
                nombreArchivoRed(archivo, saveAs, "cargar");
            
                hashRed = HashRed(100);
                aristas.clear();
                csvRed(archivo, hashRed, aristas);
                //reiniciamos el grafo
                grafo = Grafo(10, true);
            
                //insertamos los nodos en el grafo
                for (size_t i = 0; i < 10; i++) {
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
                    redArchivo();
                } 
                break;
            case 3:{
                    redGrafo(grafo);
                }
                break;
            case 0: cout << u8"\n\t Regresando al menú principal...\n\n";
                break;
            default: cout << u8"\n\n\t Opción invalida.\n";
                break;
        }
    }while(opc != 0);
}

/* Opciones para Red desde los archivos, modificar, eliminar, agregar*/
void redArchivo(){
    int opc;

    do{
        cout << "\n-----------------------------------------------";
        cout << u8"\n\t\t\t ===> Nodos y Aristas (Manejo desde Archivos) <====";
        cout << "\n\t [1] Crear nueva Red.";
        cout << "\n\t [2] Alta de Nodos.";
        cout << "\n\t [3] Alta de Aristas.";
        cout << "\n\t [4] Baja de Nodos.";
        cout << "\n\t [5] Baja de Aristas.";
        cout << u8"\n\t [0] Volver al menú anterior.";
        cout << u8"\n\n\t Elige una opción: ";
        cin >> opc;

        switch(opc){
            case 1:{
                    guardarRed();
                } 
                break;
            case 2:{
                    string nombre;
                    bool saveAs;
                    nombreArchivoRed(nombre, saveAs, "agregar");
                    distribuirRed(nombre, false, saveAs, "agregar","nodos");
                }
                break;
            case 3:{
                    string nombre;
                    bool saveAs;
                    nombreArchivoRed(nombre, saveAs, "agregar");
                    distribuirRed(nombre, false, saveAs, "agregar","aristas");
                }
                break;
            case 4:{
                    string nombre;
                    bool saveAs;
                    nombreArchivoRed(nombre, saveAs, "eliminar");
                    distribuirRed(nombre, false, saveAs, "eliminar","nodos");
                }   
                break;
            case 5:{
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

/* Opciones para Red desde el grafo (desde una red ya cargada) eliminar y agregar nodos y aristas*/
void redGrafo(Grafo& grafo){
    int opc;

    do{
        cout << "\n-----------------------------------------------";
        cout << u8"\n\t\t\t ===> Nodos y Aristas (Manejo desde Grafo) <====";
        cout << "\n\t [1] Alta de Nodos.";
        cout << "\n\t [2] Alta de Aristas.";
        cout << "\n\t [3] Baja de Nodos.";
        cout << "\n\t [4] Baja de Aristas.";
        cout << u8"\n\t [0] Volver al menú anterior.";
        cout << u8"\n\n\t Elige una opción: ";
        cin >> opc;

        switch(opc){
            case 1:{
                    string nombre;
                    cout << u8"Nombre del nodo: ";
                    cin.ignore(numeric_limits<std::streamsize>::max(), '\n');
                    getline(cin, nombre);
                    grafo.altaNodo(nombre);
                }
                break;
            case 2:{
                    int u, v; float w;
                    cout << u8"Nodo origen (ID): "; 
                    cin >> u;
                    cout << u8"Nodo destino (ID): "; 
                    cin >> v;
                    cout << u8"Peso: "; 
                    cin >> w;
                    if (!grafo.existeNodo(u) || !grafo.existeNodo(v)){
                        cout << u8"\n\t Error: uno o ambos nodos no existen.\n";
                    }else if (u == v){
                        cout << u8"\n\t Error: No se permiten bucles (u -> u).\n";
                    }else if (grafo.existeAristas(u, v)){
                        cout << u8"\n\t Ya existe una arista de " << u << " a " << v << "\n";
                        char resp;
                        cout << u8"\t ¿Reemplazar peso? (s/n): "; cin >> resp;
                        if (resp != 's' && resp != 'S') break;
                        grafo.eliminarAristas(u, v);  //borra la antigua
                    }
                    grafo.agregarAristas(u, v, w);
                    cout << u8"\n\t Arista " << u << " -> " << v << " agregada con peso " << w << "\n";
                }
                break;
            case 3:{
                    size_t id;
                    cout << u8"\n\t ID del nodo a eliminar: ";
                    cin >> id;
                
                    if (!grafo.existeNodo(id)){
                        cout << u8"\n\t Error: El nodo " << id << " no existe o ya fue eliminado.\n";
                    }else{
                        grafo.eliminarNodo(id);
                        cout << u8"\t Nodo " << id << " y todas sus aristas eliminadas correctamente.\n";
                    }
                }
                break;
            case 4:{
                    int u, v;
                    cout << u8"Nodo origen: "; 
                    cin >> u;
                    cout << u8"Nodo destino: "; 
                    cin >> v;
                    if (!grafo.existeAristas(u, v)){
                        cout << u8"\n\t No existe arista de " << u << " -> " << v << "\n";
                    }else{
                        grafo.eliminarAristas(u, v);
                        cout << u8"\t Arista " << u << " -> " << v << " eliminada correctamente.\n";
                    }
                }
                break;
            case 0: cout << u8"\n\t Regresando al menú principal...\n\n";
                break;
            default: cout << u8"\n\n\t Opción invalida.\n";
                break;
        }
    }while(opc != 0);
}

/* Matriz y lista del grafo */
void mostrar_Grafo(Grafo& grafo){
    int opc;

    do{
        cout << "\n-----------------------------------------------";
        cout << "\n\t\t\t ===> Matriz y Lista del Grafo <====";
        cout << "\n\t [1] Mostrar Matriz.";
        cout << "\n\t [2] Mostrar Lista de Adyacencia.";
        cout << u8"\n\t [0] Volver al menú anterior.";
        cout << u8"\n\n\t Elige una opción: ";
        cin >> opc;

        switch(opc){
            case 1: 
                grafo.imprimirMatriz();
                break;
            case 2: 
                grafo.imprimirLista();
                break;
            case 0: 
                break;
            default: cout << u8"\n\n\t Opción invalida.\n";
                break;
        }
    }while(opc != 0);
}

/* Recorridos */
void recorridos(Grafo& grafo){
    int opc;

    do{
        cout << "\n-----------------------------------------------";
        cout << "\n\t\t\t ===> Recorridos del Grafo <====";
        cout << "\n\t [1] Dijkstra.";
        cout << "\n\t [2] BFS.";
        cout << "\n\t [3] DFS.";
        cout << u8"\n\t [0] Volver al menú anterior.";
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
                using namespace std::chrono; //cambio porque clock() puede no estar detectando el tiempo con la CPU
                auto inicio = high_resolution_clock::now();
                
                grafo.dijkstra(origen, dist, parent);
                
                auto fin = high_resolution_clock::now();
                double tiempo = duration<double, std::micro>(fin - inicio).count();;
                cout << "\n\t Tiempo de ejecución de Dijkstra: "<< tiempo << " segundos\n"; //aqui son microsegundos
                //imprimir camino
                grafo.imprimirCamino(origen, destino, parent, dist);
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
            case 0:
                break;
            default: cout << u8"\n\n\t Opción invalida.\n";
                break;
        }
    }while(opc != 0);
}

/* Opciones para el manejo de archivos de vehiculos*/
void vehiculos(){
    int opc;

    do{
        cout << "\n-----------------------------------------------";
        cout << u8"\n\t\t\t ===> Opciones de Vehículos <====";
        cout << u8"\n\t [1] Alta de Vehículo.";
        cout << u8"\n\t [2] Buscar Vehículo.";
        cout << u8"\n\t [3] Baja de Vehículo.";
        cout << u8"\n\t [4] Crear nuevo archivo de vehículos.";
        cout << u8"\n\t [0] Regresar al menú anterior.";
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

/* Funcion auxiliar para obtener el nombre del archivo de la red */
void nombreArchivoRed(string &nomArchivo, bool& saveAs, const string accion){
    if(!verificarCRed()){
        crearContRed();
    }
    int cont = contRed(false);

    cout << "\n\t Archivos de Redes de Nodos: ";
    for(int i=1; i<=cont; i++){
        if(i==1){
            cout << "\n\t [" << i << "] red.csv";
        }else{
            cout << "\n\t [" << i << "] red" << i << ".csv";
        }
    }

    int opc;
    do{
        cout << u8"\n\n\t Qué archivo desea " << accion << ": ";
        cin >> opc;
    }while(opc <= 0 && opc >= cont);

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

/* Funcion auxiliar para obtener el nombre del archivo de vehiculos */
void nombreArchivoVehiculos(string &nomArchivo){
    if(!verificarCVehiculos()){
        crearContVehiculos();
    }
    int cont = contVehiculos(false);

    cout << u8"\n\t Archivos de Vehículos: ";
    for(int i=1; i<=cont; i++){
        if(i==1){
            cout << "\n\t [" << i << "] vehiculos.csv";
        }else{
            cout << "\n\t [" << i << "] vehiculos" << i << ".csv";
        }
    }

    int opc;
    do{
        cout << u8"\n\t Elija un archivo para trabajar con él: ";
        cin >> opc;
    }while(opc <= 0 && opc >= cont);

    //Construir el nombre del archivo de la red seleccionado por el usuario
    if(opc == 1)
        nomArchivo = "vehiculos.csv";
    else
        nomArchivo = "vehiculos" + to_string(opc) + ".csv";
}
#endif
