#ifndef ESTADISTICAS_H
#define ESTADISTICAS_H

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

using namespace std;

// Esta clase contiene los datos de los veh�culos usados y de los usuarios activos.
// Este m�todo generar� las estad�sticas al final del programa.
class Estadisticas {
	private:
	    int _vehiculosUsados;  // Almacena el n�mero de veh�culos usados
	    int _usuariosActivos;  // Almacena el n�mero de usuarios activos

	public:
		// Constructor sin par�metros
	    Estadisticas() {
	    	_vehiculosUsados = 0;
	    	_usuariosActivos = 0;
		}
		
		// Constructor con par�metros
		Estadisticas(int vehiculosUsados, int usuariosActivos) {
	    	this->_vehiculosUsados = vehiculosUsados;
	    	this->_usuariosActivos = usuariosActivos;
		}
		
		// ---------------------- M�TODOS SETTERS ----------------------
	    void setVehiculosUsados(int vehiculosUsados){
	    	this->_vehiculosUsados = vehiculosUsados;
		}
		
		void setUsuariosActivos(int usuariosActivos){
	    	this->_usuariosActivos = usuariosActivos;
		}
		
		// --------------------- M�TODOS GETTERS ----------------------
	    int getVehiculosUsados() { 
			return this->_vehiculosUsados; 
		}
		
	    int getUsuariosActivos() {
	    	return this->_usuariosActivos;
		}
		
		// Este m�todo generar� el reporte cuando se termine el programa
	    void generarReporte() {
	    	// Abre el archivo de estad�sticas en modo de escritura
	    	fstream estadistica("Estadistica.txt", ios::out);
		    string datosUsuarios = ReporteUsuarios();   // Genera el reporte de usuarios
		    string datosVehiculos = ReporteVehiculos(); // Genera el reporte de veh�culos
		    
		    // Escribe el encabezado y los datos de usuarios en el archivo
		    estadistica << "----------------------------------------------------\n|\t\tDATOS DE LOS USUARIOS\t\t   |\n----------------------------------------------------" << endl << endl;
		    estadistica << datosUsuarios << endl;
		    
		    // Escribe el encabezado y los datos de veh�culos en el archivo
		    estadistica << "----------------------------------------------------\n|\t\tDATOS DE LOS VEHICULOS\t\t   |\n----------------------------------------------------" << endl << endl;
		    estadistica << datosVehiculos << endl;
		    
		    estadistica.close();  // Cierra el archivo
		}
		
		// Genera un reporte de los usuarios y devuelve una cadena con los datos
		string ReporteUsuarios(){
			fstream archivoUsuario("Datos Usuarios.txt", ios::in); // Abre el archivo de usuarios en modo lectura
		    string linea, cedula, nombre, direccion, NVeces;
		    int max = 0; // Variable para almacenar el m�ximo de veces que un usuario ha usado la aplicaci�n
		    string datosUsuarios;
		    
		    // Lee el archivo l�nea por l�nea
		    while (getline(archivoUsuario, linea)) {
		        stringstream ss(linea);
		        getline(ss, cedula, ':');     // Obtiene la c�dula del usuario
		        getline(ss, nombre, ':');     // Obtiene el nombre del usuario
		        getline(ss, direccion, ':');  // Obtiene la direcci�n del usuario
		        getline(ss, NVeces, ':');     // Obtiene la cantidad de veces que el usuario ha usado la app
		        
		        // Separa la informaci�n de uso de la aplicaci�n
		        stringstream ss2(NVeces);
		        string token;
		        getline(ss2, token, '_');
		        string numero;
		        getline(ss2, numero, '_');
		        int numeroVeces = atoi(numero.c_str()); // Convierte el n�mero de veces a entero
		        
		        // Si el n�mero de veces es el m�ximo, guarda los datos del usuario
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
		    
		    return datosUsuarios;  // Devuelve los datos del usuario con m�s usos
		}
		
		// Genera un reporte de los veh�culos y devuelve una cadena con los datos
		string ReporteVehiculos(){
			fstream archivo("Datos Vehiculo.txt", ios::in);  // Abre el archivo de veh�culos en modo lectura
			string idSector, nombreSector, cedulaChofer, NombreChofer, placa, modelo, marca, anio, disponibilidad, nVecesUsado;
			string datosVehiculos;
		    int max = 0; // Variable para almacenar el m�ximo de veces que un veh�culo ha sido usado
			string linea = "";

			// Lee el archivo l�nea por l�nea
			while(getline(archivo,linea)){
			    stringstream ss(linea);
			    getline(ss, idSector, ':');           // Obtiene el ID del sector
			    getline(ss, nombreSector, ':');       // Obtiene el nombre del sector
			    getline(ss, cedulaChofer, ':');       // Obtiene la c�dula del chofer
			    getline(ss, NombreChofer, ':');       // Obtiene el nombre del chofer
			    getline(ss, placa, ':');              // Obtiene la placa del veh�culo
			    getline(ss, modelo, ':');             // Obtiene el modelo del veh�culo
			    getline(ss, marca, ':');              // Obtiene la marca del veh�culo
			    getline(ss, anio, ':');               // Obtiene el a�o del veh�culo
			    getline(ss, disponibilidad, ':');     // Obtiene la disponibilidad del veh�culo
			    getline(ss, nVecesUsado, ':');        // Obtiene la cantidad de veces que se ha usado el veh�culo

			    // Separa la informaci�n de uso de la aplicaci�n
			    stringstream ss2(nVecesUsado);
			    string token;
			    getline(ss2, token, '_');
			    string numero;
			    getline(ss2, numero, '_');
			    int numeroVeces = atoi(numero.c_str()); // Convierte el n�mero de veces a entero

			    // Si el n�mero de veces es el m�ximo, guarda los datos del veh�culo
			    if(numeroVeces > max){
			        datosVehiculos = 
			            "ID del sector: " + idSector + "\n" +
			            "Nombre del Sector: " + nombreSector + "\n" +
			            "Cedula del Chofer: " + cedulaChofer + "\n" +
			            "Placa del Vehiculo: " + placa + "\n" +
			            "Modelo del Vehiculo: " + modelo + "\n" +
			            "Marca del Vehiculo: " + marca + "\n" +
			            "A�o del Vehiculo: " + anio + "\n" +
			            "Disponibilidad del Vehiculo: " + (disponibilidad == "1" ? "Disponible ": "No disponible") + "\n" +
			            "N veces que uso la aplicacion: "+ numero + "\n";
			        max = numeroVeces;
			    }
			}

		    archivo.close(); // Cierra el archivo de veh�culos
		    
		    return datosVehiculos; // Devuelve los datos del veh�culo con m�s usos
		}

};

#endif

