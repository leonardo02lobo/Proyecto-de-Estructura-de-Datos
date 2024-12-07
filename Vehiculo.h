#ifndef VEHICULO_H
#define VEHICULO_H
#include "Chofer.h"
#include "Sector.h"
#include "Sectores.h"
#include<cstring>

using namespace std;

/**
 * Clase Vehiculo
 * 
 * Representa un veh�culo asociado a un chofer y sector, e incluye m�todos para gestionar los datos del veh�culo.
 * La clase permite agregar, modificar, consultar y actualizar la ubicaci�n de un veh�culo.
 */
class Vehiculo{
	private:
		string _placa;           ///< Placa del veh�culo
        string _modelo;          ///< Modelo del veh�culo
        string _marca;           ///< Marca del veh�culo
        int _anio;               ///< A�o de fabricaci�n del veh�culo
        Chofer _chofer;          ///< Chofer asignado al veh�culo
        Sector _sectorActual;    ///< Sector donde se encuentra actualmente el veh�culo
        bool _disponible;        ///< Estado de disponibilidad del veh�culo
	public:
		/**
         * Constructor sin par�metros.
         * Inicializa los atributos a valores por defecto.
         */
		Vehiculo(){
			_placa = "";
			_modelo = "";
			_marca = "";
			_anio = 0;
			_disponible = true;
		}
		/**
         * Constructor con par�metros.
         * @param placa Placa del veh�culo
         * @param modelo Modelo del veh�culo
         * @param marca Marca del veh�culo
         * @param anio A�o de fabricaci�n del veh�culo
         * @param chofer Chofer asignado al veh�culo
         * @param sectorActual Sector donde se encuentra el veh�culo
         * @param disponible Estado de disponibilidad del veh�culo
         */
		Vehiculo(string placa,string modelo,string marca,int anio,Chofer chofer,Sector sectorActual,bool disponible){
			_placa = placa;
			_modelo = modelo;
			_marca = marca;
			_anio = anio;
			_chofer = chofer;
			_sectorActual = sectorActual;
			_disponible = disponible;
		}
		/**
         * Asigna la placa del veh�culo.
         * @param placa Placa del veh�culo
         */
        void setPlaca(string placa) { _placa = placa; }

        /**
         * Asigna el modelo del veh�culo.
         * @param modelo Modelo del veh�culo
         */
        void setModelo(string modelo) { _modelo = modelo; }

        /**
         * Asigna la marca del veh�culo.
         * @param marca Marca del veh�culo
         */
        void setMarca(string marca) { _marca = marca; }

        /**
         * Asigna el a�o de fabricaci�n del veh�culo.
         * @param anio A�o del veh�culo
         */
        void setAnio(int anio) { _anio = anio; }

        /**
         * Asigna el chofer del veh�culo.
         * @param chofer Chofer del veh�culo
         */
        void setChofer(Chofer chofer) { _chofer = chofer; }

        /**
         * Asigna el sector actual del veh�culo.
         * @param sectorActual Sector donde se encuentra el veh�culo
         */
        void setSectorActual(Sector sectorActual) { _sectorActual = sectorActual; }

        /**
         * Asigna el estado de disponibilidad del veh�culo.
         * @param disponible Estado de disponibilidad
         */
        void setDisponible(bool disponible) { _disponible = disponible; }

        //----------------- M�TODOS GETTERS -------------------------------
        string getPlaca() { return this->_placa; }
        string getModelo() { return this->_modelo; }
        string getMarca() { return this->_marca; }
        int getAnio() { return this->_anio; }
        Chofer getChofer() { return this->_chofer; }
        Sector getSectorActual() { return this->_sectorActual; }
        bool getDisponible() { return this->_disponible; }
        
		
		/**
         * Asigna un sector aleatorio al veh�culo usando un objeto de la clase Sectores.
         * @param sectores Referencia al objeto Sectores para seleccionar un sector aleatorio.
         */
   		void AsignarSectorAleatorio(Sectores& sectores) {
	        // Crea un objeto Sector
	        Sector sector;
	        // Llama a DistribuirSectores para asignar un sector aleatorio
	        sectores.DistribuirSectores(&sector);
	        // Asigna el sector al veh?culo
	        _sectorActual = sector;
   		 }
		
