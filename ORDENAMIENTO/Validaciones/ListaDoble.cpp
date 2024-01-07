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

    Nodo<T>* nuevo_nodo = new Nodo<T>(new Persona(persona), siguiente, anterior);

    if (esta_vacia()) {
        cabeza = nuevo_nodo;
    } else {
        Nodo<T>* aux = cabeza;
        cabeza = nuevo_nodo;
        cabeza->set_siguiente(aux);
        aux->set_anterior(cabeza);
    }
}

template <typename T>
void ListaDoble<T>::insertarAlFinal(Persona& persona) {
    Nodo<T>* nuevo_nodo = new Nodo<T>(new Persona(persona), nullptr, nullptr);

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
            cout << persona_actual-> getCedula() << "    "
                << persona_actual->getNombre()<< "    "
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
        // La lista está vacía, no hay nada que eliminar.
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

    delete nodo_a_eliminar->get_valor();
    delete nodo_a_eliminar;
}

template <typename T>
void ListaDoble<T>::eliminarAlFinal() {
    if (esta_vacia()) {
        // La lista está vacía, no hay nada que eliminar.
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

    delete nodo_a_eliminar->get_valor();
    delete nodo_a_eliminar;
}
template <typename T>
bool ListaDoble<T>::buscar(std::string valor_buscado) {
    Nodo<T>* actual = cabeza;

  int posicion = 1;
  bool nodoEncontrado = false;
  while (actual != nullptr) {
    Persona* persona_actual = actual->get_valor();
    if (persona_actual->getCedula() == valor_buscado) {
      nodoEncontrado = true;
      break;
    }
    actual = actual->get_siguiente();
    posicion++;
  }

  if (nodoEncontrado) {
    std::cout << "El valor " << valor_buscado << " fue encontrado en la posición " << posicion << std::endl;
    return true;
  } else {
    return false;
  }
}
