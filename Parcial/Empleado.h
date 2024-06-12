#pragma once
#ifndef EMPLEADO_H
#define EMPLEADO_H

#include "Usuario.h"
#include "Dependencies.h"

class Empleado : public Usuario {
private:
    string nombreCompleto;
    int edad;
    string tipoAlojamiento;
    string lugartrabajo;
    string departamentotrabajo;
    string contrasena;

public:
    Empleado(int id, string nombreCompleto, int edad, string tipoAlojamiento, string departamentotrabajo, string lugartrabajo, string contrasena)
        : Usuario(id, nombreCompleto, contrasena),
        nombreCompleto(nombreCompleto),
        edad(edad),
        tipoAlojamiento(tipoAlojamiento),
        departamentotrabajo(departamentotrabajo),
        lugartrabajo(lugartrabajo),
        contrasena(contrasena) {}

    string toString() const override {
        ostringstream ss;
        ss << "ID: " << id << endl;
        ss << "Nombre Completo: " << nombreCompleto << endl;
        ss << "Edad: " << edad << endl;
        ss << ":Tipo Alojamiento: " << tipoAlojamiento << endl;
        ss << "Departamento Trabajo: " << departamentotrabajo << endl;
        ss << "Lugar Trabajo: " << lugartrabajo << endl;
        ss << "Contrasena: " << contrasena << endl;
        return ss.str();
    }
    string getNombreCompleto() const { return nombreCompleto; }
    void setNombreCompleto(const string& nombreCompleto) { this->nombreCompleto = nombreCompleto; }

    int getEdad() const { return edad; }
    void setEdad(int edad) { this->edad = edad; }

    string getTipoAlojamiento() const { return tipoAlojamiento; }
    void setTipoAlojamiento(const string& tipoAlojamiento) { this->tipoAlojamiento = tipoAlojamiento; }

    string getdepartamentotrabajo() const { return departamentotrabajo; }
    void setdepartamentotrabajo(const string& departamentotrabajo) { this->departamentotrabajo = departamentotrabajo; }

    string getlugartrabajo() const { return lugartrabajo; }
    void setlugartrabajo(const string& lugartrabajo) { this->lugartrabajo = lugartrabajo; }

    string getcontrasena() const { return contrasena; }
    void setcontrasena(const string& contraseña) { this->contrasena = contrasena; }

};

#endif