		/**
         * Permite al usuario ingresar los datos de un nuevo veh�culo, que luego se almacenan en un archivo.
         * Tambi�n asigna un sector aleatorio al veh�culo.
         * @param sectores Referencia al objeto Sectores para asignar un sector aleatorio.
         */
		void AgregarVehiculo(Sectores& sectores) {
	        ofstream archivo("Datos Vehiculo.txt", ios::app);
	
	        cout << "Agregar Vehiculo" << endl << endl;
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

        	// Asigna un sector aleatorio al veh?culo
        	AsignarSectorAleatorio(sectores);
			archivo<<_sectorActual.getId()<<":"<<_sectorActual.getNombreSector()<<":"<<_chofer.getCedula()<<":"<<_chofer.getNombreConductor()<<":"<<_placa<<":"<<_modelo<<":"<<_marca<<":"<<_anio<<":"<<_disponible<<":N_0"<<"\n";
			archivo.close();
			cout<<"Vehiculo con su respectivo chofer Agregado con exito"<<endl;
		}
		
		/**
         * Modifica los datos de un veh�culo bas�ndose en la c�dula del chofer. 
         * Permite al usuario elegir el dato espec�fico a modificar.
         */
		void ModificarVehiculo() {
		    ifstream archivo("Datos Vehiculo.txt", ios::in);
		    ofstream temp("temp.txt", ios::out);
		    string linea, DatoViejo;
		    string cedulaBuscar;
		    bool encontrado = false;
		
		    // Variables para almacenar los datos del veh�culo
		    string idSector, nombreSector, cedulaChofer, NombreChofer, placa, modelo, marca, anio, disponibilidad, nVecesUsado;
		
		    cout << "Ingrese la cedula para modificar los datos: ";
		    cin >> cedulaBuscar;
		
		    // Limpiar el buffer de entrada para evitar problemas al usar getline despu�s de cin
		    cin.ignore();
		
		    // Leer el archivo y buscar la c�dula
		    while (getline(archivo, linea)) {
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
		
		        if (cedulaBuscar == cedulaChofer && !encontrado) {
		            cout << "Cedula del Conductor: " << cedulaChofer << endl;
		            cout << "Nombre del Conductor: " << NombreChofer << endl;
		            cout << "Placa: " << placa << endl;
		            cout << "Modelo: " << modelo << endl;
		            cout << "Marca: " << marca << endl;
		            cout << "Anio: " << anio << endl;

		            int opcion;
		            cout << "\nQue dato desea modificar\n1. Cedula Del Conductor\n2. Nombre del Conductor\n3. Placa\n4. Modelo\n5. Marca\n6. Anio\nOpcion: ";
		            cin >> opcion;
		
		            // Limpiar el buffer de entrada para evitar problemas al usar getline despu�s de cin
		            cin.ignore();
		            cout << "Ingrese el nuevo valor: ";
		            string nuevo;
		            getline(cin, nuevo);
		
		            // Determinar que dato se va a modificar
		            if (opcion == 1) {
		                cedulaChofer = nuevo;
		            } else if (opcion == 2) {
		                NombreChofer = nuevo;
		            } else if (opcion == 3) {
		                placa = nuevo;
		            } else if (opcion == 4) {
		                modelo = nuevo;
		            } else if (opcion == 5) {
		                marca = nuevo;
		            } else if (opcion == 6) {
		                anio = nuevo;
		            }
		            encontrado = true;
		        }
		        // Escribir el registro en el archivo temporal
		        temp << idSector << ":" << nombreSector << ":" << cedulaChofer << ":" << NombreChofer << ":" 
		             << placa << ":" << modelo << ":" << marca << ":" << anio << ":" << disponibilidad << ":" 
		             << nVecesUsado << "\n";
		    }
		
		    if (!encontrado) {
		        cout << "Registro no encontrado." << endl;
		        archivo.close();
		        temp.close();
		        return;
		    }
		
		    archivo.close();
		    temp.close();
		
		    // Reemplazar el archivo original con el archivo temporal
		    remove("Datos Vehiculo.txt");
		    rename("temp.txt", "Datos Vehiculo.txt");
		
		    cout << "Registro Modificado." << endl;
		}
		
		
		/**
         * Consulta los datos de un veh�culo basado en la c�dula del chofer.
         * Muestra los detalles del veh�culo si se encuentra el registro correspondiente.
         */
		void ConsultarVehiculo() {
		    string cedulaBuscada;
		    string linea;
		    fstream archivo("Datos Vehiculo.txt", ios::in);
		    bool band = false;
		    fflush(stdin);
		    cout << "Digite la Cedula a Buscar: ";
		    getline(cin, cedulaBuscada);
		
		    while (getline(archivo, linea)) {
		        stringstream ss(linea);
		        string id, sector, cedula, nombre, placa, modelo, marca, anio, disponible;
		
		        getline(ss, id, ':');
		        getline(ss, sector, ':');
		        getline(ss, cedula, ':');
		        getline(ss, nombre, ':');
		        getline(ss, placa, ':');
		        getline(ss, modelo, ':');
		        getline(ss, marca, ':');
		        getline(ss, anio, ':');
		        getline(ss, disponible, ':');
		
		        if (cedulaBuscada == cedula) {
		            cout << "Datos Vehiculo" << endl;
		            cout << "ID: " << id << endl;
		            cout << "Sector: " << sector << endl;
		            cout << "Cedula del Conductor: " << cedula << endl;
		            cout << "Nombre del Conductor: " << nombre << endl;
		            cout << "Placa: " << placa << endl;
		            cout << "Modelo: " << modelo << endl;
		            cout << "Marca: " << marca << endl;
		            cout << "A?o: " << anio << endl;
		            cout << "Disponible: " << (disponible == "1" ? "Esta Disponible" : "No esta Disponible") << endl;
		            band = true;
		            break;
		        }
		    }
		
		    if (!band) {
		        cout << "No se ha encontrado ningun usuario con esa cedula. Por favor intente mas tarde" << endl;
		    }
		    archivo.close();
		}
		
