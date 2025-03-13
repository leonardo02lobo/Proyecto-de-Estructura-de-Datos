#ifndef VEHICULO_H
#define VEHICULO_H
#include "Chofer.h"
#include "Sector.h"
#include "Sectores.h"
#include <cstring>

using namespace std;

class Vehiculo
{
private:
	int Id;
	string _placa;
	string _modelo;
	string _marca;
	int _anio;
	Chofer _chofer;
	Sector _sectorActual;
	bool _disponible;
	int N_vecesUsado;

public:
	bool operator==(const Vehiculo &otro) const
	{
		return _placa == otro._placa;
	}

	bool operator!=(const Vehiculo &otro) const
	{
		return !(*this == otro);
	}

	Vehiculo()
	{
		_placa = "";
		_modelo = "";
		_marca = "";
		_anio = 0;
		_disponible = true;
	}

	Vehiculo(string placa, string modelo, string marca, int anio, Chofer chofer, Sector sectorActual, bool disponible)
	{
		_placa = placa;
		_modelo = modelo;
		_marca = marca;
		_anio = anio;
		_chofer = chofer;
		_sectorActual = sectorActual;
		_disponible = disponible;
	}

	void setPlaca(string placa)
	{
		_placa = placa;
	}

	void setModelo(string modelo)
	{
		_modelo = modelo;
	}

	void setId(int Id)
	{
		this->Id = Id;
	}
	void setMarca(string marca)
	{
		_marca = marca;
	}

	void setAnio(int anio)
	{
		_anio = anio;
	}

	void setChofer(Chofer chofer)
	{
		_chofer = chofer;
	}

	void setSectorActual(Sector sectorActual)
	{
		_sectorActual = sectorActual;
	}

	void setDisponible(bool disponible)
	{
		_disponible = disponible;
	}

	void setN_vecesUsado(int nVecesUsado)
	{
		N_vecesUsado = nVecesUsado;
	}
	string getPlaca()
	{
		return this->_placa;
	}
	string getModelo()
	{
		return this->_modelo;
	}
	string getMarca()
	{
		return this->_marca;
	}
	int getAnio()
	{
		return this->_anio;
	}
	Chofer getChofer()
	{
		return this->_chofer;
	}
	Sector getSectorActual()
	{
		return this->_sectorActual;
	}
	bool getDisponible()
	{
		return this->_disponible;
	}
	int getId()
	{
		return this->Id;
	}
	int getN_vecesUsado()
	{
		return N_vecesUsado;
	}

	void AsignarSectorAleatorio(Sectores &sectores)
	{
		Sector sector;
		sectores.DistribuirSectores(&sector);
		_sectorActual = sector;
	}

	void AgregarVehiculo(Sectores &sectores)
	{
		ofstream archivo("Datos Vehiculo.txt", ios::app);

		cout << "Agregar Vehiculo" << endl
			 << endl;
		fflush(stdin);
		cout << "Digite la placa: ";
		cin >> _placa;

		fflush(stdin);
		cout << "Digite el modelo: ";
		cin >> _modelo;

		fflush(stdin);
		cout << "Digite la marca: ";
		cin >> _marca;

		fflush(stdin);
		cout << "Digite el anio del carro: ";
		cin >> _anio;

		fflush(stdin);
		cout << "Digite la Cedula del chofer: ";
		int cedula;
		cin >> cedula;
		_chofer.setCedula(cedula);

		fflush(stdin);
		cout << "Digite el Nombre del chofer: ";
		string nombre;
		getline(cin, nombre);
		_chofer.setNombreConductor(nombre);

		AsignarSectorAleatorio(sectores);
		archivo << _sectorActual.getId() << ":" << _sectorActual.getNombreSector() << ":" << _chofer.getCedula() << ":" << _chofer.getNombreConductor() << ":" << _placa << ":" << _modelo << ":" << _marca << ":" << _anio << ":" << _disponible << ":N_0" << "\n";
		archivo.close();
		cout << "Vehiculo con su respectivo chofer Agregado con exito" << endl;
	}

