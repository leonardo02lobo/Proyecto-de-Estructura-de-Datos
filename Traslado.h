#ifndef TRASLADO_H
#define TRASLADO_H

#include <iostream>
#include <string>
#include <ctime>
#include <fstream>
#include <vector>
#include "Usuario.h"
#include "Sectores.h"
#include "Cola.h"
#include "Lista.h"
#include "Grafo.h"

using namespace std;

/**
 * Clase que representa el sistema de traslado de usuarios.
 * Permite solicitar un traslado y finalizarlo, gestionando la disponibilidad de vehï¿½culos.
 */
class Traslado {
public:
	
	Traslado(Cola*& colaSectores,Cola**& frente,Cola**& final,Lista*& lista);
    /**
     * Solicita un traslado para un usuario.
     * @param sectores Referencia a la clase Sectores que contiene la informaciï¿½n de los sectores disponibles.
     */
    void solicitar(Sectores& sectores);

    /**
     * Finaliza un traslado y actualiza la disponibilidad del vehï¿½culo.
     * @param placaVehiculo Placa del vehï¿½culo a marcar como disponible.
     */
    void finalizarTraslado(const string& placaVehiculo);
    
    void GuardarInformacionUsuarios(int cedula);
    
    void RevisarCola(int id);
    void RevisarLista(int id);

private:
    Usuario _usuario;       ///< Usuario que solicita el traslado.
    Sector _sectorOrigen;   ///< Sector de origen del traslado.
    Sector _sectorDestino;  ///< Sector de destino del traslado.
    string _fecha;  	///< Fecha en la que se solicita el traslado
	Cola* colaSectores;
	Cola** frente;
	Cola** final;
	Lista* lista;
	int idOrigenSeleccionado;
	Grafo* grafo;

    /**
     * Carga los datos del usuario a partir de su cï¿½dula.
     * @param cedula Cï¿½dula del usuario a buscar.
     * @return true si el usuario fue encontrado, false en caso contrario.
     */
    bool cargarUsuarioPorCedula(int cedula);

    /**
     * Selecciona un vehï¿½culo disponible en el sector de origen.
     * @param sectores Referencia a la clase Sectores que contiene la informaciï¿½n de los sectores disponibles.
     */
    void seleccionarVehiculo(Sectores& sectores);
};
Traslado::Traslado(Cola*& colaSectores,Cola**& frente,Cola**& final,Lista*& lista)
	 : colaSectores(colaSectores), frente(frente), final(final),lista(lista) {
}
/**
 * Implementaciï¿½n del mï¿½todo solicitar que permite a un usuario solicitar un traslado.
 */
