#include <cstdio>
#include "JuegoRondas.h"

int main() {
    JuegoRondas juego;

    juego.agregarJugador("Jugador1");
    juego.agregarJugador("Jugador2");
    juego.agregarJugador("Jugador3");

    printf("Lista de jugadores inicial:\n");
    juego.mostrarListaJugadores();

    juego.avanzarSiguienteTurno();
    juego.eliminarJugador("Jugador2");

    printf("Lista de jugadores después de avanzar y eliminar Jugador2:\n");
    juego.mostrarListaJugadores();

    return 0;
}
