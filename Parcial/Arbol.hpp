#pragma once
#ifndef __ARBOLBB_HPP__
#define __ARBOLBB_HPP__

#include <functional>
#include <string>

using namespace std;
using namespace System;

template <class T>
class Nodo {
public:
	T elemento;
	Nodo* izq;
	Nodo* der;
	//Nodo* padre;
};

template <class T, class S>
class ArbolBB {
	typedef function<int(S, S)> Comp; //Lambda

	Nodo<T>* raiz;
	void(*procesar)(T); //Puntero a funcion

	Comp comparar; // lambda de criterio de comparación



public:
	ArbolBB(void(*otroPunteroAFuncion)(T)) {
		this->procesar = otroPunteroAFuncion;
		this->comparar = [](string a, string b)->int {return a.compare(b); };
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
	bool Buscar(T e) {
		return _buscar(raiz, e);
	}
	Nodo<T>* Obtener(T e)
	{
		return _obtener(raiz, e);
	}

	// Propuesto 1: Elaborar un algoritmo para obtener el nodo cuyo valor es el mínimo del árbol.


	// Propuesto 2: Elaborar un algoritmo para obtener el nodo cuyo valor es el  máximo del árbol.

	bool Eliminar(T e) {
		return _eliminar(raiz, e);
	}

	void imprimirArbol() {
		_imprimirArbol(raiz, "", true);
	}
	void Intervalo_Artistas(S min, S max)
	{
		_Intervalo_Artistas(raiz, min, max);
	}

private:
	bool _buscar(Nodo<T>* nodo, T e) {
		if (nodo == nullptr) return false;
		else {
			int r = comparar(nodo->elemento, e);
			if (r == 0) return true;	//si son iguales: (nodo->elemento == e)
			else if (r < 0) {	//si (nodo->elemento < e)
				return _buscar(nodo->der, e);
			}
			else {	//si (nodo->elemento > e)
				return _buscar(nodo->izq, e);
			}
		}
	}

	bool _insertar(Nodo<T>*& nodo, T e) {
		if (nodo == nullptr) {
			nodo = new Nodo<T>();
			nodo->elemento = e;
			return true;
		}
		else {
			int r = comparar(nodo->elemento, e);
			if (r == 0) return false;	//no se acepta nodos con elemento igual
			else if (r < 0) {	//si (nodo->elemento < e)
				return _insertar(nodo->der, e);
			}
			else {	//si (nodo->elemento > e)
				return _insertar(nodo->izq, e);
			}
		}
	}
	void _enOrden(Nodo<T>* nodo) {	//Izq => Raiz => Der
		if (nodo == nullptr) return;
		_enOrden(nodo->izq);
		procesar(nodo->elemento);
		_enOrden(nodo->der);
	}

	void _preOrden(Nodo<T>* nodo) {	//Raiz => Izq => Der
		if (nodo == nullptr) return;
		procesar(nodo->elemento);
		_preOrden(nodo->izq);
		_preOrden(nodo->der);
	}

	void _postOrden(Nodo<T>* nodo) {	//Izq => Der => Raiz
		if (nodo == nullptr) return;
		_postOrden(nodo->izq);
		_postOrden(nodo->der);
		procesar(nodo->elemento);
	}

	bool _vacio() {
		return raiz == nullptr;
	}
	int _cantidad(Nodo<T>* nodo) {
		//La cantidad de nodos del árbol es:
		//	0 si es vacío
		//	1 + la cantidad de nodos por la izquierda + la cantidad de nodos por la derecha

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
		//La altura del árbol es:
		//	0 si es vacío
		//	la mayor de las alturas por la izquierda y por la derecha, las cuáles son 0 si son vacías ó 1 + la altura por la izq(o der) en caso contrario

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

	// Propuesto 1: Elaborar un algoritmo para obtener el nodo cuyo valor es el mínimo del árbol. 


	// Propuesto 2: Elaborar un algoritmo para obtener el nodo cuyo valor es el  máximo del árbol.


	bool _eliminar(Nodo<T>*& nodo, T e) {
		if (nodo == nullptr) return false;
		//Buscamos el Nodo que contiene el elemento e
		else {
			int r = comparar(nodo->elemento, e);
			if (r < 0) {	//si (nodo->elemento < e)
				return _eliminar(nodo->der, e);
			}
			else if (r > 0) {	//si (nodo->elemento > e)
				return _eliminar(nodo->izq, e);
			}

			//Analizamos el escenario en el que se encuentra el Nodo a eliminar
			else { // r==0 es porque se encontró el elemento en el arbol | si (nodo->elemento == e)
				if (nodo->der == nullptr && nodo->izq == nullptr) {	//Caso 1: Hoja
					nodo = nullptr;
					delete nodo;	//*REZC: Sí se puede hacer delete nullptr, porque nullptr es un puntero
					return true;
				}
				else if (nodo->izq == nullptr) { //Caso 2: Izq Vacío y Der No Vacío
					//aux = nodo; //8
					nodo = nodo->der;
					//delete aux;
					return true;
				}
				else if (nodo->der == nullptr) { //Caso 3: Der Vacío e Izq No Vacío
					nodo = nodo->izq;
					return true;
				}
				else { //Caso 4: Izq y Der No Vacíos
					Nodo<T>* aux = nodo->der; //Se establece buscar el menor elemento por la derecha [PPT: Nodo es la Raiz, aux es 35]
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


	// --------------------------------------------------------------------------
	// Propuesto 3 [REZC]: Elaborar un algoritmo para obtener el nodo predecesor dado un nodo seleccionado del árbol.


	// Propuesto 4 [REZC]: Elaborar un algoritmo para obtener el nodo sucesor dado un nodo seleccionado del árbol.


	// Propuesto 5 [REZC]: Elaborar un algoritmo para devolver el número de nodos por nivel del árbol.


	//Adicional [REZC]: Graficar Arbol


	// --------------------------------------------------------------------------

	// [REZC] Imprimir Arbol
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
			cout << nodo->elemento << endl;
			_imprimirArbol(nodo->izq, indent, false);
			_imprimirArbol(nodo->der, indent, true);
		}
	}

	bool _Intervalo_Artistas(Nodo<T>* nodo, T min, T max)
	{
		if (nodo == nullptr)
			return false;
		else
		{
			if (comparar(min, nodo->elemento) < 0)
				_Intervalo_Artistas(nodo->izq, min, max);
			if (min <= nodo->elemento && nodo->elemento <= max)
				cout << nodo->elemento << "n";
			if (comparar(max, nodo->elemento) < 0)
				_Intervalo_Artistas(nodo->der, min, max);
		}

	}
};

#endif
