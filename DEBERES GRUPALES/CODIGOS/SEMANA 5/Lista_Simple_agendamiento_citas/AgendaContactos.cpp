#include "AgendaContactos.h"
#include <iostream>

AgendaContactos::AgendaContactos() : cabeza(nullptr) {}

AgendaContactos::~AgendaContactos() {
    Nodo* actual = cabeza;
    while (actual != nullptr) {
        Nodo* siguiente = actual->siguiente;
        delete actual;
        actual = siguiente;
    }
}

void AgendaContactos::agregarContacto(std::string nombre, std::string telefono) {
    Nodo* nuevoContacto = new Nodo{nombre, telefono, nullptr};

    if (cabeza == nullptr) {
        cabeza = nuevoContacto;
    } else {
        Nodo* actual = cabeza;
        while (actual->siguiente != nullptr) {
            actual = actual->siguiente;
        }
        actual->siguiente = nuevoContacto;
    }
}

void AgendaContactos::buscarContacto(std::string nombre) {
    Nodo* actual = cabeza;
    while (actual != nullptr) {
        if (actual->nombre == nombre) {
            std::cout << "Contacto encontrado: " << actual->nombre << " - " << actual->telefono << std::endl;
            return;
        }
        actual = actual->siguiente;
    }
    std::cout << "Contacto no encontrado." << std::endl;
}

void AgendaContactos::eliminarContacto(std::string nombre) {
    Nodo* actual = cabeza;
    Nodo* anterior = nullptr;

    while (actual != nullptr) {
        if (actual->nombre == nombre) {
            if (anterior == nullptr) {
                cabeza = actual->siguiente;
            } else {
                anterior->siguiente = actual->siguiente;
            }
            delete actual;
            std::cout << "Contacto eliminado." << std::endl;
            return;
        }
        anterior = actual;
        actual = actual->siguiente;
    }

    std::cout << "Contacto no encontrado." << std::endl;
}

void AgendaContactos::mostrarContactos() {
    Nodo* actual = cabeza;
    while (actual != nullptr) {
        std::cout << "Nombre: " << actual->nombre << " - Telefono: " << actual->telefono << std::endl;
        actual = actual->siguiente;
    }
}
