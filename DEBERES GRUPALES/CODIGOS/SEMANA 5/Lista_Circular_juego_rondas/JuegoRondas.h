#pragma once
#include <string>

class JuegoRondas {
private:
    class Nodo {
    public:
        std::string jugador;
        Nodo* siguiente;
    };
    Nodo* cabeza;

public:
    JuegoRondas();
    ~JuegoRondas();

    void agregarJugador(std::string nombreJugador);
    void avanzarSiguienteTurno();
    void eliminarJugador(std::string nombreJugador);
    void mostrarListaJugadores();
};
