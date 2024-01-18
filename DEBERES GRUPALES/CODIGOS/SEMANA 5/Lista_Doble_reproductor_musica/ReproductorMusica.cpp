#include "ReproductorMusica.h"
#include <iostream>

ReproductorMusica::ReproductorMusica() : cabeza(nullptr) {}

ReproductorMusica::~ReproductorMusica() {
    Nodo* actual = cabeza;
    while (actual != nullptr) {
        Nodo* siguiente = actual->siguiente;
        delete actual;
        actual = siguiente;
    }
}

void ReproductorMusica::agregarCancion(std::string nombreCancion) {
    Nodo* nuevaCancion = new Nodo{nombreCancion, nullptr, nullptr};

    if (cabeza == nullptr) {
        cabeza = nuevaCancion;
    } else {
        Nodo* actual = cabeza;
        while (actual->siguiente != nullptr) {
            actual = actual->siguiente;
        }
        actual->siguiente = nuevaCancion;
        nuevaCancion->anterior = actual;
    }
}

void ReproductorMusica::reproducirSiguiente() {
    if (cabeza == nullptr || cabeza->siguiente == nullptr) {
        std::cout << "No hay canciones para reproducir." << std::endl;
        return;
    }

    Nodo* actual = cabeza->siguiente;
    std::cout << "Reproduciendo siguiente cancion: " << actual->cancion << std::endl;
}

void ReproductorMusica::reproducirAnterior() {
    if (cabeza == nullptr || cabeza->anterior == nullptr) {
        std::cout << "No hay canciones anteriores para reproducir." << std::endl;
        return;
    }

    Nodo* actual = cabeza->anterior;
    std::cout << "Reproduciendo cancion anterior: " << actual->cancion << std::endl;
}

void ReproductorMusica::eliminarCancion(std::string nombreCancion) {
    if (cabeza == nullptr) {
        std::cout << "La lista de reproducción esta vacía." << std::endl;
        return;
    }

    Nodo* actual = cabeza;
    while (actual != nullptr) {
        if (actual->cancion == nombreCancion) {
            if (actual->anterior != nullptr) {
                actual->anterior->siguiente = actual->siguiente;
            }
            if (actual->siguiente != nullptr) {
                actual->siguiente->anterior = actual->anterior;
            }
            if (actual == cabeza) {
                cabeza = actual->siguiente;
            }
            delete actual;
            std::cout << "Cancion eliminada: " << nombreCancion << std::endl;
            return;
        }
        actual = actual->siguiente;
    }

    std::cout << "Cancion no encontrada: " << nombreCancion << std::endl;
}

void ReproductorMusica::mostrarListaReproduccion() {
    Nodo* actual = cabeza;
    while (actual != nullptr) {
        std::cout << "Cancion: " << actual->cancion << std::endl;
        actual = actual->siguiente;
    }
}
