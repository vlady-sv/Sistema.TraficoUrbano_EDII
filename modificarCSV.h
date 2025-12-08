#ifndef MODIFICARCSV_H
#define MODIFICARCSV_H
#include "verificar_contarCSV.h"
using namespace std;

void agregarNodos(HashRed&, bool);
void modificarRed(const string, HashRed&, vector <Arista>&);
void guardarRed();
void guardarRed(HashRed&, vector <Arista>&);
void agregarAristas(const HashRed&, vector<Arista>&);
void eliminarNodos(HashRed&, vector<Arista>&);
void eliminarAristas(vector<Arista>&);

//Función auxiliar para saber a qué función llamar y solo usar los atributos necesario
void distribuirRed(const string nomArchivo, bool nueva, bool saveAs, string accion, string objeto){
    HashRed nNodos;
    vector <Arista> aristas;

    csvRed(nomArchivo, nNodos, aristas); //Se obtienen los elementos contenidos en el archivo
    //Separamos segun al accion que se quiera realizar
    if(accion == "agregar"){
        if(objeto == "nodos"){ //Tambien separamos segun el objeto
            agregarNodos(nNodos, nueva); //Dependiendo de la accion y el objeto solo se manda lo necesario
            if(!nueva || !saveAs) modificarRed(nomArchivo, nNodos, aristas);
            guardarRed(nNodos, aristas);
        }else if(objeto == "aristas"){
            agregarAristas(nNodos, aristas);
            if(!nueva || !saveAs)  modificarRed(nomArchivo, nNodos, aristas);
            guardarRed(nNodos, aristas);

        }
    }else if(accion == "eliminar"){
        if(objeto == "nodos"){
            eliminarNodos(nNodos, aristas);
            if(!nueva || !saveAs) modificarRed(nomArchivo, nNodos, aristas);
            guardarRed(nNodos, aristas);
        }else if(objeto == "aristas"){
            eliminarAristas(aristas);
            if(!nueva || !saveAs) modificarRed(nomArchivo, nNodos, aristas);
            guardarRed(nNodos, aristas);
        }
    }
}

//Verificacion de valores correctos
bool verificarValor(int cont, int opc){
    if(opc < 0 || opc >= cont){
        cout << u8"\n\n\t Opción inválida.";
        return false;
    }
    return true;
}

/* OPCIONES DE AGREGAR Y ELIMINAR DE LA RED */

//Preguntar por los nodos que se quieren agregar

