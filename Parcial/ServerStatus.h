#pragma once
#ifndef SERVERSTATUS_H
#define SERVERSTATUS_H
#include "Dependencies.h"

class ServerStatus
{
private:
    bool encendido; // Estado del servidor

public:
    // Constructor
    ServerStatus() {
        encendido = true; // El servidor siempre comienza encendido
    }

    // Funci�n para encender el servidor
    void encender() {
        encendido = true;
        cout << "El servidor se ha encendido." << endl;
    }

    // Funci�n para apagar el servidor
    void apagar() {
        encendido = false;
        cout << "El servidor se ha apagado." << endl;
    }

    // Funci�n para verificar si el servidor est� encendido


};
#endif