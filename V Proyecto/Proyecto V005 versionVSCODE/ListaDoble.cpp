/***********************************************************************
 UFA - ESPE
 * Module:  ListaDoble.cpp
 * Author:  Joan Cobeña, Edison Verdesoto
 * Modified: jueves, 7 de diciembre de 2023 01:11:27 p. m.
 * Purpose: Implementacion de clase ListaDoble
 ***********************************************************************/

#include "ListaDoble.h"

template <typename T>
ListaDoble<T>::ListaDoble(Nodo<T>* _cabeza){
    cabeza = _cabeza;
}

template <typename T>
ListaDoble<T>::ListaDoble(){
    cabeza = nullptr;
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
