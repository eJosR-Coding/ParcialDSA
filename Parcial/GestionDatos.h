#pragma once
#include <string>
#include "Arbol.hpp"
#include "HashTable.h"
#include<iostream>
#include<conio.h>
#include <fstream>	//Gestion de Archivo
#include <string>	//getline
#include <sstream>	//stream

using namespace std;

void imprimir(string e)
{
	cout << "" << e << endl;
}

class GestionDatos
{
private:
	ArbolBB<string, string>* arbol;
	HashTablaA ht;

	string nombre_rchivo;

public:
	GestionDatos();
	void LecturaDatosArchivo();
	void Intervalo_Artistas();
	void Generar_Arbol();
	string buscar_Codigo_Artista();
	void GenerarListaPreOrden();
	void Eliminar_Artistas();
};

GestionDatos::GestionDatos()
{
	nombre_rchivo = "TopYoutubeArtist.csv";
	arbol = new ArbolBB<string, string>(imprimir);
	ht = HashTablaA();

}

void GestionDatos::LecturaDatosArchivo()
{
	/*
	* 1_ Lee Archivo .csv
	* 2_ Imprime columnas de cada linea en consola
	*/

	ifstream archIN;
	archIN.open(nombre_rchivo, ios::in); //Apertura

	if (!archIN.is_open())
	{
		cout << "Error: No se pudo abrir el archivo !!!" << endl;
		exit(1);
	}

	string linea;
	char delimitador = '|'; //Separador de cada columna de la línea

	// Encabezado: Leemos la primera línea para descartarla, pues es el encabezado
	getline(archIN, linea);

	// Contenido: Leemos todas las líneas
	while (getline(archIN, linea))
	{
		stringstream stream(linea); // Convertir la cadena a un stream

		string col1, col2, col3, col4, col5;
		// Extraer todos los valores de esa fila [considerando 3 columans]
		getline(stream, col1, delimitador);
		getline(stream, col2, delimitador);
		getline(stream, col3, delimitador);
		getline(stream, col4, delimitador);
		getline(stream, col5, delimitador);
		arbol->insertar(col2);
		ht.insert(HashEntidad(col1, col2, col3, col4, col5));
	}

	// Cerramos Archivo
	archIN.close();
}

void GestionDatos::Generar_Arbol()
{
	arbol->imprimirArbol();
}
// función para mostrar los artistas cuyos nombres empiezan por R y S y llama a la función del arbol _Intervalo_Artistas para hacer las comparaciones
void GestionDatos::Intervalo_Artistas()
{
	arbol->Intervalo_Artistas("R", "S");
}
string GestionDatos::buscar_Codigo_Artista()
{
	arbol->Buscar();
}
void GestionDatos::GenerarListaPreOrden()
{
	arbol->preOrden();
}
void GestionDatos::Eliminar_Artistas()
{
	arbol->eliminar();
}
