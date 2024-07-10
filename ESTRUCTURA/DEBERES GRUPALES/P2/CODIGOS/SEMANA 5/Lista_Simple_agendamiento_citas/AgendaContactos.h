#pragma once
#include <string>
class AgendaContactos {
private:
    class Nodo {
    public:
        std::string nombre;
        std::string telefono;
        Nodo* siguiente;
    };
    Nodo* cabeza;

public:
    AgendaContactos();
    ~AgendaContactos();

    void agregarContacto(std::string nombre, std::string telefono);
    void buscarContacto(std::string nombre);
    void eliminarContacto(std::string nombre);
    void mostrarContactos();
};
