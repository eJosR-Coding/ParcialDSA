#pragma once
#ifndef __NODO_ARBOL_H__
#define __NODO_ARBOL_H__

template<class T>
class NodoArbol {
public:
    T elemento;
    NodoArbol* izq;
    NodoArbol* der;

    NodoArbol(T elem, NodoArbol* i = nullptr, NodoArbol* d = nullptr) {
        elemento = elem;
        izq = i;
        der = d;
    }
};

#endif
