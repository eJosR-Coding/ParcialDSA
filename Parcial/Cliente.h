#pragma once
#ifndef CLIENTE_H
#define CLIENTE_H

#include "Usuario.h"
#include <string>
#include <sstream>

class Cliente : public Usuario {
private:
    std::string nombreCompleto;
    int edad;
    int habitacion;
    std::string tipoAlojamiento;
    std::string lugar;
    std::string promocion;

public:
    // Constructor with default values
    Cliente(int id = 0, std::string nombreCompleto = "", int edad = 0, int habitacion = 0, std::string tipoAlojamiento = "", std::string lugar = "", std::string promocion = "")
        : Usuario(id, nombreCompleto, "N/A"),
        nombreCompleto(nombreCompleto),
        edad(edad),
        habitacion(habitacion),
        tipoAlojamiento(tipoAlojamiento),
        lugar(lugar),
        promocion(promocion) {}

    std::string toString() const override {
        std::ostringstream ss;
        ss << "ID: " << id << std::endl;
        ss << "Nombre Completo: " << nombreCompleto << std::endl;
        ss << "Edad: " << edad << std::endl;
        ss << "Habitación: " << habitacion << std::endl;
        ss << "Tipo Alojamiento: " << tipoAlojamiento << std::endl;
        ss << "Lugar: " << lugar << std::endl;
        ss << "Promoción: " << promocion << std::endl;
        return ss.str();
    }

    std::string getNombreCompleto() const { return nombreCompleto; }
    void setNombreCompleto(const std::string& nombreCompleto) { this->nombreCompleto = nombreCompleto; }

    int getEdad() const { return edad; }
    void setEdad(int edad) { this->edad = edad; }

    int getHabitacion() const { return habitacion; }
    void setHabitacion(int habitacion) { this->habitacion = habitacion; }

    std::string getTipoAlojamiento() const { return tipoAlojamiento; }
    void setTipoAlojamiento(const std::string& tipoAlojamiento) { this->tipoAlojamiento = tipoAlojamiento; }

    std::string getLugar() const { return lugar; }
    void setLugar(const std::string& lugar) { this->lugar = lugar; }

    std::string getPromocion() const { return promocion; }
    void setPromocion(const std::string& promocion) { this->promocion = promocion; }
};

#endif
