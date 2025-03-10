#ifndef GRAFOH
#define GRAFOH

#include "DatosGrafos.h"

struct Node {
    DatosGrafos datos;  // Datos del v�rtice
    int peso;           // Peso de la arista
    Node* siguiente;    // Puntero al siguiente nodo

    // Constructor
    Node(DatosGrafos d, int p) : datos(d), peso(p), siguiente(NULL) {}
};

using namespace std;

class Grafo {
private:
    Node** adyacencia;  // Array de listas enlazadas (lista de adyacencia)
    int V;              // N�mero de v�rtices
    DatosGrafos* vertices;  // Array de objetos DatosGrafos para identificar cada nodo

public:
    // Constructor
    Grafo(int v) : V(v) {
        adyacencia = new Node*[V];  // Inicializa el array de listas
        for (int i = 0; i < V; ++i) {
            adyacencia[i] = NULL;  // Cada lista comienza vac�a
        }
        vertices = new DatosGrafos[V];
    }

    // Destructor
    ~Grafo() {
        for (int i = 0; i < V; ++i) {
            Node* valor = adyacencia[i];
            while (valor != NULL) {
                Node* temp = valor;
                valor = valor->siguiente;
                delete temp;  // Libera memoria de cada nodo
            }
        }
        delete[] adyacencia;  // Libera el array de listas
        delete[] vertices;    // Libera el array de objetos DatosGrafos
    }

    // Asignar un objeto DatosGrafos a un v�rtice espec�fico
    void setVertice(int index, DatosGrafos dato) {
        if (index >= 0 && index < V) {
            vertices[index] = dato;
        } else {
            cout << "Error: �ndice fuera de rango." << endl;
        }
    }

    // Agregar una arista ponderada entre dos v�rtices
    void agregar(int i, int j, int peso) {
        appendNode(adyacencia[i], vertices[j], peso);  // A�ade j a la lista de i con peso
        appendNode(adyacencia[j], vertices[i], peso);  // A�ade i a la lista de j con peso (no dirigido)
    }

    // Mostrar la lista de adyacencia
    void print() const {
        for (int i = 0; i < V; ++i) {
            cout << "Nodo " << vertices[i].getDistancia() << " conectado a: ";
            Node* valor = adyacencia[i];
            while (valor != NULL) {
                cout << "(" << valor->datos.getDistancia() << ", " << valor->peso << ") ";
                valor = valor->siguiente;
            }
            cout << endl;
        }
    }

private:
    // Funci�n auxiliar para a�adir nodos al final de la lista
    void appendNode(Node*& cabeza, DatosGrafos vertice, int peso) const {
        Node* nuevoNodo = new Node(vertice, peso);
        if (cabeza == NULL) {
            cabeza = nuevoNodo;  // Si la lista est� vac�a, el nuevo nodo es el primero
        } else {
            Node* valor = cabeza;
            while (valor->siguiente != NULL) {
                valor = valor->siguiente;  // Avanza hasta el �ltimo nodo
            }
            valor->siguiente = nuevoNodo;  // Conecta el nuevo nodo al final
        }
    }
};

#endif
