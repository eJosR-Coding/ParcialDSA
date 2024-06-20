#pragma once
#ifndef __ARBOLBB_HPP__
#define __ARBOLBB_HPP__

#include <functional>
#include <string>
#include "Cliente.h"

using namespace std;

template <class T>
class ArbolBB {
    typedef function<int(T, T)> Comp; // Lambda para comparar

    Nodo<T>* raiz;
    void(*procesar)(T); // Puntero a función

    Comp comparar; // Lambda de criterio de comparación

public:
    ArbolBB(void(*otroPunteroAFuncion)(T)) {
        this->procesar = otroPunteroAFuncion;
        this->comparar = [](T a, T b)->int { return a.getNombreCompleto().compare(b.getNombreCompleto()); };
        raiz = nullptr;
    }
    Nodo<T>* getRaiz() { return raiz; }

    bool insertar(T e) {
        return _insertar(raiz, e);
    }
    void enOrden() {
        _enOrden(raiz);
    }
    void preOrden() {
        _preOrden(raiz);
    }
    void postOrden() {
        _postOrden(raiz);
    }
    int cantidad() {
        return _cantidad(raiz);
    }
    int altura() {
        return _altura(raiz);
    }
    bool buscar(T e) {
        return _buscar(raiz, e);
    }
    Nodo<T>* obtener(T e)
    {
        return _obtener(raiz, e);
    }

    bool eliminar(T e) {
        return _eliminar(raiz, e);
    }

    void imprimirArbol() {
        _imprimirArbol(raiz, "", true);
    }

    void Intervalo_Clientes(T min, T max)
    {
        _Intervalo_Clientes(raiz, min, max);
    }

private:
    bool _buscar(Nodo<T>* nodo, T e) {
        if (nodo == nullptr) return false;
        else {
            int r = comparar(nodo->elemento, e);
            if (r == 0) return true;    //si son iguales: (nodo->elemento == e)
            else if (r < 0) {    //si (nodo->elemento < e)
                return _buscar(nodo->der, e);
            }
            else {    //si (nodo->elemento > e)
                return _buscar(nodo->izq, e);
            }
        }
    }

    bool _insertar(Nodo<T>*& nodo, T e) {
        if (nodo == nullptr) {
            nodo = new Nodo<T>();
            nodo->elemento = e;
            nodo->izq = nodo->der = nullptr; // Inicializar hijos
            return true;
        }
        else {
            int r = comparar(nodo->elemento, e);
            if (r == 0) return false;    //no se acepta nodos con elemento igual
            else if (r < 0) {    //si (nodo->elemento < e)
                return _insertar(nodo->der, e);
            }
            else {    //si (nodo->elemento > e)
                return _insertar(nodo->izq, e);
            }
        }
    }

    void _enOrden(Nodo<T>* nodo) {    //Izq => Raiz => Der
        if (nodo == nullptr) return;
        _enOrden(nodo->izq);
        procesar(nodo->elemento);
        _enOrden(nodo->der);
    }

    void _preOrden(Nodo<T>* nodo) {    //Raiz => Izq => Der
        if (nodo == nullptr) return;
        procesar(nodo->elemento);
        _preOrden(nodo->izq);
        _preOrden(nodo->der);
    }

    void _postOrden(Nodo<T>* nodo) {    //Izq => Der => Raiz
        if (nodo == nullptr) return;
        _postOrden(nodo->izq);
        _postOrden(nodo->der);
        procesar(nodo->elemento);
    }

    bool _vacio() {
        return raiz == nullptr;
    }

    int _cantidad(Nodo<T>* nodo) {
        if (nodo == nullptr)
            return 0;
        else
        {
            int ci, cd;
            ci = _cantidad(nodo->izq);
            cd = _cantidad(nodo->der);
            return 1 + ci + cd;
        }
    }

    int _altura(Nodo<T>* nodo) {
        if (nodo == nullptr)
            return 0;
        else
        {
            int ai, ad;
            ai = 1 + _altura(nodo->izq);
            ad = 1 + _altura(nodo->der);
            return ai > ad ? ai : ad;
        }
    }

    bool _eliminar(Nodo<T>*& nodo, T e) {
        if (nodo == nullptr) return false;
        else {
            int r = comparar(nodo->elemento, e);
            if (r < 0) {    //si (nodo->elemento < e)
                return _eliminar(nodo->der, e);
            }
            else if (r > 0) {    //si (nodo->elemento > e)
                return _eliminar(nodo->izq, e);
            }
            else { // r==0 es porque se encontró el elemento en el arbol | si (nodo->elemento == e)
                if (nodo->der == nullptr && nodo->izq == nullptr) {    //Caso 1: Hoja
                    delete nodo;
                    nodo = nullptr;
                    return true;
                }
                else if (nodo->izq == nullptr) { //Caso 2: Izq Vacío y Der No Vacío
                    Nodo<T>* temp = nodo;
                    nodo = nodo->der;
                    delete temp;
                    return true;
                }
                else if (nodo->der == nullptr) { //Caso 3: Der Vacío e Izq No Vacío
                    Nodo<T>* temp = nodo;
                    nodo = nodo->izq;
                    delete temp;
                    return true;
                }
                else { //Caso 4: Izq y Der No Vacíos
                    Nodo<T>* aux = nodo->der; //Se establece buscar el menor elemento por la derecha
                    while (aux->izq != nullptr)
                    {
                        aux = aux->izq; //Se obtiene la hoja menor
                    }
                    nodo->elemento = aux->elemento; //Se actualiza el elemento en el nodo raiz y
                    return _eliminar(nodo->der, aux->elemento); //se envía a eliminar el elemento en el arbol por la derecha
                }
            }
        }
    }

    void _imprimirArbol(Nodo<T>* nodo, string indent, bool last)
    {
        if (nodo != nullptr) {
            cout << indent;
            if (last) {
                cout << "R----";
                indent += "   ";
            }
            else {
                cout << "L----";
                indent += "|  ";
            }
            cout << nodo->elemento.getNombreCompleto() << endl;
            _imprimirArbol(nodo->izq, indent, false);
            _imprimirArbol(nodo->der, indent, true);
        }
    }

    void _Intervalo_Clientes(Nodo<T>* nodo, T min, T max)
    {
        if (nodo == nullptr)
            return;
        else
        {
            if (comparar(min, nodo->elemento) < 0)
                _Intervalo_Clientes(nodo->izq, min, max);
            if (comparar(min, nodo->elemento) <= 0 && comparar(max, nodo->elemento) >= 0)
                cout << nodo->elemento.getNombreCompleto() << endl;
            if (comparar(max, nodo->elemento) > 0)
                _Intervalo_Clientes(nodo->der, min, max);
        }
    }
};

#endif
