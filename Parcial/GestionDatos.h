#pragma once
#include <string>
#include "Arbol.hpp"
#include "HashTable.h"
#include <iostream>
#include <conio.h>
#include <fstream>
#include <sstream>
#include "Cliente.h"
#include "Dependencies.h"
#include "Grafos.hpp"
#include "Lista.h"
#include "Cola.h"
#include "Reservacion.h"
#include "Resena.h"
using namespace std;

void imprimir(Cliente cliente) {
    cout << cliente.getNombreCompleto() << endl;
}

class GestionDatos {
private:
    ArbolBB<Cliente>* arbol;
    string nombre_archivo;

    Cola<Usuario*> colaUsuarios;
    CGrafo<Cliente> grafo;

public:
    HashTablaA tablaclientes;
    GestionDatos();

    void LecturaDatosArchivo();
    void Intervalo_Clientes();
    void Generar_Arbol();
    string buscar_Cliente(string nombre);
    void GenerarListaPreOrden();
    ArbolBB<Cliente>* getArbol() { return arbol; }
    HashTablaA& getTablaClientes() { return tablaclientes; }
    void Eliminar_Cliente(string nombre);

    // Métodos públicos para interactuar con el grafo
    void mostrarGrafo() { grafo.mostrarGrafo(); }
    void generarConexionesAleatorias() { grafo.generarConexionesAleatorias(); }
    void adicionarVerticeGrafo(Cliente cliente) { grafo.adicionarVertice(cliente); }
    CGrafo<Cliente>& getGrafo() { return grafo; } // Método para obtener una referencia al grafo


    // Métodos para mostrar el árbol
    void mostrarArbolEnOrden() { arbol->enOrden(); }
    void mostrarArbolPreOrden() { arbol->preOrden(); }
    void mostrarArbolPostOrden() { arbol->postOrden(); }
    void encontrarCaminoMasCorto(const string& nombre1, const string& nombre2);
};

GestionDatos::GestionDatos() {
    nombre_archivo = "ClienteArchivoActualizado.csv";
    arbol = new ArbolBB<Cliente>(imprimir);
    tablaclientes = HashTablaA();
}

void GestionDatos::encontrarCaminoMasCorto(const string& nombre1, const string& nombre2) {
    int src = -1;
    int dest = -1;

    for (int i = 0; i < grafo.cantidadVertices(); ++i) {
        if (grafo.obtenerVertice(i).getNombreCompleto() == nombre1) {
            src = i;
        }
        if (grafo.obtenerVertice(i).getNombreCompleto() == nombre2) {
            dest = i;
        }
    }

    if (src == -1 || dest == -1) {
        cout << "Uno o ambos nombres no se encontraron en el grafo." << endl;
        return;
    }

    vector<double> dist;
    vector<int> prev;
    grafo.dijkstra(src, dist, prev);

    if (dist[dest] == INT_MAX) {
        cout << "No hay camino entre los clientes especificados." << endl;
        return;
    }

    cout << "Distancia más corta entre los clientes: " << dist[dest] << " km" << endl;
    cout << "Camino: ";
    int u = dest;
    while (prev[u] != -1) {
        cout << grafo.obtenerVertice(u).getNombreCompleto() << " <- ";
        u = prev[u];
    }
    cout << grafo.obtenerVertice(src).getNombreCompleto() << endl;
}


void AnadirReviews(Nodo<Cliente*>* nodoCliente, Lista<Resena*>& listaReviews) {
    if (nodoCliente == nullptr) {
        return;
    }

    Usuario* usuario = nodoCliente->valor;
    Cliente* cliente = dynamic_cast<Cliente*>(usuario);

    if (cliente != nullptr) {
        string nombre = cliente->getNombreCompleto();
        int habitacion = cliente->getHabitacion();
        int rating = rand() % 10 + 1;
        Resena* nuevaReview = new Resena(listaReviews.getTamano() + 1, nombre, "Reseña sobre la habitación: " + std::to_string(habitacion), rating);
        listaReviews.insertarFinal(nuevaReview);
    }

    AnadirReviews(nodoCliente->siguiente, listaReviews);
}

void AnadirReviews(Nodo<Usuario*>* nodoCliente, Lista<Resena*>& listaReviews) {
    if (nodoCliente == nullptr) {
        return;
    }

    Usuario* usuario = nodoCliente->valor;
    Cliente* cliente = dynamic_cast<Cliente*>(usuario);

    if (cliente != nullptr) {
        string nombre = cliente->getNombreCompleto();
        int habitacion = cliente->getHabitacion();
        int rating = rand() % 10 + 1;
        Resena* nuevaReview = new Resena(listaReviews.getTamano() + 1, nombre, "Reseña sobre la habitación: " + std::to_string(habitacion), rating);
        listaReviews.insertarFinal(nuevaReview);
    }

    AnadirReviews(nodoCliente->siguiente, listaReviews);
}

void GestionDatos::LecturaDatosArchivo() {
    ifstream archIN;
    archIN.open(nombre_archivo, ios::in); // Open file for reading

    if (!archIN.is_open()) {
        cout << "Error: No se pudo abrir el archivo !!!" << endl;
        exit(1);
    }

    string linea;
    char delimitador = '|';
    int id = 1;

    getline(archIN, linea);

    // Read each line
    while (getline(archIN, linea)) {
        stringstream stream(linea);

        string col1, col4, col5, col6, col7, col8;
        int col2, col3;
        double col7Double, col8Double;

        getline(stream, col1, delimitador); // NombreCompleto
        string col2Str; // edad
        getline(stream, col2Str, delimitador);
        col2 = stoi(col2Str);
        string col3Str; // habitacion
        getline(stream, col3Str, delimitador);
        col3 = stoi(col3Str);
        getline(stream, col4, delimitador); // tipoAlojamiento
        getline(stream, col5, delimitador); // lugar
        getline(stream, col6, delimitador); // promocion
        getline(stream, col7, delimitador); // latitud
        col7Double = stod(col7);
        getline(stream, col8, delimitador); // longitud
        col8Double = stod(col8);

        Cliente* cliente = new Cliente(id++, col1, col2, col3, col4, col5, col6);
        cliente->setLatitud(col7Double);
        cliente->setLongitud(col8Double);

        grafo.adicionarVertice(*cliente);

        arbol->insertar(*cliente);
        tablaclientes.insert(*cliente);

        cout << "Cliente insertado :d: " << cliente->getNombreCompleto() << endl;
    }

    archIN.close();
}

void GestionDatos::GenerarListaPreOrden() {
    arbol->preOrden();
}

void GestionDatos::Generar_Arbol() {
    arbol->imprimirArbol();
}

void GestionDatos::Intervalo_Clientes() {
    arbol->Intervalo_Clientes(Cliente(0, "R", 0, 0, "", "", ""), Cliente(0, "S", 0, 0, "", "", ""));
}

string GestionDatos::buscar_Cliente(string nombre) {
    Cliente cliente(0, nombre, 0, 0, "", "", "");
    if (arbol->buscar(cliente)) {
        return "Cliente encontrado";
    }
    else {
        return "Cliente no encontrado";
    }
}

void GestionDatos::Eliminar_Cliente(string nombre) {
    Cliente cliente(0, nombre, 0, 0, "", "", "");
    if (arbol->eliminar(cliente)) {
        cout << "Cliente eliminado con éxito" << endl;
    }
    else {
        cout << "No se pudo encontrar el cliente para eliminar" << endl;
    }
}
