#pragma once
#ifndef LISTA_H
#define LISTA_H

#include "Nodo.h"
#include "Dependencies.h"
#include "Cliente.h"
#include <stdexcept>
#include <iostream>

template<class T>
class Lista {
private:
    Nodo<T>* inicio;
    Nodo<T>* fin;
    int longitud;

    static Nodo<T>* particionar(Nodo<T>* inicio, Nodo<T>* fin) {
        T pivot = fin->valor;
        Nodo<T>* i = inicio->anterior;

        for (Nodo<T>* j = inicio; j != fin; j = j->siguiente) {
            if (*(j->valor) <= *pivot) {
                i = (i == nullptr) ? inicio : i->siguiente;
                std::swap(i->valor, j->valor);
            }
        }
        i = (i == nullptr) ? inicio : i->siguiente;
        std::swap(i->valor, fin->valor);
        return i;
    }

    static Nodo<T>* merge(Nodo<T>* a, Nodo<T>* b) {
        Nodo<T>* result = nullptr;

        if (a == nullptr) {
            return b;
        }
        else if (b == nullptr) {
            return a;
        }

        if (*(a->valor) <= *(b->valor)) {
            result = a;
            result->siguiente = merge(a->siguiente, b);
        }
        else {
            result = b;
            result->siguiente = merge(a, b->siguiente);
        }
        return result;
    }

    static void split(Nodo<T>* source, Nodo<T>** frontRef, Nodo<T>** backRef) {
        if (source == nullptr || source->siguiente == nullptr) {
            *frontRef = source;
            *backRef = nullptr;
            return;
        }

        Nodo<T>* fast = source->siguiente;
        Nodo<T>* slow = source;

        while (fast != nullptr) {
            fast = fast->siguiente;
            if (fast != nullptr) {
                slow = slow->siguiente;
                fast = fast->siguiente;
            }
        }

        *frontRef = source;
        *backRef = slow->siguiente;
        slow->siguiente = nullptr;
    }

    static void heapify(Nodo<T>* nodo, int n, int i) {
        int largest = i;
        int left = 2 * i + 1;
        int right = 2 * i + 2;

        Nodo<T>* largestNode = nodoEnPosicion(nodo, largest);
        Nodo<T>* leftNode = (left < n) ? nodoEnPosicion(nodo, left) : nullptr;
        Nodo<T>* rightNode = (right < n) ? nodoEnPosicion(nodo, right) : nullptr;

        if (leftNode != nullptr && *(leftNode->valor) > *(largestNode->valor)) {
            largest = left;
            largestNode = leftNode;
        }

        if (rightNode != nullptr && *(rightNode->valor) > *(largestNode->valor)) {
            largest = right;
            largestNode = rightNode;
        }

        if (largest != i) {
            Nodo<T>* iNode = nodoEnPosicion(nodo, i);
            std::swap(iNode->valor, largestNode->valor);
            heapify(nodo, n, largest);
        }
    }

    static Nodo<T>* nodoEnPosicion(Nodo<T>* inicio, int index) {
        Nodo<T>* temp = inicio;
        for (int i = 0; i < index; i++) {
            if (temp == nullptr) { // Añadir verificación
                throw std::out_of_range("Índice fuera de los límites de la lista");
            }
            temp = temp->siguiente;
        }
        return temp;
    }

    static Nodo<T>* obtenerMax(Nodo<T>* inicio) {
        Nodo<T>* maxNode = inicio;
        Nodo<T>* temp = inicio->siguiente;
        while (temp != nullptr) {
            if (*(temp->valor) > *(maxNode->valor)) {
                maxNode = temp;
            }
            temp = temp->siguiente;
        }
        return maxNode;
    }

    void quickSort(Nodo<T>* inicio, Nodo<T>* fin) {
        if (fin != nullptr && inicio != fin && inicio != fin->siguiente) {
            Nodo<T>* p = particionar(inicio, fin);
            quickSort(inicio, p->anterior);
            quickSort(p->siguiente, fin);
        }
    }

    void mergeSort(Nodo<T>** headRef) {
        Nodo<T>* head = *headRef;
        if ((head == nullptr) || (head->siguiente == nullptr)) {
            return;
        }

        Nodo<T>* a;
        Nodo<T>* b;
        split(head, &a, &b);

        mergeSort(&a);
        mergeSort(&b);

        *headRef = merge(a, b);
    }

