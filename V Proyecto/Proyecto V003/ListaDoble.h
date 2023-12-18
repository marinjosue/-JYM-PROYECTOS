/*************************
 UFA - ESPE
 * Module:  CalculosCredito.cpp
 * Author:  Chiliquinga Yeshua, Marin Alquinga,Salcedo Micaela
 * Modified: domingo, 17 de diciembre de 2023
 * Purpose: Declaracion de clase ListaDoble
 ***********************************************************************/
#ifndef LISTADOBLE_H_INCLUDED
#define LISTADOBLE_H_INCLUDED

#include "Nodo.h"

template <typename T>
class ListaDoble
{
public:
    ListaDoble<T>(Nodo<T>* _cabeza);
    ListaDoble<T>();
    Nodo<T>* get_cabeza();
    void set_cabeza(Nodo<T>*);
    Nodo<T>* get_cola();
    void set_cola(Nodo<T>*);
    void insertar_cola(T valor);
    void imprimir();
    bool esta_vacia();

protected:
private:
    Nodo<T>* cabeza;
    Nodo<T>* cola;
};

#endif // LISTADOBLE_H_INCLUDED
