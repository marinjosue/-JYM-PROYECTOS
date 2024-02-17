/*************************
 UFA - ESPE
 * Module:  ListasDoble.cpp
 * Author:  Chiliquinga Yeshua, Marin Alquinga,Salcedo Micaela
 * Modified: domingo, 17 de diciembre de 2023
 * Purpose: Implementacion de clase ListaDoble
 ***********************************************************************/

#include "ListaDoble.h"

#include <iostream>


using namespace std;

template <typename T>
ListaDoble<T>::ListaDoble(){
    cabeza = nullptr;
    cola = nullptr;

}


template <typename T>
void ListaDoble<T>::insertarAlInicio(Persona* persona) {
    Nodo<T>* nuevo_nodo = new Nodo<T>(persona);
    if (esta_vacia()) {
        cabeza = nuevo_nodo;
        cola = nuevo_nodo;
    } else {
        nuevo_nodo->set_siguiente(cabeza);
        cabeza->set_anterior(nuevo_nodo);
        cabeza = nuevo_nodo;
    }
}


template <typename T>
void ListaDoble<T>::mostrarLista(){
 Nodo<T>* actual = cabeza;

    cout << "Cedula    Nombre    Apellido   ID" << endl;
    cout << "===========================================================================" << endl;

    while (actual != nullptr) {
        // Suponiendo que T es Persona* y que Persona tiene métodos getCedula(), getNombre(), getApellido() e getId()
        cout << actual->get_valor() << "    "
             << actual->get_valor()->getNombre() << "    "
             << actual->get_valor()->getApellido() << "    "
             << actual->get_valor()->getId() << endl;

        actual = actual->get_siguiente();
    }

    cout << "===========================================================================" << endl;
}


template <typename T>
bool ListaDoble<T>::esta_vacia(){
    return (cabeza == nullptr);
}



template <typename T>
void ListaDoble<T>::insertarAlFinal(Persona* persona){

}

template <typename T>
void ListaDoble<T>::eliminarAlInicio(){

}

template <typename T>
void ListaDoble<T>::eliminarAlFinal(){

}
