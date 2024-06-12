#pragma once
#ifndef COLA_H
#define COLA_H

#include "Nodo.h"
#include "Dependencies.h"

template<class T>
class Cola {
private:
    Nodo<T>* frente;
    Nodo<T>* final;
    int longitud;

public:
    Cola() : frente(NULL), final(NULL), longitud(0) {}

    ~Cola() {
        vaciar();
    }

    void encolar(T valor) {
        Nodo<T>* nuevo = new Nodo<T>(valor);
        if (final == NULL) {
            frente = final = nuevo;
        }
        else {
            final->siguiente = nuevo;
            final = nuevo;
        }
        longitud++;
    }

    T desencolar() {
        if (frente == NULL) {
            throw std::runtime_error("La cola está vacía");
        }
        Nodo<T>* temp = frente;
        T valor = frente->valor;
        frente = frente->siguiente;
        if (frente == NULL) {
            final = NULL;
        }
        delete temp;
        longitud--;
        return valor;
    }

    T obtenerFrente() const {
        if (frente == NULL) {
            throw std::runtime_error("La cola está vacía");
        }
        return frente->valor;
    }

    int getTamano() const {
        return longitud;
    }

    void vaciar() {
        while (frente != NULL) {
            Nodo<T>* temp = frente;
            frente = frente->siguiente;
            delete temp->valor; // Asumiendo que T es un puntero a objeto
            delete temp;
        }
        final = NULL;
        longitud = 0;
    }

    bool estaVacia() const {
        return frente == NULL;
    }
};

#endif
