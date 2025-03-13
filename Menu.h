// Menu.h
#ifndef MENU_H
#define MENU_H

#include <iostream>
#include "MenuGestion.h"
#include "MenuServicios.h"

class Menu {
public:
    static void mostrarMenuPrincipal(Grafo &grafo) {
        int opcion;
        do {
            std::cout << "\n=== Menu Principal ===\n";
            std::cout << "1. Gestion del Sistema\n";
            std::cout << "2. Servicios\n";
            std::cout << "3. Salir\n";
            std::cout << "Seleccione una opcion: ";
            std::cin >> opcion;

            switch (opcion) {
                case 1:
                    MenuGestion::mostrarMenuGestion();
                    break;
                case 2:
                    MenuServicios::mostrarMenuServicios(grafo);
                    break;
                case 3:
                    std::cout << "Saliendo del sistema...\n";
                    break;
                default:
                    std::cout << "Opcion invalida. Intente nuevamente.\n";
            }
        } while (opcion != 3);
    }
};

#endif // MENU_H