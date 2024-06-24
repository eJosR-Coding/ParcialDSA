#include "pch.h"
#include "Lista.h"
#include "Cliente.h"
#include "Invetario.h"
#include "Empleado.h"
#include "Promocion.h"
#include "ServerStatus.h"
#include "Reservacion.h"
#include "Administrador.h"
#include "Pago.h"
#include "Resena.h"
#include "Cola.h"
#include "Arbol.hpp"
#include "HashTable.h"
#include "GestionDatos.h"
#include "Grafos.hpp"
#include <cstdlib>
#include <ctime>
#include "menu.h"
#include <conio.h>
#include <windows.h>
using namespace System;
using namespace std;




void AnadirReviewsmain(Nodo<Cliente*>* nodoCliente, Lista<Resena*>& listaReviews) {
    if (nodoCliente == nullptr) {
        return;
    }

    Usuario* usuario = nodoCliente->valor;
    Cliente* cliente = dynamic_cast<Cliente*>(usuario);

    if (cliente != nullptr) {
        string nombre = cliente->getNombreCompleto();
        int habitacion = cliente->getHabitacion();
        int rating = rand() % 10 + 1;
        Resena* nuevaReview = new Resena(listaReviews.getTamano() + 1, nombre, "Reseña sobre la habitación: " + std::to_string(habitacion), rating);
        listaReviews.insertarFinal(nuevaReview);
    }

    AnadirReviewsmain(nodoCliente->siguiente, listaReviews);
}
int sumaEdadesRecursiva(Nodo<Usuario*>* nodoCliente) {
    if (nodoCliente == nullptr) {
        return 0;
    }

    Cliente* cliente = dynamic_cast<Cliente*>(nodoCliente->valor);
    if (cliente != nullptr) {
        return cliente->getEdad() + sumaEdadesRecursiva(nodoCliente->siguiente);
    }
    else {
        return sumaEdadesRecursiva(nodoCliente->siguiente);
    }
}

int restaEdadesLambda(Nodo<Usuario*>* nodoCliente) {
    int totalResta = 0;

    // Lambda que realiza la resta de las edades
    auto restaLambda = [&totalResta](Cliente* cliente) {
        if (cliente != nullptr) {
            totalResta -= cliente->getEdad();
        }
    };

    // Iteramos sobre la lista de nodos
    while (nodoCliente != nullptr) {
        Cliente* cliente = dynamic_cast<Cliente*>(nodoCliente->valor);
        restaLambda(cliente);
        nodoCliente = nodoCliente->siguiente;
    }

    return totalResta;
}

void generarFactura(const Cliente& cliente, const Inventario& inventario, int facturaId) {
    cout << "\n*Factura*\n";
    cout << "Cliente: " << cliente.getNombreCompleto() << endl;
    cout << "Habitación: " << cliente.getHabitacion() << endl;
    cout << "Tipo Alojamiento: " << cliente.getTipoAlojamiento() << endl;
    cout << "Lugar: " << cliente.getLugar() << endl;
    cout << "Promoción: " << cliente.getPromocion() << endl;

    double total = 0;

    if (cliente.getTipoAlojamiento() == "Departamento") {
        total = 25.0;
    }
    else if (cliente.getTipoAlojamiento() == "Casa de playa") {
        total = 50.0;
    }
    else if (cliente.getTipoAlojamiento() == "Cabaña") {
        total = 75.0;
    }
    else {
        cout << "Tipo de alojamiento no reconocido.\n";
        return;
    }

    double descuentoTotal = 0;
    string promocion = cliente.getPromocion();
    if (promocion == "Interbank") {
        descuentoTotal += total * 0.1;
    }
    else if (promocion == "BCP") {
        descuentoTotal += total * 0.15;
    }

    if (cliente.getTipoAlojamiento() == "Departamento") {
        descuentoTotal += 2.5;
    }
    else if (cliente.getTipoAlojamiento() == "Casa de playa") {
        descuentoTotal += 5.0;
    }
    else if (cliente.getTipoAlojamiento() == "Cabaña") {
        descuentoTotal += 7.5;
    }

    total -= descuentoTotal;

    // Generar aleatoriamente si desea añadir jabón, champú y toalla
    bool deseaExtras = rand() % 2;
    if (deseaExtras) {
        total += 15;
    }

    cout << "Precio Alojamiento: $" << total << endl;
    cout << "Total: $" << total << endl;

    // Generar aleatoriamente si desea realizar el pago ahora
    bool deseaPagar = rand() % 2;
    if (deseaPagar) {
        int opcionMetodoPago = rand() % 3 + 1; // Generar un número entre 1 y 3

        string metodoPago;
        switch (opcionMetodoPago) {
        case 1: metodoPago = "Efectivo"; break;
        case 2: metodoPago = "Tarjeta"; break;
        case 3: metodoPago = "Transferencia"; break;
        default: metodoPago = "Desconocido";
        }

        Pago nuevoPago(facturaId, facturaId, total, metodoPago);
        nuevoPago.confirmarPago();
    }
}

