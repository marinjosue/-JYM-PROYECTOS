#include "JuegoRondas.h"
#include <cstdio>

JuegoRondas::JuegoRondas() : cabeza(nullptr) {}

JuegoRondas::~JuegoRondas() {
    if (cabeza == nullptr) return;

    Nodo* actual = cabeza;
    do {
        Nodo* siguiente = actual->siguiente;
        delete actual;
        actual = siguiente;
    } while (actual != cabeza);
}

void JuegoRondas::agregarJugador(std::string nombreJugador) {
    Nodo* nuevoJugador = new Nodo{nombreJugador, nullptr};

    if (cabeza == nullptr) {
        cabeza = nuevoJugador;
        cabeza->siguiente = cabeza;
    } else {
        Nodo* actual = cabeza;
        while (actual->siguiente != cabeza) {
            actual = actual->siguiente;
        }
        actual->siguiente = nuevoJugador;
        nuevoJugador->siguiente = cabeza;
    }
}

void JuegoRondas::avanzarSiguienteTurno() {
    if (cabeza == nullptr) {
        printf("No hay jugadores en el juego.\n");
        return;
    }

    Nodo* nuevoCabeza = cabeza->siguiente;

    if (nuevoCabeza != nullptr) {
        printf("Siguiente turno: Jugador %s\n", nuevoCabeza->jugador.c_str());
        cabeza = nuevoCabeza;
    } else {
        printf("No hay jugadores en el juego después de avanzar el turno.\n");
    }
}



void JuegoRondas::eliminarJugador(std::string nombreJugador) {
    if (cabeza == nullptr) {
        printf("No hay jugadores en el juego.\n");
        return;
    }

    Nodo* actual = cabeza;
    Nodo* anterior = nullptr;

    do {
        if (actual->jugador == nombreJugador) {
            if (actual->siguiente == actual) {
                // Único jugador en la lista
                delete actual;
                cabeza = nullptr;
                printf("Jugador eliminado: %s\n", nombreJugador.c_str());
                return;
            }

            if (anterior != nullptr) {
                anterior->siguiente = actual->siguiente;
            }

            if (actual == cabeza) {
                cabeza = actual->siguiente;
            }

            Nodo* siguiente = actual->siguiente;
            delete actual;
            printf("Jugador eliminado: %s\n", nombreJugador.c_str());
            return;
        }

        anterior = actual;
        actual = actual->siguiente;
    } while (actual != cabeza);

    printf("Jugador no encontrado: %s\n", nombreJugador.c_str());
}

void JuegoRondas::mostrarListaJugadores() {
    if (cabeza == nullptr) return;

    Nodo* actual = cabeza;
    do {
        // Cambiar a printf() con formato seguro
        printf("Jugador: %s\n", actual->jugador.c_str());
        actual = actual->siguiente;
    } while (actual != cabeza);
}

