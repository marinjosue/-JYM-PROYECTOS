/*************************
 UFA - ESPE
 * Module:  ListasDoble.cpp
 * Author:  Chiliquinga Yeshua, Marin Alquinga,Salcedo Micaela
 * Modified: domingo, 17 de diciembre de 2023
 * Purpose: Implementacion de clase ListaDoble
 ***********************************************************************/

#include "ListaDoble.h"
#include "Persona.h"

#include <iostream>
using namespace std;

template <typename T>
ListaDoble<T>::ListaDoble(Nodo<T>* _cabeza){
    cabeza = _cabeza;
}

template <typename T>
ListaDoble<T>::ListaDoble(){
    cabeza = nullptr;
    siguiente = nullptr;
    anterior = nullptr;
    cola = nullptr;
}

template <typename T>
Nodo<T>* ListaDoble<T>::get_cabeza(){
    return cabeza;
}

template <typename T>
void ListaDoble<T>::set_cabeza(Nodo<T>* nueva_cabeza){
    cabeza = nueva_cabeza;
}

template <typename T>
Nodo<T>* ListaDoble<T>::get_cola(){
    return cola;
}

template <typename T>
void ListaDoble<T>::set_cola(Nodo<T>* nueva_cola){
    cola = nueva_cola;
}

template <typename T>
void ListaDoble<T>::insertar_cola(T valor){
    Nodo<T>* nuevo_nodo;
    if(esta_vacia()){
        nuevo_nodo = new Nodo<T>(valor, nullptr, nullptr);
        cabeza = nuevo_nodo;
    }
    else{
        nuevo_nodo = new Nodo<T>(valor, nullptr, cola);
        cola->set_siguiente(nuevo_nodo);
    }
    cola = nuevo_nodo;
}

template <typename T>
void ListaDoble<T>::imprimir(){
    Nodo<T>* aux = cabeza;
    while(aux!=nullptr){
        printf("\n %f", aux->get_valor());
        aux = aux->get_siguiente();
    }
}

template <typename T>
bool ListaDoble<T>::esta_vacia(){
    return (cabeza == nullptr);
}

template <typename T>
void ListaDoble<T>::insertarAlFinal(Persona& persona) {
    Nodo<T>* nuevo_nodo = new Nodo<T>(new Persona(persona.getNombre(), persona.getApellido(), persona.getCedula(), persona.getId()), nullptr, nullptr);

    if (esta_vacia()) {
        cabeza = nuevo_nodo;
        cola = nuevo_nodo;
    } else {
        nuevo_nodo->set_anterior(cola);
        cola->set_siguiente(nuevo_nodo);
        cola = nuevo_nodo;
    }
}


template <typename T>
void ListaDoble<T>::mostrarLista() {
    Nodo<T>* actual = cabeza;

    cout << "Cedula    Nombre    Apellido   ID" << endl;
    cout << "===========================================================================" << endl;

    try {
        while (actual != nullptr) {
            Persona* persona_actual = actual->get_valor();
            cout << persona_actual->getCedula() << "    "
                << persona_actual->getNombre() << "    "
                << persona_actual->getApellido() << "    "
                << persona_actual->getId() << endl;

            actual = actual->get_siguiente();
        }
    } catch (const std::exception& e) {
        cerr << "Error al mostrar la lista: " << e.what() << endl;
    }

    cout << "===========================================================================" << endl;
}


template <typename T>
void ListaDoble<T>::eliminarAlInicio() {
    if (esta_vacia()) {

        return;
    }

    Nodo<T>* nodo_a_eliminar = cabeza;

    if (cabeza->get_siguiente() != nullptr) {
        cabeza = cabeza->get_siguiente();
        cabeza->set_anterior(nullptr);
    } else {
        // La lista solo tiene un elemento.
        cabeza = nullptr;
        cola = nullptr;
    }

    // Obtener la persona asociada al nodo
    Persona* persona_a_eliminar = nodo_a_eliminar->get_valor();
    // Actualizar el contadorId si es necesario
    if (std::stoi(persona_a_eliminar->getId().substr(1)) == Persona::contadorId) {
        Persona::contadorId--;
    }

    delete persona_a_eliminar;
    delete nodo_a_eliminar;
}

template <typename T>
void ListaDoble<T>::eliminarAlFinal() {
    if (esta_vacia()) {
        // La lista est� vac�a, no hay nada que eliminar.
        return;
    }
    Nodo<T>* nodo_a_eliminar = cola;
    if (cola->get_anterior() != nullptr) {
        cola = cola->get_anterior();
        cola->set_siguiente(nullptr);
    } else {
        // La lista solo tiene un elemento.
        cabeza = nullptr;
        cola = nullptr;
    }
    // Obtener la persona asociada al nodo
    Persona* persona_a_eliminar = nodo_a_eliminar->get_valor();
    // Actualizar el contadorId si es necesario
    if (std::stoi(persona_a_eliminar->getId().substr(1)) == Persona::contadorId) {
        Persona::contadorId--;
    }
    delete persona_a_eliminar;
    delete nodo_a_eliminar;
}
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

template <typename T>
void ListaDoble<T>::orden_seleccion(bool (*criterio)(T, T)) {
    Nodo<T>* actual = cabeza;

    while (actual != nullptr) {
        Nodo<T>* minimo = actual;
        Nodo<T>* temp = actual->get_siguiente();

        while (temp != nullptr) {
            if (criterio(temp->get_valor(), minimo->get_valor())) {
                minimo = temp;
            }
            temp = temp->get_siguiente();
        }

        // Intercambiar nodos
        T temp_valor = actual->get_valor();
        actual->set_valor(minimo->get_valor());
        minimo->set_valor(temp_valor);

        actual = actual->get_siguiente();
    }
}
