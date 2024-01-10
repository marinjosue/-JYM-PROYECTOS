#ifndef GESTORPRSONAS_H_INCLUDED
#define GESTORPRSONAS_H_INCLUDED

#include "ListaDoble.cpp"
#include "Persona.h"

class GestorPersonas {
private:

    ListaDoble<Persona*> listaPersonas; //;

public:
    void ingresarPersona();
    Persona* buscarPersona();
    void imprimirPersona();
    void eliminarPersona();
        void ordenamientoShellSort();

};

#endif // GESTORPRSONAS_H_INCLUDED
