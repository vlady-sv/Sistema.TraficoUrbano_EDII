#include <iostream>
#include <fstream>
#include <string>
#include "TablasHash.h"
#include "verificar_contarCSV.h"
#include "leerCSV.h"
#include "windows.h"
using namespace std;

void distribuir(const string nomArchivo, bool nueva, bool saveAs, string accion, string objeto){
    HashRed nNodos;
    vector <Arista> aristas;

    csvRed(nomArchivo, nNodos, aristas); //Se obtienen los elementos contenidos en el archivo
    //Separamos segun al accion que se quiera realizar
    if(accion == "agregar"){
        if(objeto == "nodos"){ //Tambien separamos segun el objeto
            agregarNodos(nNodos, nueva); //Dependiendo de la accion y el objeto solo se manda lo necesario
            if(!nueva && !saveAs) modificarRed(nomArchivo, nNodos, aristas);
            guardarRed(nNodos, aristas, saveAs);
        }else if(objeto == "aristas"){
            agregarAristas(nNodos, aristas, nueva);
            if(!nueva && !saveAs)  modificarRed(nomArchivo, nNodos, aristas);
            guardarRed(nNodos, aristas, saveAs);

        }
    }else if(accion == "eliminar"){
        if(objeto == "nodos"){
            eliminarNodos(nNodos, aristas);
            if(!nueva && !saveAs) modificarRed(nomArchivo, nNodos, aristas);
            guardarRed(nNodos, aristas, saveAs);
        }else if(objeto == "aristas"){
            eliminarAristas();
            if(!nueva && !saveAs) modificarRed(nomArchivo, nNodos, aristas);
            guardarRed(nNodos, aristas, saveAs);
        }
    }
}

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

void agregarNodos(HashRed& nNodos, bool nueva){
    SetConsoleOutputCP(CP_UTF8);
    int lastId = 0;
    if(!nueva){
        //Mostramos al usuario los nodos que hay en el archivo
        cout << "\n\t Los nodos actuales en el archivo son: ";
        for(const auto& n: nNodos.getNodos()){
            lastId = n.id;
            cout << "\n\tId: " << n.id << " | Nombre: " << n.nombre;
        }
    }

    //Preguntar cuántos nodos se quieren agregar
    int numNodos;
    cout << u8"\n\t Cuántos nodos quieres agregar: ";
    cin >> numNodos;
    
    //Preguntamos el nombre de cada nodo nuevo a agregar
    for(int i=lastId; i<numNodos; i++){
        Nodo n;
        n.id = i;

        cout << "\n\t Dame el nombre del nodo " << i << ": ";
        cin >> n.nombre;

        nNodos.insertar(n);
    }
}

//Preguntar por las aristas entre nodos

