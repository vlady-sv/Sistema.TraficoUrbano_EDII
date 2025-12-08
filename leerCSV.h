#ifndef LEERCSV_H
#define LEERCSV_H
#include <fstream>
#include <sstream>
#include "TablasHash.h"
using namespace std;

/* LEER ARCHIVO .CSV DE RED DE NODOS*/
void csvRed(const string& archivo, HashRed& hashRed, vector<Arista>& aristas){
    fstream red(archivo);
    if(!red){
        cout << "\n\t Error al abrir el archivo";
        return;
    }

    string linea;
    while(getline(red, linea)){
        if(linea.empty()) continue;
        if(linea[0] == '#') continue;

        stringstream ss(linea);
        string tipo;
        getline(ss, tipo, ';'); //Obtiene el tipo de dato que se maneja N o E

        if(tipo == "N"){
            string stringId, nombre;
            getline(ss, stringId, ';');
            getline(ss, nombre);

            int id = stoi(stringId);
            hashRed.insertar(Nodo(id, nombre));
        }else if(tipo == "E"){
            string sOrigen, sDestino, sPeso;

            getline(ss, sOrigen, ';');
            getline(ss, sDestino, ';');
            getline(ss, sPeso);

            Arista a;
            a.origen = stoi(sOrigen);
            a.destino = stoi(sDestino);
            a.peso = stof(sPeso);

            aristas.push_back(a);
        }
    }
}

/* LEER ARCHIVO .CSV DE VEHICULOS */

void csvVehiculos(const string& archivo, HashVehiculos& hashVe, vector<Vehiculo>& vehiculos){
    fstream vehic(archivo);
    if(!vehic){
        cout << "\n\t Error al abrir el archivo";
        return;
    }

    string linea;
    while(getline(vehic, linea)){
        if(linea.empty()) continue;
        if(linea[0] == '#') continue;

        stringstream ss(linea);
        string tipoRegistro;
        getline(ss, tipoRegistro, ';'); // Saca la V del principio para que no errores

        if(tipoRegistro != "V") continue;

        string sId, sPlaca, sTipo, sOrigen, sDestino, sHoraEnt;

            getline(ss, sId, ';');
            getline(ss, sPlaca, ';');
            getline(ss, sTipo, ';');
            getline(ss, sOrigen, ';');
            getline(ss, sDestino, ';');
            getline(ss, sHoraEnt);

            Vehiculo v;
            v.id = stoi(sId);
            v.placa = sPlaca;
            v.tipo = sTipo;
            v.origen = stoi(sOrigen);
            v.destino = stoi(sDestino);
            v.horaEntrada = sHoraEnt;
            vehiculos.push_back(v);
            hashVe.insertar(Vehiculo(v));
    }
}
#endif