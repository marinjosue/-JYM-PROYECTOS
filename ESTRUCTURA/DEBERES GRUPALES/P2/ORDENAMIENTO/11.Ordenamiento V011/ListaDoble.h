/*************************
 UFA - ESPE
 * Module:  ListaDoble.h
 * Author:  Chiliquinga Yeshua, Marin Alquinga,Salcedo Micaela
 * Modified: domingo, 17 de diciembre de 2023
 * Purpose: Declaracion del encabezado ListaDoble
 ***********************************************************************/
#ifndef LISTADOBLE_H_INCLUDED
#define LISTADOBLE_H_INCLUDED

#include "Nodo.cpp"



class Persona;

template <typename T>
class ListaDoble
{
public:
    ListaDoble<T>();
    bool esta_vacia();
    void insertarAlInicio(Persona& persona);
    void insertarAlFinal(Persona& persona);
    void eliminarAlInicio();
    void eliminarAlFinal();
    void mostrarLista();
    bool buscarCedulaExistente(const std::string& cedula) const;
    void orden_seleccion(const std::string& criterio);

protected:
private:
    Nodo<T>* cabeza;
    Nodo<T>* cola;
    Nodo<T>* siguiente;
    Nodo<T>* anterior;
};

template <typename T>
bool ListaDoble<T>::buscarCedulaExistente(const std::string& cedula) const  {
    Nodo<T>* nodo_actual = cabeza;

    while (nodo_actual != nullptr) {
        Persona* persona_actual = nodo_actual->get_valor();

        if (persona_actual->getCedula() == cedula) {
            return false;
        }

        nodo_actual = nodo_actual->get_siguiente();
    }


    return true;
}

#endif // LISTADOBLE_H_INCLUDED