	void ModificarVehiculo()
	{
		ifstream archivo("Datos Vehiculo.txt", ios::in);
		ofstream temp("temp.txt", ios::out);
		string linea, DatoViejo;
		string cedulaBuscar;
		bool encontrado = false;

		cout << "Ingrese la cedula para modificar los datos: ";
		cin >> cedulaBuscar;
		cin.ignore();

		Vehiculo vehiculo = separarDatos(archivo, cedulaBuscar, encontrado);

		if (atoi(cedulaBuscar.c_str()) == vehiculo.getChofer().getCedula() && !encontrado)
		{
			cout << "Cedula del Conductor: " << vehiculo.getChofer().getCedula() << endl;
			cout << "Nombre del Conductor: " << vehiculo.getChofer().getNombreConductor() << endl;
			cout << "Placa: " << vehiculo.getPlaca() << endl;
			cout << "Modelo: " << vehiculo.getModelo() << endl;
			cout << "Marca: " << vehiculo.getMarca() << endl;
			cout << "Anio: " << vehiculo.getAnio() << endl;

			int opcion;
			cout << "\nQue dato desea modificar\n1. Cedula Del Conductor\n2. Nombre del Conductor\n3. Placa\n4. Modelo\n5. Marca\n6. Anio\nOpcion: ";
			cin >> opcion;

			cin.ignore();
			cout << "Ingrese el nuevo valor: ";
			string nuevo;
			getline(cin, nuevo);

			if (opcion == 1)
			{
				vehiculo.getChofer().setCedula(atoi(nuevo.c_str()));
			}
			else if (opcion == 2)
			{
				vehiculo.getChofer().setNombreConductor(nuevo);
			}
			else if (opcion == 3)
			{
				vehiculo.setPlaca(nuevo);
			}
			else if (opcion == 4)
			{
				vehiculo.setModelo(nuevo);
			}
			else if (opcion == 5)
			{
				vehiculo.setMarca(nuevo);
			}
			else if (opcion == 6)
			{
				vehiculo.setAnio(atoi(nuevo.c_str()));
			}
			encontrado = true;
		}

		temp << vehiculo.getId() << ":" << vehiculo.getSectorActual().getNombreSector() << ":" << vehiculo.getChofer().getCedula() << ":" << vehiculo.getChofer().getNombreConductor() << ":"
			 << vehiculo.getPlaca() << ":" << vehiculo.getModelo() << ":" << vehiculo.getMarca() << ":" << vehiculo.getAnio() << ":" << vehiculo.getDisponible() << ":"
			 << vehiculo.getN_vecesUsado() << "\n";

		if (!encontrado)
		{
			cout << "Registro no encontrado." << endl;
			archivo.close();
			temp.close();
			return;
		}

		archivo.close();
		temp.close();
		remove("Datos Vehiculo.txt");
		rename("temp.txt", "Datos Vehiculo.txt");

		cout << "Registro Modificado." << endl;
	}

	void ConsultarVehiculo()
	{
		string cedulaBuscada;
		ifstream archivo("Datos Vehiculo.txt", ios::in);
		bool band = false;
		fflush(stdin);
		cout << "Digite la Cedula a Buscar: ";
		getline(cin, cedulaBuscada);

		Vehiculo vehiculo = separarDatos(archivo, cedulaBuscada, band);

		if (atoi(cedulaBuscada.c_str()) == vehiculo.getChofer().getCedula())
		{
			cout << "Datos Vehiculo" << endl;
			cout << "ID: " << vehiculo.getId() << endl;
			cout << "Sector: " << vehiculo.getSectorActual().getNombreSector() << endl;
			cout << "Cedula del Conductor: " << vehiculo.getChofer().getCedula() << endl;
			cout << "Nombre del Conductor: " << vehiculo.getChofer().getNombreConductor() << endl;
			cout << "Placa: " << vehiculo.getPlaca() << endl;
			cout << "Modelo: " << vehiculo.getModelo() << endl;
			cout << "Marca: " << vehiculo.getMarca() << endl;
			cout << "Anio: " << vehiculo.getAnio() << endl;
			cout << "Disponible: " << (vehiculo.getDisponible() == 1 ? "Esta Disponible" : "No esta Disponible") << endl;
		}

		if (!band)
		{
			cout << "No se ha encontrado ningun usuario con esa cedula. Por favor intente mas tarde" << endl;
		}
		archivo.close();
	}