void buscarClienteArbol(ArbolBB<Cliente>& arbol) {
    string nombre;
    cout << "Ingrese nombre completo del cliente para buscar: ";
    cin.ignore();
    getline(cin, nombre);

    Cliente cliente(0, nombre, 0, 0, "", "", "");
    if (arbol.buscar(cliente)) {
        cout << "Cliente encontrado en el árbol.\n";
    }
    else {
        cout << "Cliente no encontrado en el árbol.\n";
    }
}

void buscarClienteHashTable(HashTablaA& tabla) {
    string nombre;
    cout << "Ingrese nombre completo del cliente para buscar: ";
    cin.ignore();
    getline(cin, nombre);

    tabla.buscar(nombre);
}

void mostrarClientesOrdenados(ArbolBB<Cliente>& arbol) {
    cout << "Clientes ordenados alfabeticamente:\n";
    arbol.enOrden();
}

void mostrarClientesPorRango(ArbolBB<Cliente>& arbol) {
    string min, max;
    cout << "Ingrese nombre mínimo del rango: ";
    cin.ignore();
    getline(cin, min);
    cout << "Ingrese nombre máximo del rango: ";
    getline(cin, max);

    Cliente clienteMin(0, min, 0, 0, "", "", "");
    Cliente clienteMax(0, max, 0, 0, 0, "", "");
    cout << "Clientes en el rango [" << min << " - " << max << "]:\n";
    arbol.Intervalo_Clientes(clienteMin, clienteMax);
}

void contarClientesArbol(ArbolBB<Cliente>& arbol) {
    int cantidad = arbol.cantidad();
    cout << "Cantidad de clientes registrados en el árbol: " << cantidad << "\n";
}

void eliminarClienteArbolYHash(ArbolBB<Cliente>& arbol, HashTablaA& tabla) {
    string nombre;
    cout << "Ingrese nombre completo del cliente para eliminar: ";
    cin.ignore();
    getline(cin, nombre);

    Cliente cliente(0, nombre, 0, 0, "", "", "");
    if (arbol.eliminar(cliente)) {
        cout << "Cliente eliminado del árbol con éxito.\n";
    }
    else {
        cout << "Cliente no encontrado en el árbol.\n";
    }
}

