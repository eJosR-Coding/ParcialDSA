#pragma once
#ifndef EVENTO_H
#define EVENTO_H

#include "Dependencies.h"

class Evento {
private:
    int id;
    string nombre;
    string fecha;
    string ubicacion;

public:
    Evento(int id, string nombre, string fecha, string ubicacion)
        : id(id), nombre(nombre), fecha(fecha), ubicacion(ubicacion) {}

    void mostrarDetallesEvento() const;
};

#endif

