#ifndef ESTADISTICAS_H
#define ESTADISTICAS_H

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

using namespace std;

// Esta clase contiene los datos de los vehículos usados y de los usuarios activos.
// Este método generará las estadísticas al final del programa.
class Estadisticas {
	private:
	    int _vehiculosUsados;  // Almacena el número de vehículos usados
	    int _usuariosActivos;  // Almacena el número de usuarios activos

	public:
		// Constructor sin parámetros
	    Estadisticas() {
	    	_vehiculosUsados = 0;
	    	_usuariosActivos = 0;
		}
		
		// Constructor con parámetros
		Estadisticas(int vehiculosUsados, int usuariosActivos) {
	    	this->_vehiculosUsados = vehiculosUsados;
	    	this->_usuariosActivos = usuariosActivos;
		}
		
		// ---------------------- MÉTODOS SETTERS ----------------------
	    void setVehiculosUsados(int vehiculosUsados){
	    	this->_vehiculosUsados = vehiculosUsados;
		}
		
		void setUsuariosActivos(int usuariosActivos){
	    	this->_usuariosActivos = usuariosActivos;
		}
		
		// --------------------- MÉTODOS GETTERS ----------------------
	    int getVehiculosUsados() { 
			return this->_vehiculosUsados; 
		}
		
	    int getUsuariosActivos() {
	    	return this->_usuariosActivos;
		}
		
		// Este método generará el reporte cuando se termine el programa
	    void generarReporte() {
	    	// Abre el archivo de estadísticas en modo de escritura
	    	fstream estadistica("Estadistica.txt", ios::out);
		    string datosUsuarios = ReporteUsuarios();   // Genera el reporte de usuarios
		    string datosVehiculos = ReporteVehiculos(); // Genera el reporte de vehículos
		    
		    // Escribe el encabezado y los datos de usuarios en el archivo
		    estadistica << "----------------------------------------------------\n|\t\tDATOS DE LOS USUARIOS\t\t   |\n----------------------------------------------------" << endl << endl;
		    estadistica << datosUsuarios << endl;
		    
		    // Escribe el encabezado y los datos de vehículos en el archivo
		    estadistica << "----------------------------------------------------\n|\t\tDATOS DE LOS VEHICULOS\t\t   |\n----------------------------------------------------" << endl << endl;
		    estadistica << datosVehiculos << endl;
		    
		    estadistica.close();  // Cierra el archivo
		}
		
		// Genera un reporte de los usuarios y devuelve una cadena con los datos
		string ReporteUsuarios(){
			fstream archivoUsuario("Datos Usuarios.txt", ios::in); // Abre el archivo de usuarios en modo lectura
		    string linea, cedula, nombre, direccion, NVeces;
		    int max = 0; // Variable para almacenar el máximo de veces que un usuario ha usado la aplicación
		    string datosUsuarios;
		    
		    // Lee el archivo línea por línea
		    while (getline(archivoUsuario, linea)) {
		        stringstream ss(linea);
		        getline(ss, cedula, ':');     // Obtiene la cédula del usuario
		        getline(ss, nombre, ':');     // Obtiene el nombre del usuario
		        getline(ss, direccion, ':');  // Obtiene la dirección del usuario
		        getline(ss, NVeces, ':');     // Obtiene la cantidad de veces que el usuario ha usado la app
		        
		        // Separa la información de uso de la aplicación
		        stringstream ss2(NVeces);
		        string token;
		        getline(ss2, token, '_');
		        string numero;
		        getline(ss2, numero, '_');
		        int numeroVeces = atoi(numero.c_str()); // Convierte el número de veces a entero
		        
		        // Si el número de veces es el máximo, guarda los datos del usuario
		        if (numeroVeces > max) {
		            datosUsuarios = 
		                "Cedula: " + cedula + "\n" +
		                "Nombre: " + nombre + "\n" +
		                "Direccion: " + direccion + "\n" +
		                "N veces que uso la aplicacion: " + numero + "\n";
		            max = numeroVeces;
		        }
		    }
		    archivoUsuario.close();  // Cierra el archivo de usuarios
		    
		    return datosUsuarios;  // Devuelve los datos del usuario con más usos
		}
		
		// Genera un reporte de los vehículos y devuelve una cadena con los datos
		string ReporteVehiculos(){
			fstream archivo("Datos Vehiculo.txt", ios::in);  // Abre el archivo de vehículos en modo lectura
			string idSector, nombreSector, cedulaChofer, NombreChofer, placa, modelo, marca, anio, disponibilidad, nVecesUsado;
			string datosVehiculos;
		    int max = 0; // Variable para almacenar el máximo de veces que un vehículo ha sido usado
			string linea = "";

			// Lee el archivo línea por línea
			while(getline(archivo,linea)){
			    stringstream ss(linea);
			    getline(ss, idSector, ':');           // Obtiene el ID del sector
			    getline(ss, nombreSector, ':');       // Obtiene el nombre del sector
			    getline(ss, cedulaChofer, ':');       // Obtiene la cédula del chofer
			    getline(ss, NombreChofer, ':');       // Obtiene el nombre del chofer
			    getline(ss, placa, ':');              // Obtiene la placa del vehículo
			    getline(ss, modelo, ':');             // Obtiene el modelo del vehículo
			    getline(ss, marca, ':');              // Obtiene la marca del vehículo
			    getline(ss, anio, ':');               // Obtiene el año del vehículo
			    getline(ss, disponibilidad, ':');     // Obtiene la disponibilidad del vehículo
			    getline(ss, nVecesUsado, ':');        // Obtiene la cantidad de veces que se ha usado el vehículo

			    // Separa la información de uso de la aplicación
			    stringstream ss2(nVecesUsado);
			    string token;
			    getline(ss2, token, '_');
			    string numero;
			    getline(ss2, numero, '_');
			    int numeroVeces = atoi(numero.c_str()); // Convierte el número de veces a entero

			    // Si el número de veces es el máximo, guarda los datos del vehículo
			    if(numeroVeces > max){
			        datosVehiculos = 
			            "ID del sector: " + idSector + "\n" +
			            "Nombre del Sector: " + nombreSector + "\n" +
			            "Cedula del Chofer: " + cedulaChofer + "\n" +
			            "Placa del Vehiculo: " + placa + "\n" +
			            "Modelo del Vehiculo: " + modelo + "\n" +
			            "Marca del Vehiculo: " + marca + "\n" +
			            "Año del Vehiculo: " + anio + "\n" +
			            "Disponibilidad del Vehiculo: " + (disponibilidad == "1" ? "Disponible ": "No disponible") + "\n" +
			            "N veces que uso la aplicacion: "+ numero + "\n";
			        max = numeroVeces;
			    }
			}

		    archivo.close(); // Cierra el archivo de vehículos
		    
		    return datosVehiculos; // Devuelve los datos del vehículo con más usos
		}

};

#endif