void registrarCliente(Lista<Usuario*>& listaUsuarios, Lista<Reservacion*>& listaReservaciones, Lista<Resena*>& listaReviews, int& id) {
    system("cls");
    cout << "\n*Registro de Clientes Aleatorios*\n";

    vector<string> nombres = { "Ana Rodriguez", "Carlos Perez", "Maria Lopez", "Jose Martinez", "Lucia Fernandez",
                              "Jorge Suarez", "Sofia Gonzalez", "Luis Ramirez", "Camila Torres", "Miguel Ruiz",
                              "Elena Gutierrez", "Pedro Vasquez", "Laura Rojas" };
    vector<int> edades = { 28, 34, 45, 50, 37, 32, 27, 42, 29, 38, 31, 47, 26 };
    vector<string> habitaciones = { "205", "101", "303", "402", "201", "104", "204", "501", "305", "103", "203", "502", "105" };
    vector<string> tiposAlojamiento = { "Casa de playa", "Departamento", "Casa de playa", "Departamento", "Casa de playa",
                                       "Departamento", "Casa de playa", "Departamento", "Casa de playa", "Departamento",
                                       "Casa de playa", "Departamento", "Casa de playa" };
    vector<string> lugares = { "Casa Blanca", "El Refugio", "La Morada", "Vista Alegre", "La Colina",
                              "El Mirador", "Jardines del Sol", "Los Pinos", "La Alameda", "El Bosque",
                              "Las Flores", "Rincón del Cielo", "La Cascada" };
    vector<string> promociones = { "Interbank", "BCP", "Interbank", "BCP", "Interbank",
                                  "BCP", "Interbank", "BCP", "Interbank", "BCP",
                                  "Interbank", "BCP", "Interbank" };

    srand(time(0));  // Inicializa la semilla para números aleatorios

    int numClientes;
    cout << "Ingrese el número de clientes a registrar: ";
    cin >> numClientes;

    for (int i = 0; i < numClientes; i++) {
        int idx = rand() % nombres.size(); // Seleccionar un índice aleatorio

        string nombreCompleto = nombres[idx];
        int edad = edades[idx];
        string habitacion = habitaciones[idx];
        string tipoAlojamiento = tiposAlojamiento[idx];
        string lugar = lugares[idx];
        string promocion = promociones[idx];

        Cliente* nuevoCliente = new Cliente(id++, nombreCompleto, edad, std::stoi(habitacion), tipoAlojamiento, lugar, promocion);
        listaUsuarios.insertarFinal(nuevoCliente);

        cout << "Cliente registrado con éxito.\n";

        // Aquí se asume que generarFactura y AnadirReviewsmain son funciones válidas que están definidas y funcionales en tu proyecto
        // Ajusta esta parte según cómo estén definidas y cómo quieres que funcionen

        // generarFactura(*nuevoCliente, Inventario(), id);  // Comentado temporalmente ya que Inventario no está definido aquí
        // Reservacion* nuevaReservacion = new Reservacion(nombreCompleto, habitacion);
        // listaReservaciones.insertarFinal(nuevaReservacion);
        // AnadirReviewsmain(listaUsuarios.getInicio(), listaReviews);

        cout << "Reservación creada con éxito para " << nuevoCliente->getNombreCompleto() << ".\n";
    }
}

void registrarClientePrescencial(Cola<Usuario*>& colaUsuarios, int& id) {
    system("cls");
    cout << "\n*Registro de Clientes Aleatorios en Cola*\n";

    vector<string> nombres = { "Ana Rodriguez", "Carlos Perez", "Maria Lopez", "Jose Martinez", "Lucia Fernandez",
                              "Jorge Suarez", "Sofia Gonzalez", "Luis Ramirez", "Camila Torres", "Miguel Ruiz",
                              "Elena Gutierrez", "Pedro Vasquez", "Laura Rojas" };
    vector<int> edades = { 28, 34, 45, 50, 37, 32, 27, 42, 29, 38, 31, 47, 26 };
    vector<string> habitaciones = { "205", "101", "303", "402", "201", "104", "204", "501", "305", "103", "203", "502", "105" };
    vector<string> tiposAlojamiento = { "Casa de playa", "Departamento", "Casa de playa", "Departamento", "Casa de playa",
                                       "Departamento", "Casa de playa", "Departamento", "Casa de playa", "Departamento",
                                       "Casa de playa", "Departamento", "Casa de playa" };
    vector<string> lugares = { "Casa Blanca", "El Refugio", "La Morada", "Vista Alegre", "La Colina",
                              "El Mirador", "Jardines del Sol", "Los Pinos", "La Alameda", "El Bosque",
                              "Las Flores", "Rincón del Cielo", "La Cascada" };
    vector<string> promociones = { "Interbank", "BCP", "Interbank", "BCP", "Interbank",
                                  "BCP", "Interbank", "BCP", "Interbank", "BCP",
                                  "Interbank", "BCP", "Interbank" };

    srand(static_cast<unsigned int>(time(0)));  // Inicializa la semilla para números aleatorios

    int numClientes;
    cout << "Ingrese el número de clientes a registrar: ";
    cin >> numClientes;

    for (int i = 0; i < numClientes; i++) {
        int idx = rand() % nombres.size(); // Seleccionar un índice aleatorio

        string nombreCompleto = nombres[idx];
        int edad = edades[idx];
        int habitacion = stoi(habitaciones[idx]);
        string tipoAlojamiento = tiposAlojamiento[idx];
        string lugar = lugares[idx];
        string promocion = promociones[idx];

        Cliente* nuevoCliente = new Cliente(id++, nombreCompleto, edad, habitacion, tipoAlojamiento, lugar, promocion);
        colaUsuarios.encolar(nuevoCliente);

        cout << "Cliente registrado en la cola con éxito.\n";
    }
}

