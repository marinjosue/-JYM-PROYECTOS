/*************************
 UFA - ESPE
 * Module:  ListasDoble.cpp
 * Author:  Chiliquinga Yeshua, Marin Alquinga,Salcedo Micaela
 * Modified: domingo, 17 de diciembre de 2023
 * Purpose: Implementacion de clase ListaDoble
 ***********************************************************************/

#include "ListaDoble.h"

template <typename T>
ListaDoble<T>::ListaDoble(){
    cabeza = nullptr;

}


template <typename T>
void ListaDoble<T>::insertarAlInicio(Persona* persona){
    Nodo<T>* nuevo_nodo;

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

template <typename T>
void ListaDoble<T>::mostrarLista(){

}

template <typename T>
bool ListaDoble<T>::esta_vacia(){
    return (cabeza == nullptr);
}