void Traslado::solicitar(Sectores& sectores) {
    bool band1 = false, band2 = false;
    cout << "Solicitar Traslado" << endl;

    // Solicitar datos del usuario y sectores
    string cedula;
    cout << "Ingrese la cedula del usuario: ";
    cin >> cedula;
    int cedulaInt = atoi(cedula.c_str());
    GuardarInformacionUsuarios(cedulaInt);

    cout << "Ingrese el ID del sector de origen. Ejemplo: ID#: ";
    string idSectorOrigen;
    cin >> idSectorOrigen;
    _sectorOrigen.setId(idSectorOrigen);

    cout << "Ingrese el ID sector de destino. Ejemplo: ID#: ";
    string idSectorDestino;
    cin >> idSectorDestino;
    _sectorDestino.setId(idSectorDestino);

    // Verificar que los sectores existen
    for (int i = 0; i < sectores.idSectores.size(); i++) {
        if (sectores.idSectores[i] == _sectorOrigen.getId()) {
            _sectorOrigen.setNombreSector(sectores.sectores[i]);
            band1 = true;
        }
        if (sectores.idSectores[i] == _sectorDestino.getId()) {
            _sectorDestino.setNombreSector(sectores.sectores[i]);
            band2 = true;
        }
    }

    if (!band2) {
        cout << "El ID del sector de destino no coincide con alguno dado. Por favor intentar más tarde." << endl;
        return;
    }

    // Cálculo de la ruta mínima desde el sector de origen hasta el destino
    int idOrigen = atoi(_sectorOrigen.getId().substr(2).c_str());
    int idDestino = atoi(_sectorDestino.getId().substr(2).c_str());

    pair<vector<DatosGrafos>, int> resultado = grafo->dijkstra(idOrigen, idDestino);
    vector<DatosGrafos> ruta = resultado.first;
    int distancia = resultado.second;

    if (ruta.empty()) {
        cout << "No hay ruta disponible entre los sectores seleccionados." << endl;
        return;
    }

    // Mostrar la ruta mínima usando un for simple
	cout << "Ruta minima: ";
	for (int i = 0; i < ruta.size(); i++) {
	    cout << "ID llegada: " << ruta[i].getIDSectorLlegada() 
	         << ", ID Destino: " << ruta[i].getIDSectorDestino() 
	         << ", Km: " << ruta[i].getDistancia() << " -> ";
	}
	cout << "\b\b\b   \n";  // Elimina la última flecha innecesaria
	cout << "Distancia total: " << distancia << " km" << endl;


    // Asignar fecha del traslado
    time_t now = time(0);
    _fecha = ctime(&now);

    // Buscar vehículo disponible en la mejor ruta posible
    idOrigenSeleccionado = atoi(idSectorDestino.substr(2).c_str()) - 1;
    seleccionarVehiculo(sectores);

    Usuario u;
    u.actualizarUsoApp(cedula);
}


void Traslado::GuardarInformacionUsuarios(int cedula){
	ifstream archivo("Datos Usuarios.txt");
	if (!archivo.is_open()) {
        cout << "Error al abrir el archivo de usuarios." << endl;
        return;
    }
    
    string linea;
    archivo.seekg(0);
    while (getline(archivo, linea)) {
        char* lineaChar = const_cast<char*>(linea.c_str());
        char* cedulaStr = strtok(lineaChar, ":");
        int cedulaArchivo = atoi(cedulaStr);

        if (cedulaArchivo == cedula) {
            _usuario.setCedula(cedulaArchivo);
            _usuario.setNombre(strtok(NULL, ":"));
            _usuario.setDireccion(strtok(NULL, ":"));
            archivo.close();
            return;
        }
    }

    archivo.close();
}

/**
 * Carga los datos del usuario a partir de su cï¿½dula desde el archivo de usuarios.
 * @param cedula Cï¿½dula del usuario a buscar.
 * @return true si el usuario fue encontrado, false en caso contrario.
 */
bool Traslado::cargarUsuarioPorCedula(int cedula) {
    ifstream archivo("Datos Usuarios.txt");
    if (!archivo.is_open()) {
        cout << "Error al abrir el archivo de usuarios." << endl;
        return false;
    }

    string linea;
    archivo.seekg(0);
    while (getline(archivo, linea)) {
        char* lineaChar = const_cast<char*>(linea.c_str());
        char* cedulaStr = strtok(lineaChar, ":");
        int cedulaArchivo = atoi(cedulaStr);

        if (cedulaArchivo == cedula) {
            _usuario.setCedula(cedulaArchivo);
            _usuario.setNombre(strtok(NULL, ":"));
            _usuario.setDireccion(strtok(NULL, ":"));
            archivo.close();
            return true;
        }
    }

    archivo.close();
    return false;
}

/**
 * Selecciona un vehï¿½culo disponible en el sector de origen.
 * @param sectores Referencia a la clase Sectores que contiene la informaciï¿½n de los sectores disponibles.
 */
