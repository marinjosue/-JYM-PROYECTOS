/*************************
 UFA - ESPE
 * Module:  ListaDoble.h
 * Author:  Chiliquinga Yeshua, Marin Alquinga,Salcedo Micaela
 * Modified: domingo, 17 de diciembre de 2023
 * Purpose: Declaracion del encabezado ListaDoble
 ***********************************************************************/
#ifndef LISTADOBLE_H_INCLUDED
#define LISTADOBLE_H_INCLUDED

#include "Nodo.h"
#include "Persona.h"

template <typename T>
class ListaDoble
{
public:
    ListaDoble<T>();
    bool esta_vacia();
    void insertarAlInicio(Persona* persona);
    void insertarAlFinal(Persona* persona);
    void eliminarPersona(Persona* persona);
    void eliminarAlInicio();
    void eliminarAlFinal();
    void mostrarLista();

protected:
private:
    Nodo<T>* cabeza;
    Nodo<T>* cola;
};

#endif // LISTADOBLE_H_INCLUDED