void agregarAristas(const HashRed& nNodos, vector<Arista>& aristas, bool nueva){
    //////////////////Considrerar agregar mostrar las aristas
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

// Eliminar Nodos de una red

void eliminarNodos(HashRed& nNodos, vector<Arista>& aristas){
    char resp;
    int idEliminar;
    do{
        vector<int> lastId;
        cout << "\n\t Los nodos actuales en el archivo son: ";
        for(const auto& n: nNodos.getNodos()){
            cout << "\n\tId: " << n.id << " | Nombre: " << n.nombre;
            lastId.push_back(n.id);
        }

        cout << "\n\t Escribe el ID del nodo que quieres eliminar: ";
        cin >> idEliminar;

        bool existe = false;
        for(const auto& n: nNodos.getNodos()){
            if(n.id == idEliminar){
                existe = true;
                break;
            }
        }

        if(!existe){
            cout << "\n\n\t El nodo con id " << idEliminar << " no existe.";
        }else{
            //Se elimina el nodo
            nNodos.eliminar(idEliminar);

            //Se buscan todas las aristas que tuvieran conexión con el nodo y también se eliminan
            for(size_t i=0; i<aristas.size(); ++i){
                if(aristas[i].origen == idEliminar || aristas[i].destino == idEliminar){
                    aristas.erase(aristas.begin() + i);
                    i--;
                }
            }

            cout << "\n\t El nodo con el id " << idEliminar << " y sus aristas adyacentes han sido eliminadas.";
        }

        do{
            cout << "\n\t Desea eliminar otro nodo? [S/N]: ";
            cin.ignore();
            cin >> resp;
        }while(resp != 's' && resp != 'S' && resp != 'n' && resp != 'N');
    }while(resp == 's' || resp == 'S');
}

//Eliminar aristas de una red

void eliminarAristas(){
    
}

//Eliminar vehiculos

void eliminarVehiculos(){

}

/* OPCIONES PARA RED */

/* CREAR RED DESDE CERO O GUARDA COMO UNA NUEVA A PARTIR DE OTRA*/
bool guardarRed(HashRed& nNodos, vector <Arista>& aristas, bool saveAs){
    SetConsoleOutputCP(CP_UTF8);
    if(!verificarCRed){
        crearContRed();
    }

    fstream red;
    if(!saveAs){
        HashRed nNodos;
        vector<Arista> aristas;
        int cont = contRed(true);
        string nomArchivo = "red" + to_string(cont) + ".csv";

        //Preguntar por los nodos
        agregarNodos(nNodos, true);

        //Preguntar por las aristas
        agregarAristas(nNodos, aristas, true);

        //Abrir el archivo de la red
        red.open(nomArchivo);
        if(!red){
            cout << u8"\n\t El archivo no se abrió correctamente.";
            return false;
        }

        /* GUARDAR LOS NODOS EN EL CSV */
        //Encabezados
        red << "#NODOS\n";
        red << "N;idNodo;nombre\n";

        for(const Nodo& n: nNodos.getNodos()){
            red << "N;" << n.id << ";" << n.nombre << "\n";
        }

        /* GUARDAR LAS ARISTAS EN EL CSV */
        //Encabezados
        red << "#ARISTAS (dirigidas)\n";
        red << "E;origen;destino;peso\n";

        for(const Arista& a: aristas){
            red << "E;" << a.origen << ";" << a.destino << ";" << a.peso << "\n";
        }
    }else{
        int cont = contRed(true);
        string nomArchivo = "red" + to_string(cont) + ".csv";

        //Abrir el archivo de la red
        red.open(nomArchivo);
        if(!red){
            cout << u8"\n\t El archivo no se abrió correctamente.";
            return false;
        }

        /* GUARDAR LOS NODOS EN EL CSV */
        //Encabezados
        red << "#NODOS\n";
        red << "N;idNodo;nombre\n";

        for(const Nodo& n: nNodos.getNodos()){
            red << "N;" << n.id << ";" << n.nombre << "\n";
        }

        /* GUARDAR LAS ARISTAS EN EL CSV */
        //Encabezados
        red << "#ARISTAS (dirigidas)\n";
        red << "E;origen;destino;peso\n";

        for(const Arista& a: aristas){
            red << "E;" << a.origen << ";" << a.destino << ";" << a.peso << "\n";
        }
    }

    red.close();
    cout << u8"\n\tEl archivo fue guardado correctamente.";
    return true;
}

/* GUARDAR LAS MODIFICACIONES DEL ARCHIVO DE UNA RED YA EXISTENTE*/
void modificarRed(const string nomArchivo, HashRed& nNodos, vector <Arista>& aristas){
    fstream red;
    //Abrir el archivo de la red
    red.open(nomArchivo, ios::out|ios::trunc);
    if(!red){
        cout << u8"\n\t El archivo no se abrió correctamente.";
        return;
    }

    /* GUARDAR LOS NODOS EN EL CSV */
    //Encabezados
    red << "#NODOS\n";
    red << "N;idNodo;nombre\n";

    for(const Nodo& n: nNodos.getNodos()){
        red << "N;" << n.id << ";" << n.nombre << "\n";
    }

    /* GUARDAR LAS ARISTAS EN EL CSV */
    //Encabezados
    red << "#ARISTAS (dirigidas)\n";
    red << "E;origen;destino;peso\n";

    for(const Arista& a: aristas){
        red << "E;" << a.origen << ";" << a.destino << ";" << a.peso << "\n";
    }

    red.close();
    cout << u8"\n\tEl archivo fue guardado correctamente.";
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


