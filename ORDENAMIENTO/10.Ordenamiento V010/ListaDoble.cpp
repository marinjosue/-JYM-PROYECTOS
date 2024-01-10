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
ListaDoble<T>::ListaDoble(){
    siguiente = nullptr;
    anterior = nullptr;
    cabeza = nullptr;
    cola = nullptr;

}

template <typename T>
bool ListaDoble<T>::esta_vacia(){
    return (cabeza == nullptr);
}



template <typename T>
void ListaDoble<T>::insertarAlInicio(Persona& persona) {
    Nodo<T>* nuevo_nodo = new Nodo<T>(new Persona(persona.getNombre(), persona.getApellido(), persona.getCedula(), persona.getId()), nullptr, nullptr);

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
void ListaDoble<T>::orden_seleccion(int criterio) {
    Nodo<T>* actual = cabeza;


    while (actual != nullptr) {
        Nodo<T>* minimo = actual;
        Nodo<T>* temp = actual->get_siguiente();

        while (temp != nullptr) {
            switch (criterio) {
                case 1: // Sort by Nombre
                    if (temp->get_valor()->getNombre() < minimo->get_valor()->getNombre()) {
                        minimo = temp;
                    }
                    break;
                case 2: // Sort by Apellido
                    if (temp->get_valor()->getApellido() < minimo->get_valor()->getApellido() ) {
                        minimo = temp;
                    }
                    break;
                case 3: // Sort by Cedula
                    if (temp->get_valor()->getCedula() < minimo->get_valor()->getCedula()) {
                        minimo = temp;
                    }
                    break;
                default:
                    // Handle invalid criterio
                    break;
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




