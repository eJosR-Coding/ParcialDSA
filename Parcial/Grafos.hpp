#pragma once
#ifndef __GRAFO_HPP__
#define __GRAFO_HPP__

#include <vector>
#include <iostream>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <climits>
#include "Cliente.h"
using namespace std;

template<class T>
class CGrafo {
private:
    class CArco {
    public:
        T info;
        int v; // índice del vértice de llegada del Arco
        double peso; // peso del arco

        CArco(int vLlegada, double peso) {
            info = T();
            v = vLlegada;
            this->peso = peso;
        }
    };

    class CVertice {
    public:
        T info;
        vector<CArco*>* ady; // Lista(Vector) de adyacencia

        CVertice() {
            info = T();
            ady = new vector<CArco*>();
        }
    };

    vector<CVertice*>* vertices;

public:
    CGrafo() {
        vertices = new vector<CVertice*>();
    }

    // Operaciones del Grafo
    int adicionarVertice(T info) {
        CVertice* vert = new CVertice();
        vert->info = info;
        vertices->push_back(vert);
        return static_cast<int>(vertices->size()) - 1; // retorna posición del vértice agregado (al final)
    }

    int cantidadVertices() const {
        return vertices->size();
    }

    T obtenerVertice(int v) { // Obtener Vértice dado su posición en el vector
        return (vertices->at(v))->info;
    }

    void modificarVertice(int v, T info) {
        (vertices->at(v))->info = info;
    }

    // Operaciones del arco
    int adicionarArco(int v, int vLlegada, double peso) {
        CVertice* ver = vertices->at(v);
        CArco* arc = new CArco(vLlegada, peso);
        ver->ady->push_back(arc);
        return static_cast<int>(ver->ady->size()) - 1;
    }

    int cantidadArcos(int v) const {
        return static_cast<int>(vertices->at(v)->ady->size());
    }

    T obtenerArco(int v, int apos) {
        CVertice* ver = vertices->at(v);
        return (ver->ady->at(apos))->info;
    }

    void modificarArco(int v, int apos, T info) {
        CVertice* ver = vertices->at(v);
        (ver->ady->at(apos))->info = info;
    }

    int obtenerVerticeLlegada(int v, int apos) {
        CVertice* ver = vertices->at(v);
        return (ver->ady->at(apos))->v;
    }

    double obtenerPesoArco(int v, int apos) {
        CVertice* ver = vertices->at(v);
        return (ver->ady->at(apos))->peso;
    }

    // Método para calcular la distancia entre dos coordenadas
    double calcularDistancia(double lat1, double lon1, double lat2, double lon2) {
        double dlat = lat2 - lat1;
        double dlon = lon2 - lon1;
        return sqrt(dlat * dlat + dlon * dlon);
    }

    // Generar conexiones entre clientes basándose en las coordenadas
    void generarConexionesAleatorias() {
        int numVertices = static_cast<int>(cantidadVertices());
        if (numVertices < 2) {
            cout << "No hay suficientes vértices para generar conexiones." << endl;
            return;
        }

        for (int i = 0; i < numVertices; ++i) {
            for (int j = i + 1; j < numVertices; ++j) {
                T cliente1 = obtenerVertice(i);
                T cliente2 = obtenerVertice(j);
                double distancia = calcularDistancia(cliente1.getLatitud(), cliente1.getLongitud(), cliente2.getLatitud(), cliente2.getLongitud());
                adicionarArco(i, j, distancia);
                adicionarArco(j, i, distancia);
                cout << "Conexión generada entre " << cliente1.getNombreCompleto() << " y " << cliente2.getNombreCompleto() << " con distancia " << distancia << " km\n"; // Depuración
            }
        }
        cout << "Conexiones generadas exitosamente.\n";
    }

    void CGrafo<T>::mostrarGrafo() {
        if (vertices->empty()) {
            cout << "El grafo está vacío." << endl;
            return;
        }

        for (int i = 0; i < cantidadVertices(); ++i) {
            cout << "Cliente " << i << " (" << obtenerVertice(static_cast<int>(i)).getNombreCompleto() << "):\n";
            for (int j = 0; j < cantidadArcos(static_cast<int>(i)); ++j) {
                int destino = obtenerVerticeLlegada(static_cast<int>(i), static_cast<int>(j));
                double peso = obtenerPesoArco(static_cast<int>(i), static_cast<int>(j));
                cout << "  -> Cliente " << destino << " (" << obtenerVertice(destino).getNombreCompleto() << ") : " << peso << " km\n";
            }
            cout << endl;
        }
    }

    // Implementar Dijkstra
    void dijkstra(int src) {
        const int V = static_cast<int>(cantidadVertices());
        vector<double> dist(V, INT_MAX);
        vector<bool> sptSet(V, false);

        dist[src] = 0;

        for (int count = 0; count < V - 1; ++count) {
            int u = minDistance(dist, sptSet);
            sptSet[u] = true;

            for (int v = 0; v < V; ++v) {
                int j = obtenerVerticeLlegada2(u, v);
                if (j != -1 && !sptSet[v] && obtenerArco(u, j) && dist[u] != INT_MAX && dist[u] + obtenerPesoArco(u, j) < dist[v]) {
                    dist[v] = dist[u] + obtenerPesoArco(u, j);
                }
            }
        }

        printSolution(dist);
    }

private:
    int minDistance(vector<double>& dist, vector<bool>& sptSet) {
        double min = INT_MAX;
        int min_index;

        for (int v = 0; v < static_cast<int>(dist.size()); ++v)
            if (!sptSet[v] && dist[v] <= min)
                min = dist[v], min_index = v;

        return min_index;
    }

    void printSolution(vector<double>& dist) {
        cout << "Vertice \t Distancia desde Origen\n";
        for (int i = 0; i < static_cast<int>(dist.size()); ++i)
            cout << i << " \t\t " << dist[i] << endl;
    }

    int obtenerVerticeLlegada2(int v, int dst) {
        CVertice* ver = vertices->at(v);
        for (int j = 0; j < cantidadArcos(v); ++j) {
            int verticeLlegada = ver->ady->at(j)->v;
            if (verticeLlegada == dst) {
                return j;
            }
        }
        return -1;
    }
};

#endif // !__GRAFO_HPP__
