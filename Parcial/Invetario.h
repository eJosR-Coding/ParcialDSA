#pragma once

#ifndef ARTICULO_H
#define ARTICULO_H

#include <string>

#include "Dependencies.h"
#include <vector>
// Definición de la clase Articulo
class Articulo {
private:
    // Atributos privados: nombre, precio y cantidad
    string nombre;
    double precio;
    int cantidad;

public:
    // Constructor de la clase Articulo que inicializa los atributos
    Articulo(string nombre, double precio, int cantidad)
        : nombre(nombre), precio(precio), cantidad(cantidad) {}

    // Métodos para acceder y modificar los atributos
    string getNombre() const { return nombre; }
    void setNombre(string nombre) { this->nombre = nombre; }

    double getPrecio() const { return precio; }
    void setPrecio(double precio) { this->precio = precio; }

    int getCantidad() const { return cantidad; }
    void setCantidad(int cantidad) { this->cantidad = cantidad; }
};

#endif // Fin de la definición de la clase Articulo

#ifndef INVENTARIO_H
#define INVENTARIO_H

// Definición de la clase Inventario
class Inventario {
private:
    // Atributo privado: vector que contiene objetos de tipo Articulo
    vector<Articulo> articulos;

public:
    // Método para agregar un Articulo al inventario
    void agregarArticulo(const Articulo& articulo) {
        articulos.push_back(articulo);
    }

    // Método para obtener todos los Articulos del inventario
    vector<Articulo> getArticulos() const {
        return articulos;
    }
};

#endif // Fin de la definición de la clase Inventario
