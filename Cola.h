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
};
