#include <iostream>
#include <fstream>
#include <string>
#include "TablasHash.h"
#include "verificar_contarCSV.h"
#include "windows.h"
using namespace std;

//Verificacion de valores correctos
bool verificarValor(int cont, int opc){
    SetConsoleOutputCP(CP_UTF8);
    if(opc < 0 || opc >= cont){
        cout << u8"\n\n\t Opción inválida.";
        return false;
    }
    return true;
}

/* OPCIONES PARA RED */
bool crearNuevaRed(){
    SetConsoleOutputCP(CP_UTF8);
    if(!verificarCRed) return false;
    HashRed nNodos;
    int cont = contRed();
    string nomArchivo = "red" + to_string(cont) + ".csv";

    fstream red;
    red.open(nomArchivo);

    cout << u8"\n\t Dame el número de Nodos: ";
}

bool modificarRed(){
    if(!verificarCRed) return false;
    int cont = contRed();
    int opc;

    cout << "\n\t Archivos de Redes de Nodos: ";
    for(int i=1; i<cont; i++){
        if(i=1){
            cout << "\n\t [" << i << "] red.csv";
        }
        cout << "\n\t [" << i << "] red" << i << ".csv";
    }
    do{
        cout << "\n\n\t Red a modificar: ";
        cin >> opc;
    }while(!verificarValor(cont, opc));
}

bool modificar_GuardarNuevaRed(){

}

/* OPCIONES PARA VEHICULOS */
bool crearNuevoVehiculos(){

}

bool modificarArchivoVehiculos(){
    if(!verficarCVehiculos) return false;
    int cont = contVehiculos();
}

bool modificar_GuardarNuevoVehiculos(){

}


