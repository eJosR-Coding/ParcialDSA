#pragma once
#ifndef PROMOCION_H
#define PROMOCION_H

#include "Dependencies.h"

class Promocion {
private:
    int id;
    std::string descripcion;
    std::string promocion;
public:
    static float promociónINTERBANK(float total) {
        return static_cast<float>(total * 0.6);
    }

    static float promociónBCP(float total) {
        return static_cast<float>(total * 0.8); // Se aplica un descuento del 20%
    }
};

#endif // PROMOCION_H
