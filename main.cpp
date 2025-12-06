#include <iostream>
#include <windows.h>
#include "Grafo.h"
#include "TablasHash.h"
using namespace std;

//variables globales
Grafo grafo(100, true);
HashVehiculos hash(101);

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
                break;
            case 2: 
                break;
            case 3: 
                break;
            case 4: 
                break;
            case 5:
                break;
            case 6:
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
                break;
            case 2: 
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
