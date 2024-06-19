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

using namespace System;
using namespace std;

void mostrarMenu() {
    cout << "\n========================================\n";
    cout << "===          Menu Cloudbeds          ===\n";
    cout << "========================================\n\n";
    cout << "1. Registrar Cliente\n";
    cout << "2. Atender clientes de la cola\n";
    cout << "3. Registrar Empleado\n";
    cout << "4. Mostrar Usuarios\n";
    cout << "5. Mostrar Reservas hasta la fecha\n";
    cout << "6. Resenas\n";
    cout << "7. Mostrar primer cliente registrado\n";
    cout << "8. Calcular suma de edades de los clientes\n";
    cout << "9. Salir\n";
    cout << "========================================\n";
    cout << "Seleccione una opcion: ";
}

void AnadirReviews(Nodo<Usuario*>* nodoCliente, Lista<Resena*>& listaReviews) {
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

    AnadirReviews(nodoCliente->siguiente, listaReviews);
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
    cout << "Habitacion: " << cliente.getHabitacion() << endl;
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

    char deseaExtras;
    cout << "¿Desea anadir jabon, champu y toalla? (si/no): ";
    cin >> deseaExtras;
    if (deseaExtras == 'si' || deseaExtras == 'Si') {
        total += 15;
    }

    cout << "Precio Alojamiento: $" << total << endl;
    cout << "Total: $" << total << endl;

    cout << "¿Desea realizar el pago ahora? (si/no): ";
    char deseaPagar;
    cin >> deseaPagar;

    if (deseaPagar == 's' || deseaPagar == 'S') {
        cout << "Seleccione metodo de pago: \n1. Efectivo\n2. Tarjeta\n3. Transferencia\n";
        int opcionMetodoPago;
        cin >> opcionMetodoPago;

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

void registrarCliente(Lista<Usuario*>& listaUsuarios, Lista<Reservacion*>& listaReservaciones, Lista<Resena*>& listaReviews, int& id) {
    system("cls");
    cout << "\n*Registro de Cliente*\n";
    cout << "Ingrese nombre completo: ";
    cin.ignore();
    string nombreCompleto;
    getline(cin, nombreCompleto);

    cout << "Ingrese edad: ";
    int edadTemporal;
    cin >> edadTemporal;
    while (edadTemporal <= 0 || edadTemporal >= 100) {
        cout << "Edad inválida. Ingrese nuevamente: ";
        cin >> edadTemporal;
    }
    int edad = edadTemporal;

    Inventario inventario;

    cout << "Ingrese el número de habitación: ";
    string habitacion;
    cin >> habitacion;

    cout << "Seleccione el tipo de alojamiento: " << endl;
    cout << "1. Departamento\n";
    cout << "2. Casa de playa\n";
    cout << "3. Cabaña\n";
    int opcionTipoAlojamiento;
    cin >> opcionTipoAlojamiento;
    while (opcionTipoAlojamiento < 1 || opcionTipoAlojamiento > 3) {
        cout << "Opción inválida. Ingrese nuevamente: ";
        cin >> opcionTipoAlojamiento;
    }
    string tipoAlojamiento;
    switch (opcionTipoAlojamiento) {
    case 1: tipoAlojamiento = "Departamento"; break;
    case 2: tipoAlojamiento = "Casa de playa"; break;
    case 3: tipoAlojamiento = "Cabaña"; break;
    default: tipoAlojamiento = "Indefinido";
    }

    cout << "Ingrese nombre del hospedaje: " << endl;
    string lugar;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    getline(cin, lugar);

    cout << "Seleccione la promoción: " << endl;
    cout << "1. Interbank\n";
    cout << "2. BCP\n";
    cout << "3. Sin promoción\n";
    int opcionPromocion;
    cin >> opcionPromocion;
    while (opcionPromocion < 1 || opcionPromocion > 3) {
        cout << "Opción inválida. Ingrese nuevamente: ";
        cin >> opcionPromocion;
    }
    string promocion;
    switch (opcionPromocion) {
    case 1: promocion = "Interbank"; break;
    case 2: promocion = "BCP"; break;
    case 3: promocion = "Sin promoción"; break;
    default: promocion = "Indefinida";
    }

    Cliente* nuevoCliente = new Cliente(id++, nombreCompleto, edad, stoi(habitacion), tipoAlojamiento, lugar, promocion);
    listaUsuarios.insertarFinal(nuevoCliente);

    cout << "Cliente registrado con éxito.\n";
    generarFactura(*nuevoCliente, inventario, id);

    Reservacion* nuevaReservacion = new Reservacion(nombreCompleto, habitacion);
    listaReservaciones.insertarFinal(nuevaReservacion);

    AnadirReviews(listaUsuarios.getInicio(), listaReviews);

    cout << "Reservación creada con éxito para " << nuevoCliente->getNombreCompleto() << ".\n";
}

void registrarClientePrescencial(Cola<Usuario*>& colaUsuarios, int& id) {
    system("cls");
    cout << "\n*Registro de Usuario en Cola*\n";
    cout << "Ingrese nombre completo: ";
    cin.ignore();
    string nombreCompleto;
    getline(cin, nombreCompleto);

    cout << "Ingrese edad: ";
    int edadTemporal;
    cin >> edadTemporal;
    while (edadTemporal <= 0 || edadTemporal >= 100) {
        cout << "Edad inválida. Ingrese nuevamente: ";
        cin >> edadTemporal;
    }
    int edad = edadTemporal;

    cout << "Ingrese el número de habitación: ";
    string habitacion;
    cin >> habitacion;

    cout << "Seleccione el tipo de alojamiento: " << endl;
    cout << "1. Departamento\n";
    cout << "2. Casa de playa\n";
    cout << "3. Cabaña\n";
    int opcionTipoAlojamiento;
    cin >> opcionTipoAlojamiento;
    while (opcionTipoAlojamiento < 1 || opcionTipoAlojamiento > 3) {
        cout << "Opción inválida. Ingrese nuevamente: ";
        cin >> opcionTipoAlojamiento;
    }
    string tipoAlojamiento;
    switch (opcionTipoAlojamiento) {
    case 1: tipoAlojamiento = "Departamento"; break;
    case 2: tipoAlojamiento = "Casa de playa"; break;
    case 3: tipoAlojamiento = "Cabaña"; break;
    default: tipoAlojamiento = "Indefinido";
    }

    cout << "Ingrese nombre del hospedaje: " << endl;
    string lugar;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    getline(cin, lugar);

    cout << "Seleccione la promoción: " << endl;
    cout << "1. Interbank\n";
    cout << "2. BCP\n";
    cout << "3. Sin promoción\n";
    int opcionPromocion;
    cin >> opcionPromocion;
    while (opcionPromocion < 1 || opcionPromocion > 3) {
        cout << "Opción inválida. Ingrese nuevamente: ";
        cin >> opcionPromocion;
    }
    string promocion;
    switch (opcionPromocion) {
    case 1: promocion = "Interbank"; break;
    case 2: promocion = "BCP"; break;
    case 3: promocion = "Sin promoción"; break;
    default: promocion = "Indefinida";
    }

    Cliente* nuevoCliente = new Cliente(id++, nombreCompleto, edad, stoi(habitacion), tipoAlojamiento, lugar, promocion);
    colaUsuarios.encolar(nuevoCliente);

    cout << "Usuario registrado en la cola con éxito.\n";
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
    cout << "\n*Registro de Empleado*\n";
    cout << "Ingrese nombre completo: ";
    cin.ignore();
    string nombreCompleto;
    getline(cin, nombreCompleto);

    cout << "Ingrese edad: ";
    int edadTemporal;
    cin >> edadTemporal;
    while (edadTemporal <= 0 || edadTemporal <= 100 ) {
        cout << "Edad inválida. Ingrese nuevamente: ";
        cin >> edadTemporal;
    }
    int edad = edadTemporal;

    Inventario inventario;

    cout << "Seleccione el tipo de alojamiento: " << endl;
    cout << "1. Departamento\n";
    cout << "2. Casa de playa\n";
    cout << "3. Cabaña\n";
    int opcionTipoAlojamiento;
    cin >> opcionTipoAlojamiento;
    while (opcionTipoAlojamiento < 1 || opcionTipoAlojamiento > 3) {
        cout << "Opción inválida. Ingrese nuevamente: ";
        cin >> opcionTipoAlojamiento;
    }
    string tipoAlojamiento;
    switch (opcionTipoAlojamiento) {
    case 1: tipoAlojamiento = "Departamento"; break;
    case 2: tipoAlojamiento = "Casa de playa"; break;
    case 3: tipoAlojamiento = "Cabaña"; break;
    default: tipoAlojamiento = "Indefinido";
    }

    cout << "Ingrese el departamento de trabajo: ";
    cout << "1. Limpieza\n";
    cout << "2. Recepción\n";
    cout << "3. Servicios\n";
    int opciondepartamentotrabajo;
    cin >> opciondepartamentotrabajo;
    while (opciondepartamentotrabajo < 1 || opciondepartamentotrabajo > 3) {
        cout << "Opción inválida. Ingrese nuevamente: ";
        cin >> opciondepartamentotrabajo;
    }
    string departamentotrabajo;
    switch (opciondepartamentotrabajo) {
    case 1: departamentotrabajo = "limpieza"; break;
    case 2: departamentotrabajo = "recepción"; break;
    case 3: departamentotrabajo = "servicios"; break;
    default: departamentotrabajo = "Indefinido";
    }

    cout << "Ingrese nombre del lugar de trabajo: " << endl;
    string lugartrabajo;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    getline(cin, lugartrabajo);

    cout << "Ingrese la contraseña: ";
    string contrasena;
    cin >> contrasena;

    Empleado* nuevoEmpleado = new Empleado(id++, nombreCompleto, edad, tipoAlojamiento, lugartrabajo, departamentotrabajo, contrasena);
    listaUsuarios.insertarFinal(nuevoEmpleado);
    cout << "Empleado registrado con éxito.\n";

    system("cls");
    listaUsuarios.mostrar();
}

int main() {
    ServerStatus servidor;
    servidor.encender();

    Lista<Reservacion*> listaReservaciones;
    Lista<Resena*> listaReviews;
    Lista<Usuario*> listaUsuarios;
    Cola<Usuario*> colaUsuarios;

    int opcion = 0;    
    Administrador admin("admin123");

    if (!admin.inicioSesion()) {
        cout << "Demasiados intentos fallidos. Saliendo del sistema.\n";
        return 1;
    }
    system("cls");
    int id = 1;

    do {
        mostrarMenu();
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
            cout << "1.Ordenar por intercambio : \n";
            cout << "2. Ordenar por divide y vencerás:\n";
            int subOpcion2;
            cin >> subOpcion2;
            if (subOpcion2 == 1) {
                listaUsuarios.ordenarByIntercambio();
                listaUsuarios.mostrar();
            }
            else if (subOpcion2 == 2) {
                listaUsuarios.ordenarByQuicksort();
                listaUsuarios.mostrar();
            }
            else {
                cout << "Opción no válida.\n";
                system("cls");
            }
            break;
        
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
        {
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
        }
            break;
        case 9:
            cout << "Saliendo del sistema.\n";
            servidor.apagar();
            break;
        default:
            cout << "Opción no válida. Por favor intente nuevamente.\n";

        }
    } while (opcion != 8);

    return 0;
}
