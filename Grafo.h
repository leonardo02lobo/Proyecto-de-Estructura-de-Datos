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
        return make_pair(vector<DatosGrafos>(), -1);
    }

    map<int, pair<int, int> > distances;
    for (int i = 0; i < V; ++i) {
        distances[i].first = numeric_limits<int>::max();
        distances[i].second = -1;
    }
    distances[start_index].first = 0;

    priority_queue<pair<int, int>, vector<pair<int, int> >, greater<pair<int, int> > > pq;
    pq.push(make_pair(0, start_index));

    while (!pq.empty()) {
        pair<int, int> top_pair = pq.top();
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
                distances[neighbor_index].first = new_dist;
                distances[neighbor_index].second = current_node;
                pq.push(make_pair(new_dist, neighbor_index));
            }

            neighbor = neighbor->siguiente;
        }
    }

    if (distances[end_index].first == numeric_limits<int>::max()) {
        cout << "No existe un camino entre los nodos seleccionados." << endl;
        return make_pair(vector<DatosGrafos>(), -1);
    }

    vector<DatosGrafos> path;
    int current = end_index;
    while (current != -1) {
        path.push_back(vertices[current]);
        current = distances[current].second;
    }
    reverse(path.begin(), path.end());

    cout << "Distancia total del recorrido: " << distances[end_index].first << " km" << endl;

    return make_pair(path, distances[end_index].first);
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