	int ActualizarUbicacionVehiculo()
	{
		fstream archivo("Datos Vehiculo.txt", ios::in | ios::out);
		fstream temp("temp.txt", ios::out);
		string Nplaca, IDSector, linea, lineaCambio;
		bool encontrado = false;
		string sector, id, cedulaConductor, nombreConductor, placa, modelo, marca, anio, disponibilidad, nVecesUsado;
		string nuevoId, nuevoSector;

		if (!archivo.is_open())
		{
			cout << "Error al momento de leer el archivo" << endl;
			return 0;
		}

		fflush(stdin);
		cout << "Ingrese el Numero de placa: ";
		getline(cin, Nplaca);
		fflush(stdin);
		cout << "Ingrese el ID del sector Actual. Ejemplo: ID# : ";
		getline(cin, IDSector);

		while (getline(archivo, linea))
		{
			char *lineaChar = const_cast<char *>(linea.c_str());
			id = strtok(lineaChar, ":");
			sector = strtok(NULL, ":");
			cedulaConductor = strtok(NULL, ":");
			nombreConductor = strtok(NULL, ":");
			placa = strtok(NULL, ":");
			modelo = strtok(NULL, ":");
			marca = strtok(NULL, ":");
			anio = strtok(NULL, ":");
			disponibilidad = strtok(NULL, ":");
			nVecesUsado = strtok(NULL, ":");

			if ((id == IDSector) && (placa == Nplaca))
			{
				cout << "Vehiculo Encontrado. Sector: " << sector << endl;
				encontrado = true;

				cout << "Digite el ID de nuevo Sector(del 1 al 14). Ejemplo: ID#: ";
				getline(cin, nuevoId);

				Sectores s;
				nuevoSector = s.DevolverSector(nuevoId);

				id = nuevoId;
				sector = nuevoSector;
			}
			temp << id << ":" << sector << ":" << cedulaConductor << ":" << nombreConductor << ":" << placa << ":" << modelo << ":" << marca << ":" << anio << ":" << disponibilidad << ":" << nVecesUsado << endl;
		}

		if (!encontrado)
		{
			cout << "La placa o el ID del sector fueron escritos de forma incorrecta. Por favor intentar mas tarde." << endl;
		}

		archivo.close();
		temp.close();

		remove("Datos Vehiculo.txt");
		rename("temp.txt", "Datos Vehiculo.txt");
		return atoi(nuevoId.substr(2).c_str());
	}

	void EliminarVehiculo()
	{
		string cedulaBuscada;
		string linea;
		fstream archivo("Datos Vehiculo.txt", ios::in);
		ofstream temp("temp.txt", ios::out);
		bool encontrado = false;

		fflush(stdin);
		cout << "Digite la Cedula a Buscar: ";
		getline(cin, cedulaBuscada);

		while (getline(archivo, linea))
		{
			stringstream ss(linea);
			string cedula;
			getline(ss, cedula, ':');
			getline(ss, cedula, ':');
			getline(ss, cedula, ':');

			if (cedulaBuscada != cedula)
			{
				temp << linea << "\n";
			}
			else
			{
				encontrado = true;
			}
		}

		archivo.close();
		temp.close();

		remove("Datos Vehiculo.txt");
		rename("temp.txt", "Datos Vehiculo.txt");

		if (!encontrado)
		{
			cout << "Registro no encontrado." << endl;
		}
		else
		{
			cout << "Registro eliminado." << endl;
		}
	}

private:
	Vehiculo separarDatos(ifstream &archivo, string cedulaBuscar, bool &encontrado)
	{
		string idSector, nombreSector, cedulaChofer, NombreChofer, placa, modelo, marca, anio, disponibilidad, nVecesUsado, linea;
		Vehiculo vehiculo;

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

			vehiculo.setId(atoi(idSector.c_str()));
			vehiculo.setAnio(atoi(anio.c_str()));
			vehiculo.setDisponible(disponibilidad == "1" ? true : false);
			vehiculo.setMarca(marca);
			vehiculo.setModelo(modelo);
			vehiculo.setPlaca(placa);
			Chofer chofer(NombreChofer, atoi(cedulaChofer.c_str()));
			vehiculo.setChofer(chofer);
			vehiculo.setSectorActual(Sector(idSector, nombreSector));
			encontrado = true;
			return vehiculo;
		}
		return vehiculo;
	}
};
#endif