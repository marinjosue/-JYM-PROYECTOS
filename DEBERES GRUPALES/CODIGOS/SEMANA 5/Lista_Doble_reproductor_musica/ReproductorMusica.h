#pragma once
#include <string>

class ReproductorMusica {
private:
    class Nodo {
    public:
        std::string cancion;
        Nodo* anterior;
        Nodo* siguiente;
    };
    Nodo* cabeza;

public:
    ReproductorMusica();
    ~ReproductorMusica();

    void agregarCancion(std::string nombreCancion);
    void reproducirSiguiente();
    void reproducirAnterior();
    void eliminarCancion(std::string nombreCancion);
    void mostrarListaReproduccion();
};
