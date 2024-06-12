#pragma once
#ifndef PROMOCION_H
#define PROMOCION_H

#include "Dependencies.h"

class Promocion {
private:
    int id;
    string descripcion;
    string promocion;
public:
    static float promoci�nINTERBANK(float total) {
        return total * 0.6;
    }

    static float promoci�nBCP(float total) {
        return total * 0.8; // Se aplica un descuento del 20%
    }
};

#endif