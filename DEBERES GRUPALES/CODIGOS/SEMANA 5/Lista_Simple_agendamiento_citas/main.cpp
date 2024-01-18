#include <iostream>
#include "AgendaContactos.h"

int main() {
    AgendaContactos agenda;

    agenda.agregarContacto("Juan", "555-1234");
    agenda.agregarContacto("Maria", "555-5678");
    agenda.agregarContacto("Carlos", "555-9876");

    std::cout << "Lista de contactos inicial:" << std::endl;
    agenda.mostrarContactos();

    agenda.buscarContacto("Maria");

    agenda.eliminarContacto("Carlos");

    std::cout << "Lista de contactos despues de eliminar a Carlos:" << std::endl;
    agenda.mostrarContactos();

    return 0;
}
