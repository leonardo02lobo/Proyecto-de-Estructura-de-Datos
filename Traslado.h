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

class Traslado
{
private:
    Usuario _usuario;
    Sector _sectorOrigen;
    Sector _sectorDestino;
    string _fecha;
    Cola *colaSectores;
    Cola **frente;
    Cola **final;
    Lista *lista;
    int idOrigenSeleccionado;

    bool cargarUsuarioPorCedula(int cedula)
    {
        ifstream archivo("Datos Usuarios.txt");
        if (!archivo.is_open())
        {
            cout << "Error al abrir el archivo de usuarios." << endl;
            return false;
        }

        string linea;
        archivo.seekg(0);
        while (getline(archivo, linea))
        {
            char *lineaChar = const_cast<char *>(linea.c_str());
            char *cedulaStr = strtok(lineaChar, ":");
            int cedulaArchivo = atoi(cedulaStr);

            if (cedulaArchivo == cedula)
            {
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

    void seleccionarVehiculo(Sectores &sectores)
    {
        Lista *listaTemp = NULL;

        ifstream archivo("Datos Vehiculo.txt", ios::in);
        bool disponible = false;

        if (!archivo.is_open())
        {
            cout << "Error al abrir el archivo de vehiculos." << endl;
            return;
        }

        string linea;
        vector<string> placasDisponibles;

        while (getline(archivo, linea))
        {
            char *lineaChar = const_cast<char *>(linea.c_str());
            char *idSectorChar = strtok(lineaChar, ":");
            char *nombreSector = strtok(NULL, ":");
            char *cedula = strtok(NULL, ":");
            char *nombreConductor = strtok(NULL, ":");
            char *placa = strtok(NULL, ":");
            char *modelo = strtok(NULL, ":");
            char *marca = strtok(NULL, ":");
            char *anio = strtok(NULL, ":");
            char *disponibilidad = strtok(NULL, ":");

            if (disponibilidad != "1")
            {
                Chofer chofer(nombreConductor, atoi(cedula));
                Sector sector(idSectorChar, nombreSector);
                string placaString = placa;
                string modeloString = modelo;
                string marcaString = marca;
                Vehiculo vehiculoDisponible(placaString, modeloString, marcaString, atoi(anio), chofer, sector, true);
                lista[idOrigenSeleccionado].insertarInicio(listaTemp, vehiculoDisponible);
                placasDisponibles.push_back(placa);
                disponible = true;
            }
        }
        archivo.close();

        if (!disponible)
        {
            string idString = _sectorOrigen.getId();
            int id = atoi(idString.substr(2).c_str()) - 1;

            colaSectores[id].InsertarElemento(frente[id], final[id], _usuario);
            cout << "No se encuentra ningun vehiculo disponible en el sector de origen." << endl;
            return;
        }

        cout << "\n\nVehiculos Disponibles." << endl
             << endl;
        lista[idOrigenSeleccionado].ordenarDescendente(listaTemp);
        lista[idOrigenSeleccionado].mostrar(listaTemp);

        int seleccion;
        cout << "Seleccione el numero del vehiculo para iniciar el traslado: ";
        cin >> seleccion;

        if (seleccion < 1 || seleccion > placasDisponibles.size())
        {
            cout << "Seleccion invalida. Intente de nuevo." << endl;
            return;
        }

        string placaSeleccionada = placasDisponibles[seleccion - 1];
        ifstream archivoLectura("Datos Vehiculo.txt", ios::in);
        ofstream archivoEscritura("Temp.txt", ios::out);
        string numeroDeVeces, NVecesFinal;

        while (getline(archivoLectura, linea))
        {
            stringstream ss(linea);
            for (int i = 0; i < 10; i++)
            {
                getline(ss, numeroDeVeces, ':');
            }
            if (linea.find(placaSeleccionada) != string::npos)
            {
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

                size_t pos = linea.rfind(":1");
                if (pos != string::npos)
                    linea.replace(pos, 2, ":0");

                size_t pos2 = linea.rfind(numeroDeVeces);
                if (pos2 != string::npos)
                    linea.replace(pos2, numeroDeVeces.length(), NVecesFinal);
            }
            archivoEscritura << linea << endl;
        }

        archivoLectura.close();
        archivoEscritura.close();

        remove("Datos Vehiculo.txt");
        rename("Temp.txt", "Datos Vehiculo.txt");

        cout << "El vehiculo ha sido seleccionado y esta en camino." << endl;
        lista[idOrigenSeleccionado].BuscarVehiculo(listaTemp, seleccion - 1);
    }

public:
    Traslado(Cola *&colaSectores, Cola **&frente, Cola **&final, Lista *&lista)
        : colaSectores(colaSectores), frente(frente), final(final), lista(lista)
    {
    }

    void solicitar(Sectores &sectores,Grafo *grafo)
    {
        bool band1 = false, band2 = false;
        cout << "Solicitar Traslado" << endl;

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

        for (int i = 0; i < sectores.idSectores.size(); i++)
        {
            if (sectores.idSectores[i] == _sectorOrigen.getId())
            {
                _sectorOrigen.setNombreSector(sectores.sectores[i]);
                band1 = true;
            }
            if (sectores.idSectores[i] == _sectorDestino.getId())
            {
                _sectorDestino.setNombreSector(sectores.sectores[i]);
                band2 = true;
            }
        }

        if (!band2)
        {
            cout << "El ID del sector de destino no coincide con alguno dado. Por favor intentar mas tarde." << endl;
            return;
        }

        float distancia;
        cout<<"Digite la distancia que existen entre ellas"<<endl;
        cin>>distancia;

        int idOrigen = atoi(_sectorOrigen.getId().substr(2).c_str());
        int idDestino = atoi(_sectorDestino.getId().substr(2).c_str());
        grafo->agregar(idOrigen, idDestino, distancia);
        grafo->dijkstra(idOrigen,idDestino);

        ofstream archivo("Grafo.txt",ios::app);

        if(!archivo.is_open()){
            cout<<"Error al abrir el archivo de grafo"<<endl;
            return;
        }
    
        archivo<<"\n"<<idOrigen<<","<<idDestino<<","<<distancia;
        archivo.close();

        time_t now = time(0);
        _fecha = ctime(&now);

        idOrigenSeleccionado = atoi(idSectorDestino.substr(2).c_str()) - 1;
        seleccionarVehiculo(sectores);

        Usuario u;
        u.actualizarUsoApp(cedula);
    }

    void finalizarTraslado(const string &placaVehiculo)
    {

        int idSectorVehiculo = -1;
        ifstream archivoLectura("Datos Vehiculo.txt");
        string linea;

        while (getline(archivoLectura, linea))
        {
            if (linea.find(placaVehiculo) != string::npos)
            {
                char *lineaChar = const_cast<char *>(linea.c_str());
                char *idSectorChar = strtok(lineaChar, ":");
                idSectorVehiculo = atoi(idSectorChar + 2);
                break;
            }
        }
        archivoLectura.close();

        if (idSectorVehiculo == -1)
        {
            cout << "No se encontro el vehiculo con la placa especificada." << endl;
            return;
        }

        ifstream archivoLectura2("Datos Vehiculo.txt");
        ofstream archivoEscritura("Temp.txt");

        while (getline(archivoLectura2, linea))
        {
            if (linea.find(placaVehiculo) != string::npos)
            {
                size_t pos = linea.rfind(":0");
                if (pos != string::npos)
                {
                    linea.replace(pos, 2, ":1");
                }
            }
            archivoEscritura << linea << endl;
        }

        archivoLectura2.close();
        archivoEscritura.close();

        remove("Datos Vehiculo.txt");
        rename("Temp.txt", "Datos Vehiculo.txt");

        cout << "El vehiculo con placa " << placaVehiculo << " ha sido marcado como disponible y ha regresado a la base." << endl;
    }

    void GuardarInformacionUsuarios(int cedula)
    {
        ifstream archivo("Datos Usuarios.txt");
        if (!archivo.is_open())
        {
            cout << "Error al abrir el archivo de usuarios." << endl;
            return;
        }

        string linea;
        archivo.seekg(0);
        while (getline(archivo, linea))
        {
            char *lineaChar = const_cast<char *>(linea.c_str());
            char *cedulaStr = strtok(lineaChar, ":");
            int cedulaArchivo = atoi(cedulaStr);

            if (cedulaArchivo == cedula)
            {
                _usuario.setCedula(cedulaArchivo);
                _usuario.setNombre(strtok(NULL, ":"));
                _usuario.setDireccion(strtok(NULL, ":"));
                archivo.close();
                return;
            }
        }

        archivo.close();
    }

    void RevisarCola(int id)
    {

        int opcion;
        Cola *actual = frente[id];
        while (actual != NULL)
        {
            cout << "Nombre: " << actual->usuarios.getNombre() << "\nCedula: " << actual->usuarios.getCedula() << "\nDireccion: " << actual->usuarios.getDireccion() << endl;
            cout << "\nDesea todavia el servicion(1.SI/2.NO): ";
            cin >> opcion;

            if (opcion == 1)
            {
                Sectores sectores;
                seleccionarVehiculo(sectores);
                Usuario usuario = colaSectores[id].usuarios;
                colaSectores[id].eliminarUsuario(frente[id], final[id], _usuario);
            }
            else if (opcion == 2)
            {
                colaSectores[id].eliminarUsuario(frente[id], final[id], _usuario);
            }

            system("pause");
            system("cls");
            actual = actual->siguiente;
        }
    }
    void RevisarLista(int id)
    {
        if (lista[id].esVacia())
        {
            cout << "La lista en la posicion " << id << " esta vacia." << endl;
        }
        else
        {
            cout << "La lista en la posicion " << id << " contiene elementos." << endl;
        }
    }
};
#endif