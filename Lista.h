#ifndef LISTA_H
#define LISTA_H

#include <iostream>
#include <string>
#include <sstream>
#include "Vehiculo.h"

using namespace std;

class Lista
{
public:
	Vehiculo info;
	Lista *siguiente;

public:
	bool esVacia()
	{
		return this == NULL;
	}

	void insertarInicio(Lista *&cabeza, Vehiculo valor)
	{
		Lista *nuevo = new Lista();
		nuevo->info = valor;
		nuevo->siguiente = cabeza;
		cabeza = nuevo;
	}

	void insertarFinal(Lista *&cabeza, Vehiculo valor)
	{
		Lista *nuevo = new Lista();
		nuevo->info = valor;
		nuevo->siguiente = NULL;

		if (!cabeza)
		{
			cabeza = nuevo;
			return;
		}

		Lista *temp = cabeza;
		while (temp->siguiente)
		{
			temp = temp->siguiente;
		}
		temp->siguiente = nuevo;
	}

	void eliminar(Lista *&cabeza, Vehiculo valor)
	{
		if (!cabeza)
			return;

		if (cabeza->info == valor)
		{
			Lista *temp = cabeza;
			cabeza = cabeza->siguiente;
			delete temp;
			return;
		}

		Lista *temp = cabeza;
		while (temp->siguiente && !(temp->siguiente->info == valor))
		{
			temp = temp->siguiente;
		}

		if (temp->siguiente)
		{
			Lista *eliminar = temp->siguiente;
			temp->siguiente = eliminar->siguiente;
			delete eliminar;
		}
	}

	void mostrar(Lista *&cabeza)
	{
		cout << "-----------------------------------------------" << endl;
		Lista *temp = cabeza;
		while (temp)
		{
			cout << "Marca: " << temp->info.getMarca() << "\n";
			cout << "Modelo: " << temp->info.getModelo() << "\n";
			cout << "Anio: " << temp->info.getAnio() << "\n";
			cout << "Placa: " << temp->info.getPlaca() << "\n";
			cout << "-----------------------------------------------" << endl;
			temp = temp->siguiente;
		}
	}

	void BuscarVehiculo(Lista *&cabeza, int posicion)
	{
		if (cabeza == NULL || posicion < 0)
		{
			cout << "Posicion invalida o lista vacia." << endl;
			return;
		}

		Lista *actual = cabeza;
		Lista *anterior = NULL;
		int indice = 0;

		while (actual != NULL && indice < posicion)
		{
			anterior = actual;
			actual = actual->siguiente;
			indice++;
		}

		if (actual == NULL)
		{
			cout << "Posicion fuera de rango." << endl;
			return;
		}

		if (anterior == NULL)
		{
			cabeza = actual->siguiente;
		}
		else
		{
			anterior->siguiente = actual->siguiente;
		}

		delete actual;
		cout << "Vehiculo eliminado de la lista." << endl;
	}

	void ordenarDescendente(Lista *cabeza)
	{
		if (cabeza == NULL || cabeza->siguiente == NULL)
			return;

		Lista *actual;
		Lista *siguiente;
		bool intercambiado;

		do
		{
			intercambiado = false;
			actual = cabeza;

			while (actual->siguiente != NULL)
			{
				siguiente = actual->siguiente;

				if (actual->info.getAnio() < siguiente->info.getAnio())
				{
					std::swap(actual->info, siguiente->info);
					intercambiado = true;
				}

				actual = actual->siguiente;
			}
		} while (intercambiado);
	}
};

#endif
