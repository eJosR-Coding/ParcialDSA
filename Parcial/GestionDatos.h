#pragma once
#include <string>
#include "Arbol.hpp"
#include "HashTable.h"
#include <iostream>
#include <conio.h>
#include <fstream> //Gestion de Archivo
#include <sstream> //stream
#include "Cliente.h"
using namespace std;

void imprimir(Cliente cliente) {
    cout << cliente.getNombreCompleto() << endl;
}

class GestionDatos {
private:
    ArbolBB<Cliente>* arbol;
    HashTablaA ht;
    string nombre_rchivo;

public:
    GestionDatos();
    void LecturaDatosArchivo();
    void Intervalo_Clientes();
    void Generar_Arbol();
    string buscar_Cliente(string nombre);
    void GenerarListaPreOrden();
    void Eliminar_Cliente(string nombre);
};

GestionDatos::GestionDatos() {
    nombre_rchivo = "ClienteArchivo.csv";
    arbol = new ArbolBB<Cliente>(imprimir);
    ht = HashTablaA();
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

    // Skip the header line
    getline(archIN, linea);

    // Read each line
    while (getline(archIN, linea)) {
        stringstream stream(linea); // Convert line to stringstream

        string col1, col3, col4, col5, col6;
        int col2, col3Int;

        getline(stream, col1, delimitador); // NombreCompleto
        string col2Str; // edad
        getline(stream, col2Str, delimitador);
        col2 = stoi(col2Str); // Convertir a entero
        string col3Str; // habitacion
        getline(stream, col3Str, delimitador);
        col3Int = stoi(col3Str); // Convertir a entero
        getline(stream, col4, delimitador); // tipoAlojamiento
        getline(stream, col5, delimitador); // lugar
        getline(stream, col6, delimitador); // promocion

        // Insertarlo en las estructuras siguiendo el ejemplo de clase
        Cliente cliente(1, col1, col2, col3Int, col4, col5, col6); // Asumiendo que el ID es 1 por simplicidad
        arbol->insertar(cliente);
        ht.insert(cliente);
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
