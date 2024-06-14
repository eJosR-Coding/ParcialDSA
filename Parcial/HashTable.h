#pragma once
#ifndef __HASHTABLA_HPP__
#define __HASHTABLA_HPP__
#include <iostream>
#include <vector>
#include <list>
#include <string>
#include "HashEntidad.hpp"

using namespace std;

//HASH TABLE LINEAL ES DECIR TABLA HASH CON UN TMAÑO PREDETERMINADO Y USA LISTAS PARA LAS COLISIONES

class HashTablaA {
private:
	vector<list<HashEntidad>> theLists;   // Tabla: vector cuyo cada elemento es una Lista de Nodos Hash(key, value)
	int  currentSize;	//Tamaño del vector

public:
	explicit HashTablaA(int size = 101) : currentSize{ 0 }
	{
		theLists.resize(101);	//Resize al vector, para que tenga 101 elementos: 101 listas de Nodos Hash(key, value)
	}

	void makeEmpty()
	{
		for (auto& thisList : theLists)
			thisList.clear();
	}

	bool insert(HashEntidad&& x)
	{
		auto& whichList = theLists[myhash(x.getKey())]; //Del vector, obtenemos la lista de elementos según el hash(indice) obtenido

		whichList.push_back(x); //Agregamos el nuevo elemento(key, value) a la lista del hash(indice)

		return true;
	}

	void DispAll() {
		int pos = 0;
		for (auto& thisList : theLists) {		// Recorremos el vector<>
			cout << "Key: " + to_string(pos) << " | ";
			for (auto& it : theLists[pos]) {	// Recorremos la Lista de cada indice del vector	
				cout << it.getKey() << ",";		// Imprime key
				//cout << "(" << it.getKey() << ", " << it.getValue() << "); ";	// Imprime (key,value)
			}
			cout << endl;
			pos++;
		}
	}

	// esta es la función buscar en base al codigo que es la key
	void buscar(string key)
	{
		int pos = 0;
		pos = myhash(key);

		//for (auto& thisList : theLists) {		// Recorremos el vector<>
		cout << "Key: " + to_string(pos) << " | ";
		for (auto& it : theLists[pos]) {	// Recorremos la Lista de cada indice del vector	
			if (it.getKey() == key)
				//cout << it.getKey() << ",";		// Imprime key
				cout << "(" << it.getKey()
				<< ", " << it.getArtist()
				<< ", " << it.getTotalViews()
				<< ", " << it.getAvg() << "); ";	// Imprime (key,value)
		}
		cout << endl;
		//pos++;
	//}
	}
private:

	// ...:: FUNCION HASH ::...

	size_t myhash(string key) const {
		size_t hashVal = 0;			//Funcion de Dispersion: k (the same key)
		hashVal %= theLists.size();		//Mapa de Compresion: Aritmetica Modular: F(k) = |k| mod N
		//hashVal = 10; //Prueba para verificar como se almacenan los elementos si obtienen el mismo hash
		return(hashVal);	//retornará el indice obtenido para la Tabla HASH
	}
};

#endif // !__HASHTABLA_HPP__
