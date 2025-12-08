#ifndef TABLAS_HASH
#define TABLAS_HASH
#include <iostream>
#include <vector>
#include <list>
#include <string>
using namespace std;

/* MANEJO DE TABLA HASH DE LA RED DE NODOS Y ARISTAS */

struct Nodo{
    int id;
    string nombre;

    Nodo(int i = -1, const string& nom = "")
        : id(i), nombre(nom) {}
};

struct Arista{
    int origen;
    int destino;
    float peso;
};

class HashRed{
    private:
        vector<list<Nodo>> tabla;
        size_t capacidad;

        size_t hashID(int id) const{
            return id % capacidad;
        }
    public:
        HashRed(size_t cap = 100) : tabla(cap), capacidad(cap) {}

        void insertar(const Nodo& n){
            size_t idx = hashID(n.id);

            for(auto& nd: tabla[idx]){
                if(nd.id == n.id){
                    nd = n;
                    return;
                }
            }
            tabla[idx].push_back(n);
        }

        Nodo* buscar(const int& id){
            size_t idx = hashID(id);
            for(auto& nd: tabla[idx]){
                if(nd.id == id) return &nd;
            }
            return nullptr;
        }

        void imprimirDebug() const{
            for(size_t i=0; i<capacidad; ++i){
                cout << "\n\t Bucket " << i << ": ";
                for(const auto& nd : tabla [i]){
                    cout << "[ " << nd.id << " | " << nd.nombre << " ]";
                }
                cout << "\n";
            }
        }

        bool eliminar(int id){
            size_t idx = hashID(id);

            for(auto i = tabla[idx].begin(); i != tabla[idx].end(); ++i){
                if(i->id == id){
                    tabla[idx].erase(i);
                    return true;
                }
            }
            return false;
        }

        vector<Nodo> getNodos()const{
            vector<Nodo> nodos;

            for(const auto& bucket: tabla){
                for(const auto& nodo: bucket){
                    nodos.push_back(nodo);
                }
            }

            return nodos;
        }

};

/* MANEJO DE TABLA HASH DE VEHICULOS */
struct Vehiculo{
    string placa;
    string tipo;
    int id;
    int destino;
    size_t horaEntrada;

    Vehiculo(string p = "", string t = "", int i = -1, int d = -1, size_t hE= 0.0)
        : placa(p), tipo(t), id(i), destino(d), horaEntrada(hE) {}
};

class HashVehiculos{
    private:
        vector<list<Vehiculo>> tabla;
        size_t capacidad;

        size_t hashID(int id) const{
            return id % capacidad;
        }
    public:
        HashVehiculos(size_t cap = 100) : tabla(cap), capacidad(cap) {}
        
        void insertar(const Vehiculo& v){
            size_t idx = hashID(v.id);

            for(auto& vh: tabla[idx]){
                if(vh.id == v.id){
                    vh = v;
                    return;
                }
            }
            tabla[idx].push_back(v);
        }

        Vehiculo* buscar(const int& id){
            size_t idx = hashID(id);
            for(auto& vh: tabla[idx]){
                if(vh.id == id) return &vh;
            }
            return nullptr;
        }

        void imprimirDebug() const{
            for(size_t i=0; i<capacidad; ++i){
                cout << "\n\t Bucket " << i << ": ";
                for(const auto& nd : tabla [i]){
                    cout << "[ " << nd.id << " | " << " ]";
                }
                cout << "\n";
            }
        }
};

#endif