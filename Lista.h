#ifndef LISTA_H
#define LISTA_H

#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include "Vehiculo.h" 

using namespace std;

class Lista {
private:
    vector<Vehiculo> vehiculos;  // Vector para almacenar los vehiculos

public:
    // Agregar un vehiculo a la lista
    void agregarVehiculo(const Vehiculo& vehiculo) {
        vehiculos.push_back(vehiculo);
    }

    // Eliminar un vehiculo de la lista dado su indice
    void eliminarVehiculo(int index) {
        if (index >= 0 && index < vehiculos.size()) {
            vehiculos.erase(vehiculos.begin() + index);
        }
    }

    // Mostrar los vehiculos disponibles en la lista
    void mostrarVehiculos() {
        bool encontrado = false;
        cout << "\nVeh?culos Disponibles:" << endl;
        cout << "-----------------------------------------------" << endl;

        for (int i = 0; i < vehiculos.size(); i++) {
            // Verificar disponibilidad antes de mostrar
            if (vehiculos[i].getDisponible()) {
                cout << i + 1 << ". Conductor: " << vehiculos[i].getChofer().getNombreConductor() << endl;
                cout << "   Placa: " << vehiculos[i].getPlaca() << endl;
                cout << "   Modelo: " << vehiculos[i].getModelo() << endl;
                cout << "   Marca: " << vehiculos[i].getMarca() << endl;
                cout << "   A?o: " << vehiculos[i].getAnio() << endl;
                cout << "-----------------------------------------------" << endl;
                encontrado = true;
            }
        }

        if (!encontrado) {
            cout << "No hay veh?culos disponibles en el sector." << endl;
        }
    }

    // Ordenar vehiculos por año de manera descendente
    void ordenarPorAnio() {
        for (int i = 0; i < vehiculos.size(); i++) {
            for (int j = 0; j < vehiculos.size() - 1 - i; j++) {
                if (vehiculos[j].getAnio() < vehiculos[j + 1].getAnio()) {
                    swap(vehiculos[j], vehiculos[j + 1]);
                }
            }
        }
    }

    // Seleccionar un vehiculo de la lista, usando su indice
    Vehiculo seleccionarVehiculo(int index) {
        if (index >= 0 && index < vehiculos.size()) {
            // Desmarcar como disponible el veh?culo seleccionado
            vehiculos[index].setDisponible(false);
            return vehiculos[index];
        }
        return Vehiculo(); // Devolver un vehiculo vacio si el indice es incorrecto
    }

    // Obtener el tamaño de la lista de vehiculos
    int tamano() {
        return vehiculos.size();
    }
};

#endif



