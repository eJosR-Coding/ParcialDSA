#ifndef __NODO_H__
#define __NODO_H__

template<class T>
class Nodo {
public:
    T valor;
    Nodo<T>* anterior;
    Nodo<T>* siguiente;

public:
    Nodo(T v, Nodo<T>* ant = nullptr, Nodo<T>* sig = nullptr) {
        valor = v;
        anterior = ant;
        siguiente = sig;
    }
};

#endif
