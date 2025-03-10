#ifndef GRAFOH
#define GRAFOH

#include "DatosGrafos.h"

struct Node {
    DatosGrafos datos;  // Datos del vértice
    int peso;           // Peso de la arista
    Node* siguiente;    // Puntero al siguiente nodo

    // Constructor
    Node(DatosGrafos d, int p) : datos(d), peso(p), siguiente(NULL) {}
};

using namespace std;

class Grafo {
private:
    Node** adyacencia;  // Array de listas enlazadas (lista de adyacencia)
    int V;              // Número de vértices
    DatosGrafos* vertices;  // Array de objetos DatosGrafos para identificar cada nodo

public:
    // Constructor
    Grafo(int v) : V(v) {
        adyacencia = new Node*[V];  // Inicializa el array de listas
        for (int i = 0; i < V; ++i) {
            adyacencia[i] = NULL;  // Cada lista comienza vacía
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

    // Asignar un objeto DatosGrafos a un vértice específico
    void setVertice(int index, DatosGrafos dato) {
        if (index >= 0 && index < V) {
            vertices[index] = dato;
        } else {
            cout << "Error: Índice fuera de rango." << endl;
        }
    }

    // Agregar una arista ponderada entre dos vértices
    void agregar(int i, int j, int peso) {
        appendNode(adyacencia[i], vertices[j], peso);  // Añade j a la lista de i con peso
        appendNode(adyacencia[j], vertices[i], peso);  // Añade i a la lista de j con peso (no dirigido)
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
    // Función auxiliar para añadir nodos al final de la lista
    void appendNode(Node*& cabeza, DatosGrafos vertice, int peso) const {
        Node* nuevoNodo = new Node(vertice, peso);
        if (cabeza == NULL) {
            cabeza = nuevoNodo;  // Si la lista está vacía, el nuevo nodo es el primero
        } else {
            Node* valor = cabeza;
            while (valor->siguiente != NULL) {
                valor = valor->siguiente;  // Avanza hasta el último nodo
            }
            valor->siguiente = nuevoNodo;  // Conecta el nuevo nodo al final
        }
    }
};

#endif
