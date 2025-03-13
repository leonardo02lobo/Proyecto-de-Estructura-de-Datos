#ifndef ESTADISTICAS_H
#define ESTADISTICAS_H

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

using namespace std;

class Estadisticas
{
private:
	int _vehiculosUsados;
	int _usuariosActivos;

public:
	Estadisticas()
	{
		_vehiculosUsados = 0;
		_usuariosActivos = 0;
	}

	Estadisticas(int vehiculosUsados, int usuariosActivos)
	{
		this->_vehiculosUsados = vehiculosUsados;
		this->_usuariosActivos = usuariosActivos;
	}

	void setVehiculosUsados(int vehiculosUsados)
	{
		this->_vehiculosUsados = vehiculosUsados;
	}

	void setUsuariosActivos(int usuariosActivos)
	{
		this->_usuariosActivos = usuariosActivos;
	}

	int getVehiculosUsados()
	{
		return this->_vehiculosUsados;
	}

	int getUsuariosActivos()
	{
		return this->_usuariosActivos;
	}

	void generarReporte()
	{

		fstream estadistica("Estadistica.txt", ios::out);
		string datosUsuarios = ReporteUsuarios();
		string datosVehiculos = ReporteVehiculos();

		estadistica << "----------------------------------------------------\n|\t\tDATOS DE LOS USUARIOS\t\t   |\n----------------------------------------------------" << endl
					<< endl;
		estadistica << datosUsuarios << endl;

		estadistica << "----------------------------------------------------\n|\t\tDATOS DE LOS VEHICULOS\t\t   |\n----------------------------------------------------" << endl
					<< endl;
		estadistica << datosVehiculos << endl;

		estadistica.close();
	}

	string ReporteUsuarios()
	{
		fstream archivoUsuario("Datos Usuarios.txt", ios::in);
		string linea, cedula, nombre, direccion, NVeces;
		int max = 0;
		string datosUsuarios;

		while (getline(archivoUsuario, linea))
		{
			stringstream ss(linea);
			getline(ss, cedula, ':');
			getline(ss, nombre, ':');
			getline(ss, direccion, ':');
			getline(ss, NVeces, ':');

			stringstream ss2(NVeces);
			string token;
			getline(ss2, token, '_');
			string numero;
			getline(ss2, numero, '_');
			int numeroVeces = atoi(numero.c_str());

			if (numeroVeces > max)
			{
				datosUsuarios =
					"Cedula: " + cedula + "\n" +
					"Nombre: " + nombre + "\n" +
					"Direccion: " + direccion + "\n" +
					"N veces que uso la aplicacion: " + numero + "\n";
				max = numeroVeces;
			}
		}
		archivoUsuario.close();

		return datosUsuarios;
	}

	string ReporteVehiculos()
	{
		fstream archivo("Datos Vehiculo.txt", ios::in);
		string idSector, nombreSector, cedulaChofer, NombreChofer, placa, modelo, marca, anio, disponibilidad, nVecesUsado;
		string datosVehiculos;
		int max = 0;
		string linea = "";

		while (getline(archivo, linea))
		{
			stringstream ss(linea);
			getline(ss, idSector, ':');
			getline(ss, nombreSector, ':');
			getline(ss, cedulaChofer, ':');
			getline(ss, NombreChofer, ':');
			getline(ss, placa, ':');
			getline(ss, modelo, ':');
			getline(ss, marca, ':');
			getline(ss, anio, ':');
			getline(ss, disponibilidad, ':');
			getline(ss, nVecesUsado, ':');

			stringstream ss2(nVecesUsado);
			string token;
			getline(ss2, token, '_');
			string numero;
			getline(ss2, numero, '_');
			int numeroVeces = atoi(numero.c_str());

			if (numeroVeces > max)
			{
				datosVehiculos =
					"ID del sector: " + idSector + "\n" +
					"Nombre del Sector: " + nombreSector + "\n" +
					"Cedula del Chofer: " + cedulaChofer + "\n" +
					"Placa del Vehiculo: " + placa + "\n" +
					"Modelo del Vehiculo: " + modelo + "\n" +
					"Marca del Vehiculo: " + marca + "\n" +
					"Anio del Vehiculo: " + anio + "\n" +
					"Disponibilidad del Vehiculo: " + (disponibilidad == "1" ? "Disponible " : "No disponible") + "\n" +
					"N veces que uso la aplicacion: " + numero + "\n";
				max = numeroVeces;
			}
		}

		archivo.close();

		return datosVehiculos;
	}
};
#endif