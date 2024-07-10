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
    ListaDoble<T>(Nodo<T>* _cabeza);
    ListaDoble<T>();
    Nodo<T>* get_cabeza();
    void set_cabeza(Nodo<T>*);
    Nodo<T>* get_cola();
    void set_cola(Nodo<T>*);
    void insertar_cola(T valor);
    void imprimir();
    bool esta_vacia();
    void insertarAlInicio(Persona& persona);
    void insertarAlFinal(Persona& persona);
    void eliminarAlInicio();
    void eliminarAlFinal();
    void mostrarLista();
    bool buscarCedulaExistente(const std::string& cedula) const;
    void orden_seleccion(bool (*criterio)(T, T));
   void mostrarListaDesdeArchivo();
protected:
private:
    Nodo<T>* cabeza;
    Nodo<T>* cola;
    Nodo<T>* siguiente;
    Nodo<T>* anterior;
};

#endif // LISTADOBLE_H_INCLUDED
