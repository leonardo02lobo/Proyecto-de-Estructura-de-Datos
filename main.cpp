/*
Integrantes del proyecto
Leonardo Jose Lobo Candelario V-31.489.733
Moises David Becerra Salamanca V-30.965.748
Luis Alfonso Omaña Colmenares V-31.180.408
*/
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
#include "Menu.h"

using namespace std;

int main(int argc, char** argv) {
	Grafo grafo(numeroSectores.numSectores);
	MenuServicios m;
    m.GenerarGrafodesdeArchivo(grafo);
    Menu::mostrarMenuPrincipal(grafo);
    m.LiberarGrafo();
    return 0;
}