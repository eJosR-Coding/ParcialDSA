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
        vector<CArco*> ady; // Lista(Vector) de adyacencia

        CVertice() {
            info = T();
        }
    };

    vector<CVertice*> vertices;

public:
    CGrafo() {}

    // Operaciones del Grafo
    int adicionarVertice(T info) {
        CVertice* vert = new CVertice();
        vert->info = info;
        vertices.push_back(vert);
        return static_cast<int>(vertices.size()) - 1; // retorna posición del vértice agregado (al final)
    }

    int cantidadVertices() const {
        return static_cast<int>(vertices.size());
    }

    T obtenerVertice(int v) { // Obtener Vértice dado su posición en el vector
        return vertices.at(v)->info;
    }

    void modificarVertice(int v, T info) {
        vertices.at(v)->info = info;
    }

    // Operaciones del arco
    int adicionarArco(int v, int vLlegada, double peso) {
        CVertice* ver = vertices.at(v);
        CArco* arc = new CArco(vLlegada, peso);
        ver->ady.push_back(arc);
        return static_cast<int>(ver->ady.size()) - 1;
    }

    int cantidadArcos(int v) const {
        return static_cast<int>(vertices.at(v)->ady.size());
    }

    CArco* obtenerArco(int v, int apos) {
        CVertice* ver = vertices.at(v);
        return ver->ady.at(apos);
    }

    void modificarArco(int v, int apos, T info) {
        CVertice* ver = vertices.at(v);
        ver->ady.at(apos)->info = info;
    }

    int obtenerVerticeLlegada(int v, int apos) {
        CVertice* ver = vertices.at(v);
        return ver->ady.at(apos)->v;
    }

    double obtenerPesoArco(int v, int apos) {
        CVertice* ver = vertices.at(v);
        return ver->ady.at(apos)->peso;
    }

    // Método para calcular la distancia entre dos coordenadas
    double calcularDistancia(double lat1, double lon1, double lat2, double lon2) {
        double dlat = lat2 - lat1;
        double dlon = lon2 - lon1;
        return sqrt(dlat * dlat + dlon * dlon);
    }

    // Generar conexiones entre clientes basándose en las coordenadas
    void generarConexionesAleatorias() {
        int numVertices = cantidadVertices();
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

    void mostrarGrafo() {
        if (vertices.empty()) {
            cout << "El grafo está vacío." << endl;
            return;
        }

        for (int i = 0; i < cantidadVertices(); ++i) {
            cout << "Cliente " << i << " (" << obtenerVertice(i).getNombreCompleto() << "):\n";
            for (int j = 0; j < cantidadArcos(i); ++j) {
                int destino = obtenerVerticeLlegada(i, j);
                double peso = obtenerPesoArco(i, j);
                cout << "  -> Cliente " << destino << " (" << obtenerVertice(destino).getNombreCompleto() << ") : " << peso << " km\n";
            }
            cout << endl;
        }
    }

    // Implementar Dijkstra
    void dijkstra(int src, vector<double>& dist, vector<int>& prev) {
        int V = cantidadVertices();
        dist.resize(V, INT_MAX);
        prev.resize(V, -1);
        vector<bool> sptSet(V, false);

        dist[src] = 0;

        for (int count = 0; count < V - 1; ++count) {
            int u = minDistance(dist, sptSet);
            sptSet[u] = true;

            for (int v = 0; v < V; ++v) {
                int j = obtenerVerticeLlegada2(u, v);
                CArco* arco = obtenerArco(u, j);
                if (j != -1 && !sptSet[v] && arco && dist[u] != INT_MAX && dist[u] + arco->peso < dist[v]) {
                    dist[v] = dist[u] + arco->peso;
                    prev[v] = u;
                }
            }
        }
    }

    void encontrarCaminoMasCorto(int src, int dest) {
        vector<double> dist;
        vector<int> prev;
        dijkstra(src, dist, prev);

        if (dist[dest] == INT_MAX) {
            cout << "No hay camino entre los clientes especificados." << endl;
            return;
        }

        cout << "Distancia más corta entre los clientes: " << dist[dest] << " km" << endl;
        cout << "Camino: ";
        printPath(dest, prev);
        cout << endl;
    }

private:
    int minDistance(const vector<double>& dist, const vector<bool>& sptSet) {
        double min = INT_MAX;
        int min_index = -1;

        for (int v = 0; v < static_cast<int>(dist.size()); ++v) {
            if (!sptSet[v] && dist[v] <= min) {
                min = dist[v];
                min_index = v;
            }
        }

        return min_index;
    }

    void printPath(int j, const vector<int>& prev) {
        if (prev[j] == -1)
            return;

        printPath(prev[j], prev);
        cout << j << " ";
    }

    int obtenerVerticeLlegada2(int v, int dst) {
        CVertice* ver = vertices.at(v);
        for (int j = 0; j < cantidadArcos(v); ++j) {
            int verticeLlegada = ver->ady.at(j)->v;
            if (verticeLlegada == dst) {
                return j;
            }
        }
        return -1;
    }
};

#endif // !__GRAFO_HPP__
