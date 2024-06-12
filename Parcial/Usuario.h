#pragma once
#ifndef USUARIO_H
#define USUARIO_H

#include "Dependencies.h"

class Usuario {
protected:
    int id;
    string nombreUsuario;
    string contraseña;
    int edad;

public:
    Usuario(int id, string nombreUsuario, string contraseña)
        : id(id), nombreUsuario(nombreUsuario), contraseña(contraseña) {}

    virtual string toString() const {
        ostringstream ss;
        ss << "Usuario(ID: " << id << ", Usuario: " << nombreUsuario << ")";
        return ss.str();
    }

    virtual string getNombre() const { return nombreUsuario; } // Método para obtener el nombre del usuario

    virtual ~Usuario() {}

    bool operator<=(const Usuario& otro) const {
        return nombreUsuario <= otro.nombreUsuario;
    }
};


#endif
