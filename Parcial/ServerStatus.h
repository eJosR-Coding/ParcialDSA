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

    // Función para encender el servidor
    void encender() {
        encendido = true;
        cout << "El servidor se ha encendido." << endl;
    }

    // Función para apagar el servidor
    void apagar() {
        encendido = false;
        cout << "El servidor se ha apagado." << endl;
    }

    // Función para verificar si el servidor está encendido


};
#endif