void agregarNodos(HashRed& nNodos, bool nueva){
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
    cout << u8"\n\t Cuántos nodos deseas agregar: ";
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

void agregarAristas(const HashRed& nNodos, vector<Arista>& aristas){
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
        cout << "\n\t Los nodos actuales en el archivo son: ";
        for(const auto& n: nNodos.getNodos()){
            cout << "\n\tId: " << n.id << " | Nombre: " << n.nombre;
        }

        cout << "\n\t Escribe el ID del nodo que deseas eliminar: ";
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

void eliminarAristas(vector<Arista>& aristas){
    char resp;
    int origenEliminar, destinoEliminar, pesoEliminar, aristaEliminar, nAristas = 1;
    do{
        cout << "\n\t Las aristas actuales en el archivo son: ";
        for(const auto& a: aristas){
            cout << "\n\t Origen: " << a.origen << " | Destino: " << a.destino << " | Peso: " << a.peso;
            nAristas++;
        }

        do{
            cout << "\n\t Esctiba el origen de la arista que desea eliminar: ";
            cin >> origenEliminar;
        }while(origenEliminar < 1 && origenEliminar > nAristas);

        int cont = 1;
        for(const auto& a: aristas){
            if(a.origen == origenEliminar){ //Mostramos solo las aristas que tengan el origen seleccionado por el usuario
                cout << "\n\t [" << cont << "]" <<" Origen: " << a.origen << " | Destino: " << a.destino << " | Peso: " << a.peso;
                cont++;
            }
        }

        do{
            cout << "\n\n\t Elija la arista que desea eliminar: ";
            cin >> aristaEliminar;
        }while(aristaEliminar < 1 && aristaEliminar > cont);

        //Buscamos la arista apoyandonos de cont
        cont = 1;
        for(const auto& a: aristas){
            if(a.origen == origenEliminar){
                if(cont == aristaEliminar){ //Mostramos solo las aristas que tengan el origen seleccionado por el usuario
                    destinoEliminar = a.destino;
                    pesoEliminar = a.peso;
                    break;
                }
                cont++;
            }
        }
        

        //Se busca la aristas que tuvieran conexión con el nodo y también se eliminan
        for(size_t i=0; i<aristas.size(); ++i){
            if(aristas[i].origen == origenEliminar && aristas[i].destino == destinoEliminar && aristas[i].peso == pesoEliminar){
                aristas.erase(aristas.begin() + i);
                i--;
            }
        }

        cout << "\n\t La arista con: \n" << 
        "\t Origen: " << origenEliminar << " | Destino: " << destinoEliminar << " | Peso: " << pesoEliminar;
        cout << "\n\n\t Ha sido eliminada.";
        
        do{
            cout << "\n\t Desea eliminar otra arista? [S/N]: ";
            cin.ignore();
            cin >> resp;
        }while(resp != 's' && resp != 'S' && resp != 'n' && resp != 'N');
    }while(resp == 's' || resp == 'S');
}

/* (SOBRECARGADA) CREAR RED DESDE CERO*/
void guardarRed(){
    if(!verificarCRed()){
        crearContRed();
    }

    fstream red;
    HashRed nNodos;
    vector<Arista> aristas;
    int cont = contRed(true);
    string nomArchivo = "red" + to_string(cont) + ".csv";

    //Preguntar por los nodos
    agregarNodos(nNodos, true);

    //Preguntar por las aristas
    agregarAristas(nNodos, aristas);

    //Abrir el archivo de la red
    red.open(nomArchivo, ios::out);
    if(!red){
        cout << u8"\n\t El archivo no se abrió correctamente.";
        return;
    }

    /* GUARDAR LOS NODOS EN EL CSV */
    //Encabezados
    red << "#NODOS\n";
    red << "#N;idNodo;nombre\n";

    for(const Nodo& n: nNodos.getNodos()){
        red << "N;" << n.id << ";" << n.nombre << "\n";
    }

    /* GUARDAR LAS ARISTAS EN EL CSV */
    //Encabezados
    red << "#ARISTAS (dirigidas)\n";
    red << "#E;origen;destino;peso\n";

    for(const Arista& a: aristas){
        red << "E;" << a.origen << ";" << a.destino << ";" << a.peso << "\n";
    }
    
    red.close();
    cout << "\n\tEl archivo fue guardado correctamente.";
}

/* (SOBRECARGADA) GUARDAR COMO UNA NUEVA A PARTIR DE OTRA*/
void guardarRed(HashRed& nNodos, vector <Arista>& aristas){
    if(!verificarCRed()){
        crearContRed();
    }

    fstream red;
    
    int cont = contRed(true);
    string nomArchivo = "red" + to_string(cont) + ".csv";

    //Abrir el archivo de la red
    red.open(nomArchivo, ios::out);
    if(!red){
        cout << u8"\n\t El archivo no se abrió correctamente.";
        return;
    }

    /* GUARDAR LOS NODOS EN EL CSV */
    //Encabezados
    red << "#NODOS\n";
    red << "#N;idNodo;nombre\n";

    for(const Nodo& n: nNodos.getNodos()){
        red << "N;" << n.id << ";" << n.nombre << "\n";
    }

    /* GUARDAR LAS ARISTAS EN EL CSV */
    //Encabezados
    red << "#ARISTAS (dirigidas)\n";
    red << "#E;origen;destino;peso\n";

    for(const Arista& a: aristas){
        red << "E;" << a.origen << ";" << a.destino << ";" << a.peso << "\n";
    }

    red.close();
    cout << u8"\n\tEl archivo fue guardado correctamente.";
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
    red << "#N;idNodo;nombre\n";

    for(const Nodo& n: nNodos.getNodos()){
        red << "N;" << n.id << ";" << n.nombre << "\n";
    }

    /* GUARDAR LAS ARISTAS EN EL CSV */
    //Encabezados
    red << "#ARISTAS (dirigidas)\n";
    red << "#E;origen;destino;peso\n";

    for(const Arista& a: aristas){
        red << "E;" << a.origen << ";" << a.destino << ";" << a.peso << "\n";
    }

    red.close();
    cout << u8"\n\tEl archivo fue guardado correctamente.";
}

/* OPCIONES PARA VEHICULOS */

/* (SOBRECARGADA) Solo verificar formato de placa*/
bool verificarPlaca(const string placa){
    bool correcto = true;
    //Primero se verifica el formato 'AAA000'
    if(!(placa.size() == 6)) correcto = false;
    if(isdigit(placa[0])) correcto = false;
    if(isdigit(placa[1])) correcto = false;
    if(isdigit(placa[2])) correcto = false;
    if(!(isdigit(placa[3]))) correcto = false;
    if(!(isdigit(placa[4]))) correcto = false;
    if(!(isdigit(placa[5]))) correcto = false;
    
    if(correcto == false){
        cout << "\n\t Error: El formato de la placa es incorrecto.";
        return false;
    }

    return true;
}

/* (SOBRECARGADA) Verificar el formato de placa y verificar que no se repita*/
bool verificarPlaca(const string placa, const vector<Vehiculo> vehiculos){
    bool correcto = true;
    //Primero se verifica el formato 'AAA000'
    if(!(placa.size() == 6)) correcto = false;
    if(isdigit(placa[0])) correcto = false;
    if(isdigit(placa[1])) correcto = false;
    if(isdigit(placa[2])) correcto = false;
    if(!(isdigit(placa[3]))) correcto = false;
    if(!(isdigit(placa[4]))) correcto = false;
    if(!(isdigit(placa[5]))) correcto = false;
    
    if(correcto == false){
        cout << "\n\t Error: El formato de la placa es incorrecto.";
        return false;
    }
    
    //Si el formato fue correcto se verifica que no haya otro vehiculo con dicha placa
    for(const Vehiculo& v: vehiculos){
        if(v.placa == placa){
            cout << u8"\n\t Error: Ya hay un vehículo registrado con la placa " << placa;
            return false;
        }   
    }

    //Si no se dio ninguno de los casos anteriores la placa es valida
    return true;
}

void llenarVehiculos(Vehiculo& v, const vector<Vehiculo> vehiculos){
        bool placaCorrecta;
        do{
            cout << "\n\t Ingresa la placa del vehiculo (Formato AAA000): ";
            cin >> v.placa;
            placaCorrecta = verificarPlaca(v.placa, vehiculos);
        }while(!placaCorrecta);
        int tVh;
        do{
            cout << u8"\n\t [1] Partícular";
            cout << u8"\n\t [2] Transporte";
            cout << "\n\t Escoja el tipo de vehículo: ";
            cin >> tVh;
        }while(tVh != 1 && tVh != 2);
        if(tVh == 1) v.tipo = "Partícular";
        else v.tipo = "Transporte";
        cout << u8"\n\t Ingresa el nodo de origen del vehículo: ";
        cin >> v.origen;
        cout << u8"\n\t Ingresa el nodo de destino del vehículo: ";
        cin >> v.destino;
        cout << u8"\n\t Ingresa la hora de entrada del vehículo: ";
        cin >> v.horaEntrada;
}


//Eliminar vehiculos
void agregarVehiculos(const string nomArchivo){
    HashVehiculos hsVh;
    vector<Vehiculo> vehiculos;
    vector<Vehiculo> nuevosVehiculos;
    csvVehiculos(nomArchivo, hsVh, vehiculos);
    int nVehiculos; 
    int lastId;

    for(const Vehiculo& v: vehiculos){
        lastId = v.id;
    }

    int idInicial = lastId + 1;
    cout << u8"\n\t Cuántos vehículos desea ingresar: ";
    cin >> nVehiculos;
    for(int i=idInicial; i<=nVehiculos; ++i){
        cout << u8"\n\t -- Vehículo " << i << " --";
        Vehiculo v;
        v.id = i;
        llenarVehiculos(v, vehiculos);
        nuevosVehiculos.push_back(v);
    }

    fstream archVh;
    archVh.open(nomArchivo, ios::out|ios::app);

    //Ingresar los nuevos vehiculos al final del CSV
    for(const Vehiculo& v: nuevosVehiculos){
        archVh << "V;" << v.id << ";" << v.placa << ";" << v.tipo << ";" << v.origen << ";" << v.destino << ";" << v.horaEntrada << "\n";
    }

    archVh.close();
    cout << u8"\n\t Los vehículos se agregaron correctamente al archivo: " << nomArchivo;
}

void eliminarVehiculos(const string nomArchivo){
    HashVehiculos hashVh;
    vector<Vehiculo> vehiculos;
    csvVehiculos(nomArchivo, hashVh, vehiculos);
    int vEliminar;
    char resp; 

    do{
        if(vehiculos.empty()){ //Si el vector esta vacio ya no hay vehiculos para eliminar
            cout << "\n\t No hay vehículos en el archivo.";
            return;
        }
        int i = 1;
        cout << u8"\n\t Los vehículos contenidos en el archivo son: ";
        for(const Vehiculo& v: vehiculos){ //Mostrar todo los vehiculos
            cout << "\n\t [" << i << "] | Id: " << v.id << " | Placa: " << v.placa << " | Tipo: " << v.tipo << " | Origen: " << v.origen << " | Destino: " 
                << v.destino << " | Hora de entrada: " << v.horaEntrada;
            i++;
        }
        
        do{
            cout << u8"\n\t Qué vehículo desea eliminar: ";
            cin >> vEliminar;

            if(vEliminar < 1 || vEliminar > i) cout << u8"\n\t Error. Opción fuera de rango."; //Verificar que este dentro del rango de vehiculos que le mostramos
        }while(vEliminar < 1 && vEliminar > i);

         
        do{
            cout << "\n\t Desea eliminar otro vehículo?  [S/N]: ";
            cin.ignore();
            cin >> resp;
        }while(resp != 's' && resp != 'S' && resp != 'n' && resp != 'N');
    }while(resp == 's' || resp == 'S');

    fstream archVh;
    archVh.open(nomArchivo, ios::out|ios::trunc);
    if(!archVh){
        cout << u8"\n\t El archivo no se abrió correctamente.";
        return;
    }

    //Actualizar los id de todos los vehiculos restantes para evitar dejar huecos
    for(size_t i=0; i<vehiculos.size(); ++i){
        vehiculos[i].id = i;
    }

    /* GUARDAR LOS VEHICULOS EN EL CSV */
    //Encabezados
    archVh << "#V;id;placa;tipo;origen;destino;horaEntrada\n";

    //Vehiculos
    for(const Vehiculo& v: vehiculos){
        archVh << "V;" << v.id << ";" << v.placa << ";" << v.tipo << ";" << v.origen << ";" << v.destino << ";" << v.horaEntrada << "\n";
    }
    
    archVh.close();
    cout << u8"\n\t Los vehículos fueron eliminados correctamente, y los Id fueron actualizados.";
}

void buscarVehiculos(const string nomArchivo){
    HashVehiculos hashVh;
    vector<Vehiculo> vehiculos;
    csvVehiculos(nomArchivo, hashVh, vehiculos);
    int opc;

    if(vehiculos.empty()){
        cout << u8"\n\t El archivo no contiene vehículos, no se puede buscar.";
        return;
    }
    do{
        cout << "\n\t [1] Buscar por Id";
        cout << "\n\t [2] Buscar por placa";
        cin >> opc;

        switch(opc){
            case 1:{
                    int id;
                    cout << "\n\t Ingresa el Id el vehículo a buscar: ";
                    cin >> id;
                    Vehiculo* v = hashVh.buscar(id);
                    if(v == nullptr){
                        cout << u8"\n\t El vehículo con el Id " << id << " no se encuentra en el archivo.";
                    }else{
                        cout << u8"\n\t -- Vehículo --";
                        cout << "\n\t Id: " << v->id << " | Placa: " << v->placa << " | Tipo: " << v->tipo << " | Origen: " << v->origen << " | Destino: " 
                            << v->destino << " | Hora de entrada: " << v->horaEntrada;
                    }
                }
                break;
            case 2:{
                    bool encontrado = false, formatoCorrecto;
                    Vehiculo vBuscado;
                    string placa;

                    do{
                        cout << u8"\n\t Ingresa la placa del vehículo a buscar (Formato AAA000): ";
                        cin >> placa;
                        formatoCorrecto = verificarPlaca(placa);
                    }while(!formatoCorrecto);

                    for(const Vehiculo& v: vehiculos){
                        if(v.placa == placa){ //Comparamos vehiculo por vehiculo para ver si la placa coincide
                            encontrado = true;
                            vBuscado = v;
                            break;
                        }
                    }

                    if(!encontrado){ //Si se mantuvo en false sabemos que no se encontro el vehiculo con la placa dada por el usuario
                        cout << u8"\n\t El vehículo con la placa " << placa << " no se encuentra en el archivo.";
                    }else{
                        cout << u8"\n\t -- Vehículo --";
                        cout << "\n\t Id: " << vBuscado.id << " | Placa: " << vBuscado.placa << " | Tipo: " << vBuscado.tipo << " | Origen: " << vBuscado.origen << " | Destino: " 
                            << vBuscado.destino << " | Hora de entrada: " << vBuscado.horaEntrada;
                    }
                }
                break;
            default: cout << u8"\n\n\t Opción inválida.\n";
                break;
        }
    }while(opc != 1 && opc != 2);
}

void crearNuevoVehiculos(){
    if(!verificarCVehiculos()){
        crearContVehiculos();
    }
    int cont = contVehiculos(false);
    string nomArchivo = "vehiculos" + to_string(cont) + ".csv";

    HashVehiculos hashVh;
    vector <Vehiculo> vehiculos;
    int nVehiculos;
    cout << u8"\n\t Cuántos vehículos desea ingresar: ";
    cin >> nVehiculos;

    for(int i=0; i<nVehiculos; ++i){
        cout << "\n\t -- Vehiculo " << i+1 << " --";
        Vehiculo v;
        v.id= i;
        llenarVehiculos(v, vehiculos);
        vehiculos.push_back(v);
    }

    fstream archVh;
    archVh.open(nomArchivo, ios::out);
    if(!archVh){
        cout << u8"\n\t El archivo no se abrió correctamente.";
        return;
    }

    /* GUARDAR LOS VEHICULOS EN EL CSV */
    //Encabezados
    archVh << "#V;id;placa;tipo;origen;destino;horaEntrada\n";

    //Vehiculos
    for(const Vehiculo& v: vehiculos){
        archVh << "V;" << v.id << ";" << v.placa << ";" << v.tipo << ";" << v.origen << ";" << v.destino << ";" << v.horaEntrada << "\n";
    }
    
    archVh.close();
    cout << u8"\n\t El archivo fue creado correctamente";
}
#endif