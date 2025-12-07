#include <iostream>
#include <fstream>
#include <string>
#include "TablasHash.h"
#include "verificar_contarCSV.h"
#include "leerCSV.h"
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

//Preguntar por los nodos que se quieren agregar

void agregarNodos(HashRed& nNodos, int numNodos, int idInicial){
    for(int i=idInicial; i<numNodos; i++){
        Nodo n;
        n.id = i;

        cout << "\n\t Dame el nombre del nodo " << i << ": ";
        cin >> n.nombre;

        nNodos.insertar(n);
    }

}

//Preguntar por las aristas entre nodos

void pedirAristas(const HashRed& nNodos, vector<Arista>& aristas){
    /* Preguntar nodo por nodo si se quiere agregar una arista entre ellos*/
    for(const auto& origen: nNodos.getNodos()){
        cout << "\n\t Nodo origen: " << origen.id << " (" << origen.nombre << ")\n";

        for(const auto& destino:nNodos.getNodos()){
            if(origen.id == destino.id) continue;

            char opc;
            do{
                cout << "\n\t Deseas agregar una arista desde " << origen.nombre 
                    << " hacia " << destino.nombre << "? [S/N]: "; 
                cin >> opc;
            }while(opc != 's' && opc != 'S' && opc != 'n' && opc != 'N');

            if(opc == 's' || opc == 'S'){
                Arista a;
                a.origen = origen.id;
                a.destino = destino.id;

                cout << "\n\t Peso: ";
                cin >> a.peso;

                aristas.push_back(a);
            }
        }
    }
}

/* OPCIONES PARA RED */

/* CREAR EL ARCHIVO PARA UNA NUEVA RED */
bool crearNuevaRed(){
    SetConsoleOutputCP(CP_UTF8);
    if(!verificarCRed) return false;
    HashRed nNodos;
    vector<Arista> aristas;
    int numNodos;
    int cont = contRed(true);
    string nomArchivo = "red" + to_string(cont) + ".csv";
    
    cout << u8"\n\t Dame el número de Nodos: ";
    cin >> numNodos;

    agregarNodos(nNodos, numNodos, 0);
    
    fstream red;
    red.open(nomArchivo);
    if(!red){
        cout << u8"\n\t El archivo no se abrió correctamente.";
        return false;
    }

    /* GUARDAR LOS NODOS EN EL CSV */
    //Encabezados
    red << "#NODOS\n";
    red << "N;idNodo;nombre\n";

    //Sacamos el id y nombre de cada nodo desde la tabla hash
    for(const auto& nodo: nNodos.getNodos()){
        red << "N;" << nodo.id << ";" << nodo.nombre << "\n";
    }

    //Preguntar por las aristas
    pedirAristas(nNodos, aristas);

    /* GUARDAR LAS ARISTAS EN EL CSV */
    //Encabezados
    red << "#ARISTAS (dirigidas)\n";
    red << "E;origen;destino;peso\n";

    for(const Arista& a: aristas){
        red << "E;" << a.origen << ";" << a.destino << ";" << a.peso << "\n";
    }

    red.close();
    cout << u8"\n\tEl archivo fue creado correctamente.";
    return true;
}

