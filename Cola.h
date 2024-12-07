#ifndef COLA_H
#define COLA_H
#include<iostream>

using namespace std;

class Cola{
	public:
		Usuario usuarios;
		Cola* siguiente;
		
		void InsertarElemento(Cola*& frente,Cola*& final,Usuario elemento){
			Cola* nuevo = new Cola();
			nuevo->usuarios = elemento;
			nuevo->siguiente = NULL;
			
			if(final == NULL){
				frente = nuevo;
			}else{
				final->siguiente = nuevo;
			}
			final = nuevo;
			cout<<"Elemento Agregado a la cola"<<endl;
		}
		
		void EliminarElemento(Cola*& frente, Cola*& final){
			if(frente == NULL){
				cout<<"Cola Vacia. No existe ningun usuario registrado"<<endl;
				return;
			}
			
			frente = frente->siguiente;
			cout<<"Elemento eliminado"<<endl;
			if(frente == NULL){
				final == NULL;
			}
		}
		void mostrarCola(Cola* frente) {
		    Cola* actual = frente;
		    while (actual != NULL) {
		        cout<<actual->usuarios.getNombre()<< " -> ";
		        actual = actual->siguiente;
		    }
		    cout << "NULL" << endl;
		}
		void eliminarUsuario(Cola*& frente,Cola*& final,Usuario elemento) {
			bool band = false;
	        if (frente == NULL) {
	            cout << "La cola está vacía." << endl;
	            return;
	        }
	
	        Cola* actual = frente;
	        Cola* anterior = NULL;
	
	        while (actual != NULL) {
	            if (actual->usuarios.getCedula() == elemento.getCedula()) {
	                if (anterior == NULL) { // El usuario a eliminar es el primero
	                    frente = actual->siguiente;
	                    if (frente == NULL) { // Si la cola queda vacía
	                        final = NULL;
	                    }
	                } else {
	                    anterior->siguiente = actual->siguiente;
	                    if (actual == final) { // Si el usuario a eliminar es el último
	                        final = anterior;
	                    }
	                }
	                cout << "Usuario eliminado de la cola." << endl;
	                delete actual;
	                band = true;
	                return;
	            }
	            anterior = actual;
	            actual = actual->siguiente;
	        }
		if(!band){
			cout << "Usuario no encontrado en la cola." << endl;
		}
    }
};

#endif
