#include <iostream>
#include <fstream>
using namespace std;

//////// Lógica para el conteo de los archivos .csv ////////////////////

/* PARA LA RED DE NODOS */
int crearContRed(){ //Creacion del archivo contador para la cantidad de archivos de Red
    fstream cRed;
    cRed.open("ContRed.dat", ios::binary|ios::out);
    if(!cRed){
        cout << "\n\t El archivo no se creo correctamente.";
        cin.get();
        return -1;
    }
    int primero = 1;
    cRed.write(reinterpret_cast<char*>(&primero), sizeof(int));
    cRed.close();
    return 1;
}

bool verificarCRed(){ //Verificacion de existencia del archivo contador de archivos de red
    fstream cRed("ContRed.dat", ios::binary|ios::in);
    if(!cRed) return false;
    return true;
}

int contRed(bool aumentar){ //Leemos en que numero de archivo en que vamos y aumentamos el contador
    fstream cRed;
    int cont = 0;
    cRed.open("ContRed.dat", ios::binary|ios::in|ios::out);
    if(!cRed){
        cout << "\n\t El archivo no se abrio correctamente.";
        cin.get();
        return -1;
    }

    cRed.seekg(-sizeof(int), ios::end);
    if(!cRed.read(reinterpret_cast<char*>(&cont), sizeof(int))){
        cRed.clear();
        cont = 0;
    }

    if(aumentar){
        cont++;
        cRed.seekp(0, ios::end);
        cRed.write(reinterpret_cast<char*>(&cont), sizeof(int));
        cRed.close();
    }

    return cont;
}

/* PARA LOS VEHICULOS */
int crearContVehiculos(){
    fstream cVehiculos;
    cVehiculos.open("ContVehiculos.dat", ios::binary|ios::out);
    if(!cVehiculos){
        cout << "\n\t El archivo no se creo correctamente.";
        cin.get();
        return -1;
    }
    int primero = 1;
    cVehiculos.write(reinterpret_cast<char*>(&primero), sizeof(int));
    cVehiculos.close();
    return 1;
}

bool verficarCVehiculos(){
    fstream cVehiculos("ContVehiculos.dat", ios::binary|ios::in);
    if(!cVehiculos) return false;
    return true;
}

int contVehiculos(){
    fstream cVehiculos;
    int cont = 0;
    cVehiculos.open("ContVehiculos.dat", ios::binary|ios::in|ios::out);
    if(!cVehiculos){
        cout << "\n\t El archivo no se abrio correctamente.";
        cin.get();
        return -1;
    }

    cVehiculos.seekg(-sizeof(int), ios::end);
    if(!cVehiculos.read(reinterpret_cast<char*>(&cont), sizeof(int))){
        cVehiculos.clear();
        cont = 0;
    }

    cont++;
    cVehiculos.seekp(0, ios::end);
    cVehiculos.write(reinterpret_cast<char*>(&cont), sizeof(int));
    cVehiculos.close();

    return cont;
}