		/**
         * Actualiza la ubicaci�n del veh�culo seg�n la placa proporcionada.
         */
		int ActualizarUbicacionVehiculo() {
		    fstream archivo("Datos Vehiculo.txt", ios::in | ios::out);
		    fstream temp("temp.txt", ios::out);
		    string Nplaca, IDSector, linea, lineaCambio;
		    bool encontrado = false;
		    string sector, id,cedulaConductor,nombreConductor,placa,modelo,marca,anio,disponibilidad,nVecesUsado;
		    string nuevoId, nuevoSector;
		
		    if (!archivo.is_open()) {
		        cout << "Error al momento de leer el archivo" << endl;
		        return 0;
		    }
		
			fflush(stdin);
		    cout << "Ingrese el Numero de placa: ";
		    getline(cin, Nplaca);
		    fflush(stdin);
		    cout << "Ingrese el ID del sector Actual. Ejemplo: ID# : ";
		    getline(cin, IDSector);
		
		    while (getline(archivo, linea)) {
		        char* lineaChar = const_cast<char*>(linea.c_str());
		        id = strtok(lineaChar, ":");
		        sector = strtok(NULL, ":");
		        cedulaConductor = strtok(NULL, ":");
		       	nombreConductor = strtok(NULL, ":");
		        placa = strtok(NULL, ":");
		        modelo = strtok(NULL, ":");
		        marca = strtok(NULL, ":");
		        anio = strtok(NULL, ":");
		        disponibilidad = strtok(NULL, ":");
		        nVecesUsado = strtok(NULL,":");
		        
		        if ((id == IDSector) && (placa == Nplaca)) {
		            cout << "Vehiculo Encontrado. Sector: " << sector << endl;
		            encontrado = true;

		            cout << "Digite el ID de nuevo Sector(del 1 al 14). Ejemplo: ID#: ";
		            getline(cin, nuevoId);
		            
		            Sectores s;
		            nuevoSector = s.DevolverSector(nuevoId);
		            
		            id = nuevoId;
		            sector = nuevoSector;
		        }
		
		        // Escribir la linea (modificada o no) en el archivo temporal
		        temp <<id<<":"<<sector<<":"<<cedulaConductor<<":"<<nombreConductor<<":"<<placa<<":"<<modelo<<":"<<marca<<":"<<anio<<":"<<disponibilidad<<":"<<nVecesUsado<< endl;
		    }
		
		    if (!encontrado) {
		        cout << "La placa o el ID del sector fueron escritos de forma incorrecta. Por favor intentar mas tarde." << endl;
		    }
		
		    archivo.close();
		    temp.close();
		
		    // Reemplazar el archivo original con el temporal
		    remove("Datos Vehiculo.txt");
		    rename("temp.txt", "Datos Vehiculo.txt");
		    return atoi(nuevoId.substr(2).c_str());
		}
		//Elimina el vehiculo con sus datos seleccionados
		void EliminarVehiculo(){
			string cedulaBuscada;
			string linea;
			fstream archivo("Datos Vehiculo.txt", ios::in);
			ofstream temp("temp.txt",ios::out);
			bool encontrado = false;
			
			fflush(stdin);
			cout<<"Digite la Cedula a Buscar: ";
			getline(cin,cedulaBuscada);
			
			while(getline(archivo,linea)){
				stringstream ss(linea);
				string cedula; 
				getline(ss,cedula,':');
				getline(ss,cedula,':');
				getline(ss,cedula,':');
				
				if(cedulaBuscada != cedula){
					temp<<linea<<"\n";
				}else{
					encontrado = true;
				}
			}
			
			archivo.close();
			temp.close();
			
			remove("Datos Vehiculo.txt");
			rename("temp.txt", "Datos Vehiculo.txt");
			
		    if (!encontrado) {
			    cout << "Registro no encontrado." << endl;
			} else {
				cout << "Registro eliminado." << endl;
			}
		}
};

#endif