void Traslado::seleccionarVehiculo(Sectores& sectores) {
	Lista* listaTemp = NULL;

    ifstream archivo("Datos Vehiculo.txt", ios::in);
    bool disponible = false;

    if (!archivo.is_open()) {
        cout << "Error al abrir el archivo de vehï¿½culos." << endl;
        return;
    }

    string linea;
    vector<string> placasDisponibles;

    // Buscar vehï¿½culos disponibles
    while (getline(archivo, linea)) {
        char* lineaChar = const_cast<char*>(linea.c_str());
        char* idSectorChar = strtok(lineaChar, ":");
        char* nombreSector = strtok(NULL, ":");
        char* cedula = strtok(NULL, ":");
        char* nombreConductor = strtok(NULL, ":");
        char* placa = strtok(NULL, ":");
        char* modelo = strtok(NULL, ":");
        char* marca = strtok(NULL, ":");
        char* anio = strtok(NULL, ":");
        char* disponibilidad = strtok(NULL, ":");

        if (disponibilidad != "1") {  // Verifica que el vehï¿½culo estï¿½ disponible
            Chofer chofer(nombreConductor,atoi(cedula));
            Sector sector(idSectorChar,nombreSector);
            string placaString = placa;
            string modeloString = modelo;
            string marcaString = marca;
            Vehiculo vehiculoDisponible(placaString,modeloString,marcaString,atoi(anio),chofer,sector,true);
            lista[idOrigenSeleccionado].insertarInicio(listaTemp,vehiculoDisponible);
            placasDisponibles.push_back(placa);  // Guarda la placa para identificar el vehï¿½culo despuï¿½s
            disponible = true;
        }
    }
    archivo.close();

    if (!disponible) {
    	string idString =_sectorOrigen.getId();
    	int id = atoi(idString.substr(2).c_str()) - 1;
    	
    	colaSectores[id].InsertarElemento(frente[id],final[id],_usuario);
        cout << "No se encuentra ningun vehiculo disponible en el sector de origen." << endl;
        return;
    }

    cout << "\n\nVehiculos Disponibles." << endl << endl;
    lista[idOrigenSeleccionado].ordenarDescendente(listaTemp);
    lista[idOrigenSeleccionado].mostrar(listaTemp);

    // Permitir al usuario seleccionar el vehï¿½culo
    int seleccion;
    cout << "Seleccione el numero del vehiculo para iniciar el traslado: ";
    cin >> seleccion;
    // Validar la selecciï¿½n del usuario
    if (seleccion < 1 || seleccion > placasDisponibles.size()) {
        cout << "Seleccion invalida. Intente de nuevo." << endl;
        return;
    }

    // Actualizar la disponibilidad del vehï¿½culo seleccionado
    string placaSeleccionada = placasDisponibles[seleccion - 1];
    ifstream archivoLectura("Datos Vehiculo.txt", ios::in);
    ofstream archivoEscritura("Temp.txt", ios::out);
    string numeroDeVeces, NVecesFinal;

    while (getline(archivoLectura, linea)) {
        stringstream ss(linea);
        for (int i = 0; i < 10; i++) {
            getline(ss, numeroDeVeces, ':');
        }
        if (linea.find(placaSeleccionada) != string::npos) {
            stringstream ss2(numeroDeVeces);
            string token;
            getline(ss2, token, '_');
            string numero;
            getline(ss2, numero, '_');

            int numeroVeces = atoi(numero.c_str());
            numeroVeces++;

            ostringstream oss;
            oss << "N_" << numeroVeces;
            NVecesFinal = oss.str();
            // Cambia la disponibilidad a 0 en la lï¿½nea seleccionada
            size_t pos = linea.rfind(":1");
            if (pos != string::npos) linea.replace(pos, 2, ":0");

            size_t pos2 = linea.rfind(numeroDeVeces);
            if (pos2 != string::npos) linea.replace(pos2, numeroDeVeces.length(), NVecesFinal);
        }
        archivoEscritura << linea << endl;
    }

    archivoLectura.close();
    archivoEscritura.close();

    remove("Datos Vehiculo.txt");
    rename("Temp.txt", "Datos Vehiculo.txt");

    cout << "El vehiculo ha sido seleccionado y esta en camino." << endl;
    lista[idOrigenSeleccionado].BuscarVehiculo(listaTemp,seleccion-1);
}

