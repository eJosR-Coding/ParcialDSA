#pragma once
#ifndef RESERVACION_H
#define RESERVACION_H

#include "Dependencies.h"
using namespace std;

class Reservacion {
private:
    string nombreCliente;
    string numeroHabitacion;

public:
    Reservacion(string nombreCliente, string numeroHabitacion)
        : nombreCliente(nombreCliente), numeroHabitacion(numeroHabitacion) {}

    void mostrarDetalles() const {
        cout << "Cliente: " << nombreCliente << ", Habitación: " << numeroHabitacion << endl;
    }

    static void mostrarReservaciones(const Lista<Reservacion*>& listaReservaciones) {
        if (listaReservaciones.getTamano() == 0) {
            cout << "No hay reservaciones registradas." << endl;
        }
        else {
            Nodo<Reservacion*>* actual = listaReservaciones.getInicio();
            while (actual != nullptr) {
                actual->valor->mostrarDetalles();
                actual = actual->siguiente;
            }
        }
    }
};
#endif
