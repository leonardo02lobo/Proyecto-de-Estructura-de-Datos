#ifndef GRAFOH
#define GRAFOH

#include "DatosGrafos.h"
#include <vector>
#include <queue>
#include <limits>
#include <iostream>
#include <map>
#include <algorithm>

struct Node {
    DatosGrafos datos;  // Datos del vï¿½rtice
    int peso;           // Peso de la arista
    Node* siguiente;    // Puntero al siguiente nodo

    // Constructor
    Node(DatosGrafos d, int p) : datos(d), peso(p), siguiente(NULL) {}
};

using namespace std;

class Grafo {
private:
    Node** adyacencia;
    int V;
    DatosGrafos* vertices;

public:
    Grafo(int v) : V(v) {
        adyacencia = new Node*[V];
        for (int i = 0; i < V; ++i) {
            adyacencia[i] = NULL;
        }
        vertices = new DatosGrafos[V];
    }

    ~Grafo() {
        for (int i = 0; i < V; ++i) {
            Node* valor = adyacencia[i];
            while (valor != NULL) {
                Node* temp = valor;
                valor = valor->siguiente;
                delete temp;
            }
        }
        delete[] adyacencia;
        delete[] vertices;
    }

    void setVertice(int index, DatosGrafos dato) {
        if (index >= 0 && index < V) {
            vertices[index] = dato;
        } else {
            cout << "Error: Índice fuera de rango." << endl;
        }
    }

    void agregar(int i, int j, int peso) {
        appendNode(adyacencia[i], vertices[j], peso);
        appendNode(adyacencia[j], vertices[i], peso); // No dirigido
    }

    pair<vector<DatosGrafos>, int> dijkstra(int start_index, int end_index) const {
        if (start_index < 0 || start_index >= V || end_index < 0 || end_index >= V) {
            cout << "Error: Índices fuera de rango." << endl;
            return {{}, -1};
        }

        map<int, pair<int, int> > distances; // {distancia, nodo_previo}
        for (int i = 0; i < V; ++i) {
            distances[i] = {numeric_limits<int>::max(), -1};
        }
        distances[start_index] = {0, -1};

        std::priority_queue<
	    std::pair<int, int>, 
	    std::vector<std::pair<int, int> >, 
	    std::greater<std::pair<int, int> > // Especifica el tipo aquí
		> pq;
        pq.push({0, start_index});

        while (!pq.empty()) {
            pair<int, int> top_pair = pq.top(); // Especifica el tipo explícitamente
			int current_dist = top_pair.first;
			int current_node = top_pair.second;
            pq.pop();

            if (current_dist > distances[current_node].first) continue;

            if (current_node == end_index) break;

            Node* neighbor = adyacencia[current_node];
            while (neighbor != NULL) {
                int neighbor_index = findIndex(neighbor->datos);
                int new_dist = current_dist + neighbor->peso;

                if (new_dist < distances[neighbor_index].first) {
                    distances[neighbor_index] = {new_dist, current_node};
                    pq.push({new_dist, neighbor_index});
                }

                neighbor = neighbor->siguiente;
            }
        }

        vector<DatosGrafos> path;
        int current = end_index;
        while (current != -1) {
            path.push_back(vertices[current]);
            current = distances[current].second;
        }
        reverse(path.begin(), path.end());

        return {path, distances[end_index].first};
    }

private:
    void appendNode(Node*& cabeza, DatosGrafos vertice, int peso) const {
        Node* nuevoNodo = new Node(vertice, peso);
        if (cabeza == NULL) {
            cabeza = nuevoNodo;
        } else {
            Node* valor = cabeza;
            while (valor->siguiente != NULL) {
                valor = valor->siguiente;
            }
            valor->siguiente = nuevoNodo;
        }
    }

    int findIndex(DatosGrafos& dato) const {
        for (int i = 0; i < V; ++i) {
            if (vertices[i].getDistancia() == dato.getDistancia()) {
                return i;
            }
        }
        return -1;
    }
};

#endif