/* MODIFICAR EL ARCHIVO DE UNA RED YA EXISTENTE*/
bool modificarRed(){
    SetConsoleOutputCP(CP_UTF8);
    if(!verificarCRed) return false;
    int cont = contRed(false);
    int opc;

    cout << "\n\t Archivos de Redes de Nodos: ";
    for(int i=1; i<=cont; i++){
        if(i=1){
            cout << "\n\t [" << i << "] red.csv";
        }
        cout << "\n\t [" << i << "] red" << i << ".csv";
    }
    do{
        cout << "\n\n\t Red a modificar: ";
        cin >> opc;
    }while(!verificarValor(cont, opc));

    string archivoRed;
    if(opc == 1) 
        archivoRed = "red.csv";
    else
        archivoRed = "red" + to_string(opc) + ".csv";
    

    HashRed nNodos;
    vector <Arista> aristas;
    csvRed(archivoRed, nNodos, aristas);

    //Mostramos al usuario los nodos que hay en el archivo
    cout << "\n\t Los nodos actuales en el archivo son: ";
    int lastId;
    for(const auto& n: nNodos.getNodos()){
        lastId = n.id;
        cout << "\n\tId: " << n.id << " | Nombre: " << n.nombre;
    }

    char resp;
    do{
        cout << "\n\t Deseas agregar más nodos al archivo? [S/N]: "; 
        cin >> resp;
    }while(resp != 's' && resp != 'S' && resp != 'n' && resp != 'N');
    
    if(resp == 's' || resp == 'S'){
        int numNodos;
        cout << u8"\n\t Cuántos nodos nuevos quieres agregar: ";
        cin >> numNodos;

        agregarNodos(nNodos, numNodos, lastId);
    }

    pedirAristas(nNodos, aristas); //Preguntamos por las aristas de cada nodo

    fstream red;
    red.open(archivoRed, ios::out|ios::trunc); /* Se abre el archivo en modo trunc para escribir 
    todo nuevamente y evitar problemas de sobreescritura*/
    if(!red){
        cout << u8"\n\t El archivo no se abrió correctamente.";
        return false;
    }

    //Encabezados del archivo
    red << "#NODOS\n";
    red << "N;id;nombre\n";
    for(const Nodo& n: nNodos.getNodos()){ //Nodos
        red << "N;" << n.id << ";" << n.nombre << "\n";
    }
    
    //Encabezados de las aristas
    red << "#ARISTAS (dirigidas)\n";
    red << "E;origen;destino;peso\n";

    for(const Arista& a: aristas){ //Aristas
        red << "E;" << a.origen << ";" << a.destino << ";" << a.peso << "\n";
    }
    
    red.close();
    cout << u8"\n\tEl archivo fue actualizado correctamente.";
    return true;
}

bool modificar_GuardarNuevaRed(){
    SetConsoleOutputCP(CP_UTF8);
    if(!verificarCRed) return false;
    int cont = contRed(true);
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

    string archivoModRed;
    if(opc == 1) 
        archivoModRed = "red.csv";
    else
        archivoModRed = "red" + to_string(opc) + ".csv";
    

    HashRed nNodos;
    vector <Arista> aristas;
    csvRed(archivoModRed, nNodos, aristas);

    //Mostramos al usuario los nodos que hay en el archivo
    cout << "\n\t Los nodos actuales en el archivo son: ";
    int lastId;
    for(const auto& n: nNodos.getNodos()){
        lastId = n.id;
        cout << "\n\tId: " << n.id << " | Nombre: " << n.nombre;
    }

    char resp;
    do{
        cout << "\n\t Deseas agregar más nodos al archivo? [S/N]: "; 
        cin >> resp;
    }while(resp != 's' && resp != 'S' && resp != 'n' && resp != 'N');
    
    if(resp == 's' || resp == 'S'){
        int numNodos;
        cout << u8"\n\t Cuántos nodos nuevos quieres agregar: ";
        cin >> numNodos;

        agregarNodos(nNodos, numNodos, lastId);
    }

    pedirAristas(nNodos, aristas); //Preguntamos por las aristas de cada nodo
    
    string nuevoArchRed = "red" + to_string(cont) + ".csv";
    fstream red;
    red.open(nuevoArchRed, ios::out|ios::trunc); /* Se abre el archivo en modo trunc para escribir 
    todo nuevamente y evitar problemas de sobreescritura*/
    if(!red){
        cout << u8"\n\t El archivo no se abrió correctamente.";
        return false;
    }

    //Encabezados del archivo
    red << "#NODOS\n";
    red << "N;id;nombre\n";
    for(const Nodo& n: nNodos.getNodos()){ //Nodos
        red << "N;" << n.id << ";" << n.nombre << "\n";
    }
    
    //Encabezados de las aristas
    red << "#ARISTAS (dirigidas)\n";
    red << "E;origen;destino;peso\n";

    for(const Arista& a: aristas){ //Aristas
        red << "E;" << a.origen << ";" << a.destino << ";" << a.peso << "\n";
    }

    cout << u8"\n\tEl archivo fue actualizado y guardado como copia correctamente.";
    return true;
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


