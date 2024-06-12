#pragma once
#ifndef PAGO_H
#define PAGO_H

#include "Dependencies.h"

class Pago {
private:
    int id;
    int facturaId;
    double monto;
    string metodoPago;  // Ejemplo: efectivo, tarjeta, transferencia

public:
    Pago(int id, int facturaId, double monto, string metodoPago)
        : id(id), facturaId(facturaId), monto(monto), metodoPago(metodoPago) {}

    void confirmarPago() {
        // Lógica para confirmar el pago
        cout << "Pago confirmado: " << monto << " usando " << metodoPago << endl;
        // Puedes añadir más lógica aquí, como actualizar el estado de la factura, registrar el pago en una base de datos, etc.
    }

    void mostrarDetallesPago() const {
        cout << "Pago ID: " << id << endl;
        cout << "Factura ID: " << facturaId << endl;
        cout << "Monto: $" << monto << endl;
        cout << "Método de Pago: " << metodoPago << endl;
    }
};

#endif

