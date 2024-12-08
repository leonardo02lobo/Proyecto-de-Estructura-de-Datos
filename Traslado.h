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

using namespace std;

/**
 * Clase que representa el sistema de traslado de usuarios.
 * Permite solicitar un traslado y finalizarlo, gestionando la disponibilidad de vehículos.
 */
class Traslado {
public:
	
	Traslado(Cola*& colaSectores,Cola**& frente,Cola**& final,Lista**& lista);
    /**
     * Solicita un traslado para un usuario.
     * @param sectores Referencia a la clase Sectores que contiene la información de los sectores disponibles.
     */
    void solicitar(Sectores& sectores);

    /**
     * Finaliza un traslado y actualiza la disponibilidad del vehículo.
     * @param placaVehiculo Placa del vehículo a marcar como disponible.
     */
    void finalizarTraslado(const string& placaVehiculo);
    
    void GuardarInformacionUsuarios(int cedula);
    
    void RevisarCola(int id);

private:
    Usuario _usuario;       ///< Usuario que solicita el traslado.
    Sector _sectorOrigen;   ///< Sector de origen del traslado.
    Sector _sectorDestino;  ///< Sector de destino del traslado.
    string _fecha;  	///< Fecha en la que se solicita el traslado
	Cola* colaSectores;
	Cola** frente;
	Cola** final;
	Lista** lista;
	int idOrigenSeleccionado;

    /**
     * Carga los datos del usuario a partir de su cédula.
     * @param cedula Cédula del usuario a buscar.
     * @return true si el usuario fue encontrado, false en caso contrario.
     */
    bool cargarUsuarioPorCedula(int cedula);

    /**
     * Selecciona un vehículo disponible en el sector de origen.
     * @param sectores Referencia a la clase Sectores que contiene la información de los sectores disponibles.
     */
    void seleccionarVehiculo(Sectores& sectores);
};
Traslado::Traslado(Cola*& colaSectores,Cola**& frente,Cola**& final,Lista**& lista)
	 : colaSectores(colaSectores), frente(frente), final(final),lista(lista) {
}
/**
 * Implementación del método solicitar que permite a un usuario solicitar un traslado.
 */
void Traslado::solicitar(Sectores& sectores) {
    bool band1 = false;
    bool band2 = false;
    cout << "Solicitar Traslado" << endl;

    string cedula;
    cout << "Ingrese la cédula del usuario: ";
    cin >> cedula;
    int cedulaInt = atoi(cedula.c_str());
    GuardarInformacionUsuarios(cedulaInt);

    // Solicitar los sectores de origen y destino
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

    if (!band1) {
        cout << "No se encuentra ningun vehiculo en el sector de origen. Por favor intentar mas tarde." << endl;
        return;
    } else if (!band2) {
        cout << "El ID del sector de destino no coincide con alguno dado. Por favor intentar mas tarde." << endl;
        return;
    }

    // Asignar fecha del traslado
    time_t now = time(0);
    _fecha = ctime(&now);

    // Seleccionar un vehículo disponible
    idOrigenSeleccionado = atoi(idSectorOrigen.substr(2).c_str()) - 1;
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
 * Carga los datos del usuario a partir de su cédula desde el archivo de usuarios.
 * @param cedula Cédula del usuario a buscar.
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
 * Selecciona un vehículo disponible en el sector de origen.
 * @param sectores Referencia a la clase Sectores que contiene la información de los sectores disponibles.
 */
void Traslado::seleccionarVehiculo(Sectores& sectores) {
	Lista* listaTemp = NULL;

    ifstream archivo("Datos Vehiculo.txt", ios::in);
    bool disponible = false;

    if (!archivo.is_open()) {
        cout << "Error al abrir el archivo de vehículos." << endl;
        return;
    }

    string linea;
    vector<string> placasDisponibles;

    // Buscar vehículos disponibles
    while (getline(archivo, linea)) {
        char* lineaChar = const_cast<char*>(linea.c_str());
        char* idSectorChar = strtok(lineaChar, ":");

        if (idSectorChar == _sectorOrigen.getId()) {
            char* nombreSector = strtok(NULL, ":");
            char* cedula = strtok(NULL, ":");
            char* nombreConductor = strtok(NULL, ":");
            char* placa = strtok(NULL, ":");
            char* modelo = strtok(NULL, ":");
            char* marca = strtok(NULL, ":");
            char* anio = strtok(NULL, ":");
            char* disponibilidad = strtok(NULL, ":");

            if (disponibilidad != "1") {  // Verifica que el vehículo está disponible
            Chofer chofer(nombreConductor,atoi(cedula));
            Sector sector(idSectorChar,nombreSector);
            string placaString = placa;
            string modeloString = modelo;
            string marcaString = marca;
                Vehiculo vehiculoDisponible(placaString,modeloString,marcaString,atoi(anio),chofer,sector,true);
                lista[idOrigenSeleccionado]->insertarInicio(listaTemp,vehiculoDisponible);
                placasDisponibles.push_back(placa);  // Guarda la placa para identificar el vehículo después
                disponible = true;
            }
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
    lista[idOrigenSeleccionado]->ordenarDescendente(listaTemp);
    lista[idOrigenSeleccionado]->mostrar(listaTemp);

    // Permitir al usuario seleccionar el vehículo
    int seleccion;
    cout << "Seleccione el numero del vehiculo para iniciar el traslado: ";
    cin >> seleccion;
    // Validar la selección del usuario
    if (seleccion < 1 || seleccion > placasDisponibles.size()) {
        cout << "Seleccion invalida. Intente de nuevo." << endl;
        return;
    }

    // Actualizar la disponibilidad del vehículo seleccionado
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
            // Cambia la disponibilidad a 0 en la línea seleccionada
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
    lista[idOrigenSeleccionado]->BuscarVehiculo(listaTemp,seleccion-1);
}

/**
 * Finaliza un traslado y actualiza la disponibilidad del vehículo.
 * @param placaVehiculo Placa del vehículo a marcar como disponible.
 */
void Traslado::finalizarTraslado(const string& placaVehiculo) {
    ifstream archivoLectura("Datos Vehiculo.txt");
    ofstream archivoEscritura("Temp.txt");

    if (!archivoLectura.is_open()) {
        cout << "Error al abrir el archivo de vehículos." << endl;
        return;
    }

    string linea;
    bool actualizado = false;

    while (getline(archivoLectura, linea)) {
        if (linea.find(placaVehiculo) != string::npos) {
            // Cambia la disponibilidad a 1 en la línea del vehículo correspondiente
            size_t pos = linea.rfind(":0");
            if (pos != string::npos) {
                linea.replace(pos, 2, ":1");  // Actualiza la disponibilidad a 1
                actualizado = true;
            }
        }
        archivoEscritura << linea << endl;
    }

    archivoLectura.close();
    archivoEscritura.close();

    remove("Datos Vehiculo.txt");
    rename("Temp.txt", "Datos Vehiculo.txt");

    if (actualizado) {
        cout << "El vehiculo con placa " << placaVehiculo << " ha sido marcado como disponible." << endl;
    } else {
        cout << "No se encontro el vehiculo con la placa especificada o ya estaba disponible." << endl;
    }
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

#endif

