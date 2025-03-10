#ifndef GRAFOH
#define GRAFOH

#include "DatosGrafos.h"

struct Node{
	DatosGrafos datos;
	int peso;
	Node* siguiente;
	
	Node(DatosGrafos d, int p) : datos(d),peso(p),siguiente(NULL){}
};

using namespace std;

class Grafo{
	private:
		Lista** adyacencia;
		int vertices;
		DatosGrafos* vertices;
	public:
		Grafo(int vertices) : this->vertices(vertices){
			adyacencia = new Lista*[vertices];
			for(int i = 0; i < vertices; i++){
				adyacencia[i] = NULL;
			}
		}
		
		~Grafo(){
			for(int i = 0; i < vertices; i++){
				Lista* valor = adyacencia[i];
				while(valor != NULL){
					Lista* temp = valor;
					valor = valor->siguiente;
					delete temp;
				}
			}
			delete[] adyacencia;
			delete[] vertices;
		}
		
		void setVertice(int index, DatosGrafos dato){
			if(index >= 0 && index < vertices){
				vertices[index] = dato;
			}else{
				cout<< "Error: Indice fuera de rango"<<endl;
			}
		}
		
		void agregar(int i, int j,int peso){
			appendNode(adyacencia[i],adyacencia[j],peso);
			appendNode(adyacencia[j],adyacencia[i],peso);
		}
		
		void print() const {
			for(int i = 0; i < vertices; i++){
				cout<<"Nodo "<<vertices[i]<<" conectado a: ";
				Node* valor = adyacencia[i];
				while(valor != NULL){
					cout<<"("<<valor->datos<<", "<<valor->peso<<") ";
					valor = valor->siguiente;
				}
				cout<<endl;
			}
		}
		
		private:
			void appendNode(Node*& cabeza,DatosGrafos vertice,int peso) const {
				Node* nuevoNodo = new Node(vertice,peso);
				if(cabeza == NULL){
					cabeza = nuevoNodo;
				}else{
					Node* valor = cabeza;
					while(valor->siguiente != NULL){
						valor = valor->siguiente;
					}
					valor->siguiente = nuevoNodo;
				}
			}
};
#endif
