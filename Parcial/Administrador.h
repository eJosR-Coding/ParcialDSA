#pragma once
#ifndef ADMINISTRADOR_H
#define ADMINISTRADOR_H
#include "Dependencies.h"

#include <string>

class Administrador {
private:
    string contrasena;

public:
    Administrador(const std::string& contrasena)
        : contrasena(contrasena) {}

    bool verificarContrasena(const string& contrasenaUsuario) const {
        return (contrasenaUsuario == contrasena);
    }


    bool inicioSesion() {
        string nombreAdmin;
        string contrasenaAdmin;
        cout << "\nInicio de sesión de Administrador\n";
        cout << "Ingrese el nombre de administrador: ";
        cin >> nombreAdmin;
        cout << "Ingrese la contraseña: ";
        cin >> contrasenaAdmin;

        if (nombreAdmin == "admin" && verificarContrasena(contrasenaAdmin)) {
            cout << "Inicio de sesión exitoso.\n";
            return true; // Inicio de sesión exitoso
        }
        else {
            cout << "Nombre de usuario o contraseña incorrectos. Inténtelo nuevamente.\n";
            return inicioSesion(); // Volver a solicitar inicio de sesión
        }
    }
};

#endif