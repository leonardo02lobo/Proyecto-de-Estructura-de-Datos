#ifndef GRAFOH
#define GRAFOH

#include "DatosGrafos.h"
#include <vector>
#include <queue>
#include <limits>
#include <iostream>
#include <map>
#include <algorithm>

struct Node
{
    DatosGrafos datos;
    int peso;
    Node *siguiente;

    Node(DatosGrafos d, int p) : datos(d), peso(p), siguiente(NULL) {}
};

using namespace std;

class Grafo
{
private:
    Node **adyacencia;
    int V;
    DatosGrafos *vertices;

public:
    Grafo()
    {
        V = 0;
        adyacencia = NULL;
        vertices = NULL;
    }
    Grafo(int v) : V(v)
    {
        adyacencia = new Node *[V];
        for (int i = 0; i < V; ++i)
        {
            adyacencia[i] = NULL;
        }
        vertices = new DatosGrafos[V];
    }

    ~Grafo()
    {
        for (int i = 0; i < V; ++i)
        {
            Node *valor = adyacencia[i];
            while (valor != NULL)
            {
                Node *temp = valor;
                valor = valor->siguiente;
                delete temp;
            }
        }
        delete[] adyacencia;
        delete[] vertices;
    }

    void setV(int v)
    {
        V = v;
        adyacencia = new Node *[V];
        for (int i = 0; i < V; ++i)
        {
            adyacencia[i] = NULL;
        }
        vertices = new DatosGrafos[V];
    }

    void setVertice(int index, DatosGrafos dato)
    {
        if (index >= 0 && index < V)
        {
            vertices[index] = dato;
        }
        else
        {
            cout << "Error: indice fuera de rango." << endl;
        }
    }

    void agregar(int i, int j, int peso)
    {
        appendNode(adyacencia[i], vertices[j], peso);
        appendNode(adyacencia[j], vertices[i], peso);
    }

    int dijkstra(int start_index, int end_index) const
    {
        if (start_index < 0 || start_index >= V || end_index < 0 || end_index >= V)
        {
            cout << "Error: indice fuera de rango." << endl;
            return -1;
        }

        vector<int> dist(V, numeric_limits<int>::max());
        dist[start_index] = 0;

        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
        pq.push({0, start_index});

        while (!pq.empty())
        {
            int u = pq.top().second;
            pq.pop();

            if (u == end_index)
                break;

            Node *neighbor = adyacencia[u];
            while (neighbor != NULL)
            {
                int v = findIndex(neighbor->datos);
                int weight = neighbor->peso;

                if (dist[u] + weight < dist[v])
                {
                    dist[v] = dist[u] + weight;
                    pq.push({dist[v], v});
                }

                neighbor = neighbor->siguiente;
            }
        }

        if (dist[end_index] == numeric_limits<int>::max())
        {
            return -1; // No se encontró una ruta válida
        }

        return dist[end_index];
    }

    void mostrarConexiones() const
    {
        for (int i = 0; i < V; ++i)
        {
            cout << "Nodo " << i << " conectado a: ";
            Node *neighbor = adyacencia[i];
            while (neighbor != NULL)
            {
                cout << "(" << findIndex(neighbor->datos) << ", " << neighbor->peso << ") ";
                neighbor = neighbor->siguiente;
            }
            cout << endl;
        }
    }

private:
    void appendNode(Node *&cabeza, DatosGrafos vertice, int peso) const
    {
        Node *nuevoNodo = new Node(vertice, peso);
        if (cabeza == NULL)
        {
            cabeza = nuevoNodo;
        }
        else
        {
            Node *valor = cabeza;
            while (valor->siguiente != NULL)
            {
                valor = valor->siguiente;
            }
            valor->siguiente = nuevoNodo;
        }
    }

    int findIndex(DatosGrafos &dato) const
    {
        for (int i = 0; i < V; ++i)
        {
            if (vertices[i].getDistancia() == dato.getDistancia())
            {
                return i;
            }
        }
        return -1;
    }
};

#endif