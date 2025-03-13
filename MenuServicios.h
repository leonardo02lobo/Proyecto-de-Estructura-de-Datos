
#ifndef MENUSERVICIOS_H
#define MENUSERVICIOS_H

#include <iostream>
#include <windows.h>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include <vector>
#include <limits>
#include "Usuario.h"
#include "Vehiculo.h"
#include "Chofer.h"
#include "Sector.h"
#include "Traslado.h"
#include "Estadisticas.h"
#include "Sectores.h"
#include "DatosGrafos.h"
#include "Grafo.h"

Sectores numeroSectores;
Cola *colaSectores = new Cola[numeroSectores.numSectores];
Cola **frente = new Cola *[numeroSectores.numSectores];
Cola **final = new Cola *[numeroSectores.numSectores];
Lista *lista = new Lista[numeroSectores.numSectores];
int **adyacenciaMatriz = NULL; // Matriz global para almacenar el grafo
int N = 0;                     // Tamaño de la matriz

class MenuServicios
{
public:
    static void mostrarMenuServicios(Grafo &grafo)
    {
        int opcion = 0;
        Sectores sectores;
        Vehiculo vehiculo;
        Traslado traslado(colaSectores, frente, final, lista);
        do
        {
            do
            {
                system("cls");
                fflush(stdin);

                cout << "-------------------------";

                cout << "|   Servicios diarios   |";

                cout << "------------------------";
                ;
                cout << "\nElije una opcion" << endl;

                cout << "1. Actualizar Ubicacion Vehiculo" << endl;

                cout << "2. Solicitar Traslado" << endl;

                cout << "3. Finalizar Traslado" << endl;

                cout << "4. Imprimir Reporte" << endl;

                cout << "5. Generar Grafo de Sectores" << endl;

                cout << "6. Calcular todas las rutas" << endl;

                cout << "7. Salir" << endl;

                cout << "Ingrese la opcion: " << endl;

                cin >> opcion;

                if (opcion < 1 || opcion > 7)
                {

                    cout << "La opcion ingresa es invalida" << endl;
                    system("pause");
                }
                system("cls");
            } while (opcion < 1 || opcion > 7);
            switch (opcion)
            {
            case 1:
            {
                int id = vehiculo.ActualizarUbicacionVehiculo();
                traslado.RevisarCola(id);
                traslado.RevisarLista(id);
                break;
            }
            case 2:
                traslado.solicitar(sectores,&grafo);
                break;
            case 3:
            {
                string placa;
                cout << "Ingrese la placa del vehiculo para finalizar el traslado: ";
                cin >> placa;
                traslado.finalizarTraslado(placa);
            }
            break;
            case 4:
            {
                Estadisticas e;
                e.generarReporte();

                cout << "Estadisticas Hechas. El archivo se encuentra en la raiz del proyecto." << endl;
                break;
            }
            case 5:
                GenerarGrafodesdeArchivo(grafo);
                break;
            case 6:
                grafo.mostrarConexiones();
                break;
            case 7:
                cout << "Volver al Menu Anterior." << endl;
                break;
            }
            system("pause");
        } while (opcion != 7);
    }

    static void GenerarGrafodesdeArchivo(Grafo &grafo)
    {
        string nombreDelArchivo = "Grafo.txt";
        ifstream file(nombreDelArchivo.c_str());

        if (!file.is_open())
        {
            cout << "No se pudo abrir el archivo 'Grafo.txt'" << endl;
            return;
        }

        int maxSectores = 0;
        vector<DatosGrafos> hijos;
        string linea;

        while (getline(file, linea))
        {
            int sectorLlegada, sectorDestino;
            float distancia;
            char coma;
            stringstream ss(linea);

            ss >> sectorLlegada >> coma >> sectorDestino >> coma >> distancia;

            maxSectores = max(maxSectores, max(sectorLlegada, sectorDestino));

            DatosGrafos datos(sectorLlegada, sectorDestino, distancia);
            hijos.push_back(datos);
        }
        file.close();

        for (int i = 0; i < hijos.size(); i++)
        {
            int sector1 = hijos[i].getIDSectorLlegada();
            int sector2 = hijos[i].getIDSectorDestino();
            int distancia = hijos[i].getDistancia();

            grafo.agregar(sector1, sector2, distancia);
        }

        cout << "Lista de adyacencia generada." << endl;
    }

    void LiberarGrafo()
    {
        if (adyacenciaMatriz != NULL)
        {
            for (int i = 0; i < N; ++i)
            {
                delete[] adyacenciaMatriz[i];
            }
            delete[] adyacenciaMatriz;
            adyacenciaMatriz = NULL;
        }
    }
};

#endif // MENUSERVICIOS_H