    void heapSort(Nodo<T>*& inicio, int longitud) {
        for (int i = longitud / 2 - 1; i >= 0; i--) {
            heapify(inicio, longitud, i);
        }

        for (int i = longitud - 1; i > 0; i--) {
            Nodo<T>* rootNode = nodoEnPosicion(inicio, 0);
            Nodo<T>* endNode = nodoEnPosicion(inicio, i);
            std::swap(rootNode->valor, endNode->valor);
            heapify(inicio, i, 0);
        }
    }

public:
    Lista() : inicio(nullptr), fin(nullptr), longitud(0) {}
    ~Lista() {
        vaciar();
    }

    Nodo<T>* obtenerUltimoNodo() const {
        return fin;
    }

    void insertarInicio(T valor) {
        Nodo<T>* nuevo = new Nodo<T>(valor, nullptr, inicio);
        if (inicio != nullptr) {
            inicio->anterior = nuevo;
        }
        if (inicio == nullptr) {
            fin = nuevo;
        }
        inicio = nuevo;
        longitud++;
    }

    void insertarFinal(T valor) {
        if (inicio == nullptr) {
            insertarInicio(valor);
        }
        else {
            Nodo<T>* nuevo = new Nodo<T>(valor, fin, nullptr);
            fin->siguiente = nuevo;
            fin = nuevo;
            longitud++;
        }
    }

    void push(T valor) {
        insertarFinal(valor);
    }

    T pop() {
        if (longitud == 0) {
            throw std::runtime_error("La lista está vacía");
        }

        if (longitud == 1) {
            T valor = inicio->valor;
            delete inicio;
            inicio = nullptr;
            fin = nullptr;
            longitud--;
            return valor;
        }

        T valor = fin->valor;
        Nodo<T>* penultimo = fin->anterior;
        delete fin;
        fin = penultimo;
        fin->siguiente = nullptr;
        longitud--;

        return valor;
    }

    T obtenerUltimoSinEliminar() const {
        if (longitud == 0) {
            throw std::runtime_error("La lista está vacía");
        }

        return fin->valor;
    }

    int getTamano() const {
        return longitud;
    }

    T obtener(int indice) const {
        if (indice < 0 || indice >= longitud) {
            throw std::out_of_range("Índice fuera de rango");
        }
        Nodo<T>* actual = inicio;
        for (int i = 0; i < indice; ++i) {
            actual = actual->siguiente;
        }
        return actual->valor;
    }

    void mostrar() const {
        Nodo<T>* actual = inicio;
        while (actual != nullptr) {
            std::cout << actual->valor->toString() << " -> ";
            actual = actual->siguiente;
        }
        std::cout << "NULL\n";
    }

    void vaciar() {
        Nodo<T>* actual = inicio;
        while (actual != nullptr) {
            Nodo<T>* temp = actual;
            actual = actual->siguiente;
            delete temp->valor;  // Asumiendo que T es un puntero a objeto
            delete temp;
        }
        inicio = nullptr;
        fin = nullptr;
        longitud = 0;
    }

    Nodo<T>* getInicio() const {
        return inicio;
    }

    void ordenarByIntercambio() {
        Nodo<T>* nodo_i = inicio;
        while (nodo_i != nullptr) {
            Nodo<T>* nodo_k = nodo_i->siguiente;
            while (nodo_k != nullptr) {
                if (nodo_i->valor != nullptr && nodo_k->valor != nullptr) {
                    Usuario* usuario_i = dynamic_cast<Usuario*>(nodo_i->valor);
                    Usuario* usuario_k = dynamic_cast<Usuario*>(nodo_k->valor);
                    if (usuario_i && usuario_k && usuario_i->getNombre() > usuario_k->getNombre()) {
                        T temp = nodo_i->valor;
                        nodo_i->valor = nodo_k->valor;
                        nodo_k->valor = temp;
                    }
                }
                nodo_k = nodo_k->siguiente;
            }
            nodo_i = nodo_i->siguiente;
        }
    }

    void ordenarByQuickSort() {
        quickSort(inicio, obtenerUltimoNodo());
    }

    void ordenarByMergeSort() {
        mergeSort(&inicio);
    }

    void ordenarByHeapSort() {
        heapSort(inicio, longitud);
    }
};

#endif