void mostrarInfoCliente(Usuario* Usuario) {
    cout << "Atendiendo a: " << Usuario->getNombre() << endl;
    // Aquí puedes agregar más información específica del cliente si lo necesitas.
}

void atenderClientesDeCola(Cola<Usuario*>& colaUsuarios, void (*mostrarInformacion)(Usuario*)) {
    system("cls");
    cout << "\n*Atendiendo Usuarios de la Cola*\n";

    while (!colaUsuarios.estaVacia()) {
        Usuario* usuario = colaUsuarios.desencolar();
        mostrarInformacion(usuario);
    }

    cout << "Todos los usuarios han sido atendidos.\n";
}

void registrarEmpleado(Lista<Usuario*>& listaUsuarios, int& id) {
    system("cls");
    cout << "\n*Registro de Empleados Aleatorios*\n";

    vector<string> nombres = { "Juan Perez", "Pedro Gomez", "Maria Lopez", "Ana Martinez", "Luis Garcia", "Elena Sanchez", "Carlos Ramirez", "Lucia Torres" };
    vector<int> edades = { 25, 30, 35, 40, 45, 50, 55, 60 };
    vector<string> lugares = { "Hotel Central", "Resort Playa", "Cabañas del Sol", "Hostal Mar" };
    vector<string> tiposAlojamiento = { "Departamento", "Casa de playa", "Cabaña" };
    vector<string> departamentos = { "Limpieza", "Recepción", "Servicios" };

    srand(static_cast<unsigned int>(time(0)));  // Inicializa la semilla para números aleatorios

    int numEmpleados;
    cout << "Ingrese el número de empleados a registrar: ";
    cin >> numEmpleados;

    for (int i = 0; i < numEmpleados; i++) {
        int idxNombre = rand() % nombres.size(); // Seleccionar un índice aleatorio
        int idxEdad = rand() % edades.size();
        int idxLugar = rand() % lugares.size();
        int idxTipoAlojamiento = rand() % tiposAlojamiento.size();
        int idxDepartamento = rand() % departamentos.size();

        string nombreCompleto = nombres[idxNombre];
        int edad = edades[idxEdad];
        string tipoAlojamiento = tiposAlojamiento[idxTipoAlojamiento];
        string lugarTrabajo = lugares[idxLugar];
        string departamento = departamentos[idxDepartamento];

        // Generar una contraseña aleatoria
        string contrasena;
        for (int j = 0; j < 8; ++j) { // Contraseña de 8 caracteres
            contrasena += static_cast<char>(33 + rand() % (126 - 33 + 1)); // Caracteres imprimibles en ASCII
        }

        Empleado* nuevoEmpleado = new Empleado(id++, nombreCompleto, edad, tipoAlojamiento, lugarTrabajo, departamento, contrasena);
        listaUsuarios.insertarFinal(nuevoEmpleado);
    }

    cout << "Empleados registrados con éxito.\n";

    system("cls");
    listaUsuarios.mostrar();
}

