#pragma once
#ifndef __HASHTABLA_HPP__
#define __HASHTABLA_HPP__
#include <iostream>
#include <vector>
#include <list>
#include <string>
#include "Cliente.h"

using namespace std;

class HashTablaA {
private:
    vector<list<Cliente>> theLists;   // Tabla: vector cuyo cada elemento es una Lista de Nodos Hash(key, value)
    size_t currentSize;    // Tamaño del vector

public:
    explicit HashTablaA(size_t size = 30) : currentSize{ 0 }
    {
        theLists.resize(size);    // Resize al vector, para que tenga `size` elementos: `size` listas de Nodos Hash(key, value)
    }

    void makeEmpty()
    {
        for (auto& thisList : theLists)
            thisList.clear();
    }

    bool insert(const Cliente& x)
    {
        auto& whichList = theLists[myhash(x.getNombreCompleto())]; // Del vector, obtenemos la lista de elementos según el hash(indice) obtenido

        whichList.push_back(x); // Agregamos el nuevo elemento(key, value) a la lista del hash(indice)

        return true;
    }

    bool insert(Cliente&& x)
    {
        auto& whichList = theLists[myhash(x.getNombreCompleto())]; // Del vector, obtenemos la lista de elementos según el hash(indice) obtenido

        whichList.push_back(std::move(x)); // Agregamos el nuevo elemento(key, value) a la lista del hash(indice)

        return true;
    }

    void DispAll() {
        for (size_t i = 0; i < theLists.size(); ++i) {        // Recorremos el vector<>
            cout << "Indice " << i << ": ";
            for (const auto& it : theLists[i]) {    // Recorremos la Lista de cada indice del vector    
                cout << it.getNombreCompleto() << ",";

            }
            cout << endl;
        }
    }

    void buscar(const string& key)
    {
        size_t pos = myhash(key);

        cout << "Buscando en el indice: " << pos << endl;
        for (const auto& it : theLists[pos]) {    // Recorremos la Lista de cada indice del vector    
            if (it.getNombreCompleto() == key) {
                cout << "Cliente encontrado: "
                    << it.getNombreCompleto()
                    << ", Edad: " << it.getEdad()
                    << ", Habitacion: " << it.getHabitacion()
                    << ", Tipo Alojamiento: " << it.getTipoAlojamiento()
                    << ", Lugar: " << it.getLugar()
                    << ", Promocion: " << it.getPromocion()
                    << ",Latitud"<<it.getLatitud()
                    << ",Longitud" << it.getLongitud() << endl;
                return;
            }
        }
        cout << "Cliente no encontrado" << endl;
    }

private:
    size_t myhash(const string& key) const {
        size_t hashVal = 0;
        for (char ch : key) {
            hashVal = 37 * hashVal + ch; // Simple hash function
        }
        return hashVal % theLists.size();    // Retornará el indice obtenido para la Tabla HASH
    }
};

#endif // !__HASHTABLA_HPP__