/**
 * Finaliza un traslado y actualiza la disponibilidad del vehï¿½culo.
 * @param placaVehiculo Placa del vehï¿½culo a marcar como disponible.
 */
void Traslado::finalizarTraslado(const string& placaVehiculo) {
    // Buscar el sector de origen del vehículo
    int idSectorVehiculo = -1;
    ifstream archivoLectura("Datos Vehiculo.txt");
    string linea;

    while (getline(archivoLectura, linea)) {
        if (linea.find(placaVehiculo) != string::npos) {
            char* lineaChar = const_cast<char*>(linea.c_str());
            char* idSectorChar = strtok(lineaChar, ":");
            idSectorVehiculo = atoi(idSectorChar + 2); // Extrae el ID del sector
            break;
        }
    }
    archivoLectura.close();

    if (idSectorVehiculo == -1) {
        cout << "No se encontró el vehículo con la placa especificada." << endl;
        return;
    }

    // Buscar la ruta mínima de regreso a la base (Ejemplo: ID Base = 1)
    pair<vector<DatosGrafos>, int> resultado = grafo->dijkstra(idSectorVehiculo, 1);
    vector<DatosGrafos> ruta = resultado.first;
    int distancia = resultado.second;

    if (ruta.empty()) {
        cout << "No hay ruta disponible para el regreso del vehículo." << endl;
        return;
    }

    cout << "Ruta mínima de regreso: ";
    for (int i = 0; i < ruta.size(); i++) {
        cout << "ID llegada: " << ruta[i].getIDSectorLlegada() 
             << ", ID Destino: " << ruta[i].getIDSectorDestino() 
             << ", Km: " << ruta[i].getDistancia() << " -> ";
    }
    cout << "\b\b\b   \n";
    cout << "Distancia total: " << distancia << " km" << endl;

    // Actualizar el archivo de vehículos para marcar como disponible
    ifstream archivoLectura2("Datos Vehiculo.txt");
    ofstream archivoEscritura("Temp.txt");

    while (getline(archivoLectura2, linea)) {
        if (linea.find(placaVehiculo) != string::npos) {
            size_t pos = linea.rfind(":0");
            if (pos != string::npos) {
                linea.replace(pos, 2, ":1");  
            }
        }
        archivoEscritura << linea << endl;
    }

    archivoLectura2.close();
    archivoEscritura.close();

    remove("Datos Vehiculo.txt");
    rename("Temp.txt", "Datos Vehiculo.txt");

    cout << "El vehículo con placa " << placaVehiculo << " ha sido marcado como disponible y ha regresado a la base." << endl;
}

void Traslado::RevisarCola(int id){
	//mostrar todos los elementos de la cola y luego pedir si desea trasladarlos 
	int opcion;
	Cola* actual = frente[id];
	while (actual != NULL) {
		cout<<"Nombre: "<<actual->usuarios.getNombre()<< "\nCedula: "<<actual->usuarios.getCedula()<<"\nDireccion: "<<actual->usuarios.getDireccion()<<endl;
		cout<<"\nDesea todavia el servicion(1.SI/2.NO): ";
		cin>>opcion;
		
		if(opcion == 1){
			Sectores sectores;
			seleccionarVehiculo(sectores);
			Usuario usuario = colaSectores[id].usuarios;
			colaSectores[id].eliminarUsuario(frente[id],final[id],_usuario);
		}else if(opcion == 2){
			colaSectores[id].eliminarUsuario(frente[id],final[id],_usuario);
		}
		
		system("pause");
		system("cls");
		actual = actual->siguiente;
	}
	

}
void Traslado::RevisarLista(int id){
	if (lista[id].esVacia()) {  // Verifica si la lista estï¿½ vacï¿½a
        cout << "La lista en la posiciï¿½n " << id << " estï¿½ vacï¿½a." << endl;
    } else {
        cout << "La lista en la posiciï¿½n " << id << " contiene elementos." << endl;
    }
}
#endif