/// GRAFOS
void registrarConexion(CGrafo<Cliente>& grafo) { // Cambiar int por Cliente
    int id1, id2;
    double distancia;
    cout << "Ingrese ID del primer cliente: ";
    cin >> id1;
    cout << "Ingrese ID del segundo cliente: ";
    cin >> id2;
    cout << "Ingrese la distancia entre los dos clientes: ";
    cin >> distancia;

    grafo.adicionarArco(id1, id2, distancia);
    grafo.adicionarArco(id2, id1, distancia);

    cout << "Conexión registrada exitosamente.\n";
}


void mostrarConexiones(CGrafo<Cliente>& grafo) { 
    grafo.mostrarGrafo();
}


void generarConexionesAleatorias(CGrafo<Cliente>& grafo) {
    srand(static_cast<unsigned int>(time(0)));
    int cantidad = grafo.cantidadVertices();

    for (int i = 0; i < cantidad; ++i) {
        for (int j = i + 1; j < cantidad; ++j) {
            double distancia = (rand() % 100) + 1;  // Distancia aleatoria entre 1 y 100
            grafo.adicionarArco(i, j, distancia);
            grafo.adicionarArco(j, i, distancia);
        }
    }
    cout << "Conexiones aleatorias generadas exitosamente.\n";
}
int main() {
    ServerStatus servidor;
    servidor.encender();

    Lista<Reservacion*> listaReservaciones;
    Lista<Resena*> listaReviews;
    Lista<Usuario*> listaUsuarios;
    Cola<Usuario*> colaUsuarios;
    GestionDatos gestionDatos; // Instancia de GestionDatos

    int opcion = 0;
    Administrador admin("admin123");

    if (!admin.inicioSesion()) {
        cout << "Demasiados intentos fallidos. Saliendo del sistema.\n";
        return 1;
    }
    system("cls");
    int id = 1;

    do {
        menuSelector(); 
        cin >> opcion;

        switch (opcion) {
        case 1:
            system("cls");
            cout << "Registrar Cliente:\n";
            cout << "1. Registrar Cliente por app:\n";
            cout << "2. Registrar Cliente prescencial:\n";
            int subOpcion;
            cin >> subOpcion;
            if (subOpcion == 1) {
                registrarCliente(listaUsuarios, listaReservaciones, listaReviews, id);
                cout << "Cliente registrado con exito \n";
                system("cls");
            }
            else if (subOpcion == 2) {
                registrarClientePrescencial(colaUsuarios, id);
                cout << "Cliente Encolado con exito \n";
                system("cls");
            }
            else {
                cout << "Opción no válida.\n";
                system("cls");
            }
            break;
        case 2:
            atenderClientesDeCola(colaUsuarios, mostrarInfoCliente);
            system("cls");
            break;
        case 3:
            registrarEmpleado(listaUsuarios, id);
            system("cls");
            break;
        case 4:
            system("cls");
            cout << "Usuarios registrados:\n";
            listaUsuarios.mostrar();
            cout << "\nOrdenar Usuarios:\n";
            cout << "1. Ordenar por intercambio\n";
            cout << "2. Ordenar por Quicksort\n";
            cout << "3. Ordenar por Mergesort\n";
            cout << "4. Ordenar por Heapsort\n";
            int subOpcion2;
            cin >> subOpcion2;
            switch (subOpcion2) {
            case 1:
                listaUsuarios.ordenarByIntercambio();
                listaUsuarios.mostrar();
                break;
            case 2:
                listaUsuarios.ordenarByQuickSort();
                listaUsuarios.mostrar();
                break;
            case 3:
                listaUsuarios.ordenarByMergeSort();
                listaUsuarios.mostrar();
                break;
            case 4:
                listaUsuarios.ordenarByHeapSort();
                listaUsuarios.mostrar();
                break;
            default:
                cout << "Opción no válida.\n";
                system("cls");
                break;
            }
            break;
        case 5:
            system("cls");
            cout << "Reservaciones hasta la fecha: \n";
            Reservacion::mostrarReservaciones(listaReservaciones);
            break;
        case 6:
            system("cls");
            cout << "Reseñas hasta la fecha: " << endl;
            if (listaReviews.getTamano() > 0) {
                Nodo<Resena*>* nodoActual = listaReviews.getInicio();
                while (nodoActual != nullptr) {
                    nodoActual->valor->show();
                    nodoActual = nodoActual->siguiente;
                }
            }
            else {
                cout << "No hay reseñas disponibles.\n";
            }
            break;
        case 7:
            system("cls");
            try {
                Usuario* primerCliente = listaUsuarios.obtenerUltimoSinEliminar();
                cout << "Primer cliente registrado: " << primerCliente->toString() << endl;
            }
            catch (const std::runtime_error& e) {
                cout << e.what() << endl;
            }
            break;
        case 8:
            system("cls");
            cout << "SUMAR O RESTAR EDADES\n";
            cout << "1. Sumar edades \n";
            cout << "2. Restar edades \n";
            int subOpcion3;
            cin >> subOpcion3;
            if (subOpcion3 == 1) {
                int sumaEdades = sumaEdadesRecursiva(listaUsuarios.getInicio());
                cout << "La suma de las edades de todos los clientes es: " << sumaEdades << endl;
            }
            else if (subOpcion3 == 2) {
                int restaEdades = restaEdadesLambda(listaUsuarios.getInicio());
                cout << "La resta de las edades de todos los clientes es: " << restaEdades << endl;
            }
            else {
                cout << "Opción no válida.\n";
            }
            break;
        case 9:
            // Submenú para mostrar clientes en el árbol en diferentes órdenes
            system("cls");
            cout << "Mostrar Clientes en el Arbol:\n";
            cout << "1. En orden\n";
            cout << "2. Preorden\n";
            cout << "3. Postorden\n";
            int subOpcion4;
            cin >> subOpcion4;
            switch (subOpcion4) {
            case 1:
                gestionDatos.mostrarArbolEnOrden();
                break;
            case 2:
                gestionDatos.mostrarArbolPreOrden();
                break;
            case 3:
                gestionDatos.mostrarArbolPostOrden();
                break;
            default:
                cout << "Opción no válida.\n";
            }
            break;
        case 10:
            buscarClienteArbol(*gestionDatos.getArbol());
            break;
        case 11:
            buscarClienteHashTable(gestionDatos.getTablaClientes());
            break;
        case 12:
            mostrarClientesOrdenados(*gestionDatos.getArbol());
            break;
        case 13:
            mostrarClientesPorRango(*gestionDatos.getArbol());
            break;
        case 14:
            contarClientesArbol(*gestionDatos.getArbol());
            break;
        case 15:
            eliminarClienteArbolYHash(*gestionDatos.getArbol(), gestionDatos.getTablaClientes());
            break;
        case 16:
            cout << "Mostrando todos los clientes/empleados en la tabla hash:\n";
            gestionDatos.getTablaClientes().DispAll();
            break;
        case 17:
            gestionDatos.LecturaDatosArchivo();
            cout << "Datos leidos desde el archivo.\n";
            break;
        case 18:
            cout << "Generando conexiones aleatorias..." << endl;
            gestionDatos.generarConexionesAleatorias();
            break;
        case 19:
            cout << "Mostrando conexiones en el grafo..." << endl;
            gestionDatos.mostrarGrafo();
            break;
        case 20:
            cout << "Saliendo del sistema.\n";
            servidor.apagar();
            break;
        default:
            cout << "Opción no válida. Por favor intente nuevamente.\n";
        }
    } while (opcion != 20);

    return 0;
}


