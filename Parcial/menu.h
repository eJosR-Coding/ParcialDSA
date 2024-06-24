#include "pch.h"
#include <iostream>
#include <conio.h>
#include <windows.h>

using namespace std;

// Función para mover el cursor a una posición específica
void gotoxy(int x, int y) {
    COORD coord;
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

// Función para establecer el color de la consola
void color(int color) {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}

// Función principal para mostrar y navegar el menú
void menuSelector() {
    bool repite = true;
    int opcion = 1;
    const int totalOpciones = 19;

    // Configuración inicial de colores
    system("color 07"); // Fondo negro, texto blanco

    do {
        system("cls");
        gotoxy(10, 2);
        color(11); // Texto celeste
        cout << " ,-----.,--.    ,-----. ,--. ,--.,------.  ,-----.  ,------.,------.   ,---.  " << endl;
        gotoxy(10, 3);
        cout << "'  .--./|  |   '  .-.  '|  | |  ||  .-.  \\ |  |) /_ |  .---'|  .-.  \\ '   .-' " << endl;
        gotoxy(10, 4);
        cout << "|  |    |  |   |  | |  ||  | |  ||  |  \\  :|  .-.  \\|  --, |  |  \\  :.  `-. " << endl;
        gotoxy(10, 5);
        cout << "'  '--'\\|  '--.'  '-'  ''  '-'  '|  '--'  /|  '--' /|  `---.|  '--'  /.-'    |" << endl;
        gotoxy(10, 6);
        cout << " -----'-----' -----'  `-----' `-------' `------' `------'-------' `-----' " << endl;
        gotoxy(10, 7);
        cout << "===============================================================================" << endl;

        for (int i = 1; i <= totalOpciones; ++i) {
            gotoxy(20, 8 + i);
            if (opcion == i) {
                color(12); // Texto rojo para la opción seleccionada
            }
            else {
                color(11); // Texto celeste para las demás opciones
            }
            cout << (opcion == i ? "> " : "  ") << i << ". ";
            switch (i) {
            case 1: cout << "Registrar Cliente"; break;
            case 2: cout << "Atender clientes de la cola"; break;
            case 3: cout << "Registrar Empleado"; break;
            case 4: cout << "Mostrar Usuarios"; break;
            case 5: cout << "Mostrar Reservas hasta la fecha"; break;
            case 6: cout << "Reseñas"; break;
            case 7: cout << "Mostrar primer cliente registrado"; break;
            case 8: cout << "Calcular suma de edades de los clientes"; break;
            case 9: cout << "Buscar Cliente en Árbol"; break;
            case 10: cout << "Buscar Cliente en HashTable"; break;
            case 11: cout << "Mostrar Clientes Ordenados"; break;
            case 12: cout << "Mostrar Clientes por Rango de Nombres"; break;
            case 13: cout << "Contar Clientes en Árbol"; break;
            case 14: cout << "Eliminar Cliente del Árbol y HashTable"; break;
            case 15: cout << "Mostrar Todos los Clientes/Empleados (HashTable)"; break;
            case 16: cout << "Leer Datos desde Archivo"; break;
            case 17: cout << "Generar Conexiones Aleatorias"; break;
            case 18: cout << "Mostrar Conexiones entre Clientes"; break;
            case 19: cout << "Salir"; break;
            }
            cout << endl;
        }

        char tecla = _getch();
        switch (tecla) {
        case 'w':
        case 'W':
        case 72: // Flecha hacia arriba
            opcion--;
            if (opcion < 1) opcion = totalOpciones;
            break;
        case 's':
        case 'S':
        case 80: // Flecha hacia abajo
            opcion++;
            if (opcion > totalOpciones) opcion = 1;
            break;
        case 13: // Tecla Enter
            switch (opcion) {
            case 1:
                cout << "Elegiste Registrar Cliente" << endl;
                break;
            case 2:
                cout << "Elegiste Atender clientes de la cola" << endl;
                break;
            case 3:
                cout << "Elegiste Registrar Empleado" << endl;
                break;
            case 4:
                cout << "Elegiste Mostrar Usuarios" << endl;
                break;
            case 5:
                cout << "Elegiste Mostrar Reservas hasta la fecha" << endl;
                break;
            case 6:
                cout << "Elegiste Reseñas" << endl;
                break;
            case 7:
                cout << "Elegiste Mostrar primer cliente registrado" << endl;
                break;
            case 8:
                cout << "Elegiste Calcular suma de edades de los clientes" << endl;
                break;
            case 9:
                cout << "Elegiste Buscar Cliente en Árbol" << endl;
                break;
            case 10:
                cout << "Elegiste Buscar Cliente en HashTable" << endl;
                break;
            case 11:
                cout << "Elegiste Mostrar Clientes Ordenados" << endl;
                break;
            case 12:
                cout << "Elegiste Mostrar Clientes por Rango de Nombres" << endl;
                break;
            case 13:
                cout << "Elegiste Contar Clientes en Árbol" << endl;
                break;
            case 14:
                cout << "Elegiste Eliminar Cliente del Árbol y HashTable" << endl;
                break;
            case 15:
                cout << "Elegiste Mostrar Todos los Clientes/Empleados (HashTable)" << endl;
                break;
            case 16:
                cout << "Elegiste Leer Datos desde Archivo" << endl;
                break;
            case 17:
                cout << "Elegiste Generar Conexiones Aleatorias" << endl;
                break;
            case 18:
                cout << "Elegiste Mostrar Conexiones entre Clientes" << endl;
                break;
            case 19:
                repite = false;
                break;
            default:
                cout << "Opcion invalida. Introduce un numero valido." << endl;
                break;
            }
            if (opcion != 19) {
                cout << "Presiona cualquier tecla para continuar..." << endl;
                _getch();
            }
            break;
        }
    } while (repite);
}