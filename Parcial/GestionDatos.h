#pragma once
#include <string>
#include "Arbol.hpp"
#include "HashTable.h"
#include <iostream>
#include <conio.h>
#include <fstream> //Gestion de Archivo
#include <sstream> //stream
#include "Cliente.h"
#include "Dependencies.h"

using namespace std;

void imprimir(Cliente cliente) {
    cout << cliente.getNombreCompleto() << endl;
}

class GestionDatos {
private:
    ArbolBB<Cliente>* arbol;
    string nombre_rchivo;
    Lista<Reservacion*> listaReservaciones;
    Lista<Resena*> listaReviews;
    Lista<Cliente*> listasClientes;
    Cola<Usuario*> colaUsuarios;
public:
    HashTablaA tablaclientes;
    GestionDatos();
    void LecturaDatosArchivo();
    void Intervalo_Clientes();
    void Generar_Arbol();
    string buscar_Cliente(string nombre);
    void GenerarListaPreOrden();
    Lista<Cliente*>  getClientes() { return listasClientes; }
    void Eliminar_Cliente(string nombre);
};

GestionDatos::GestionDatos() {
    nombre_rchivo = "ClienteArchivo.csv";
    arbol = new ArbolBB<Cliente>(imprimir);
    tablaclientes = HashTablaA();


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
    archIN.open(nombre_rchivo, ios::in); // Open file for reading

    if (!archIN.is_open()) {
        cout << "Error: No se pudo abrir el archivo !!!" << endl;
        exit(1);
    }

    string linea;
    char delimitador = '|'; // Column separator
    int id = 1; // Assuming ID starts from 1

    // Skip the header line
    getline(archIN, linea);

    // Read each line
    while (getline(archIN, linea)) {
        stringstream stream(linea); // Convert line to stringstream

        string col1, col4, col5, col6;
        int col2, col3;

        getline(stream, col1, delimitador); // NombreCompleto
        string col2Str; // edad
        getline(stream, col2Str, delimitador);
        col2 = stoi(col2Str); // Convert to integer
        string col3Str; // habitacion
        getline(stream, col3Str, delimitador);
        col3 = stoi(col3Str); // Convert to integer
        getline(stream, col4, delimitador); // tipoAlojamiento
        getline(stream, col5, delimitador); // lugar
        getline(stream, col6, delimitador); // promocion

        // Create a new Cliente object

        Cliente* cliente = new Cliente(id++, col1, col2, col3, col4, col5, col6);
        Cliente* clientelista = new Cliente(id++, col1, col2, col3, col4, col5, col6);
        Cliente* clienteHash = new Cliente(id++, col1, col2, col3, col4, col5, col6);

        // Insert the client into the tree
        arbol->insertar(*cliente);
        

        // Insert the client into the hash table
        tablaclientes.insert(*clienteHash);


        // Insert the client into the list
        listasClientes.insertarFinal(clientelista);
        cout << "Cliente insertado en la lista: " << clientelista->getNombreCompleto() << endl;

        // Create a new reservation
        Reservacion* nuevaReservacion2 = new Reservacion(col1, to_string(col3));
        listaReservaciones.insertarFinal(nuevaReservacion2);

        // Add reviews (assuming AnadirReviews is defined somewhere)
        AnadirReviews(listasClientes.getInicio(), listaReviews);
        cout << "Reviews añadidas para: " << cliente->getNombreCompleto() << endl;
    }

    // Close the file
    archIN.close();
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

void GestionDatos::GenerarListaPreOrden() {
    arbol->preOrden();
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
