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
    void insertarAlFinal(Persona& persona);
    void eliminarAlFinal();
    bool buscarCedulaExistente(const std::string& cedula) const;
    void orden_seleccion(bool (*criterio)(T, T));
   void mostrarListaDesdeArchivo();
   void guardarEnArchivo(const std::string& nombreArchivo);
   void cargarDesdeArchivo(const std::string& nombreArchivo);
   Nodo<T>* begin() const {
        return cabeza;
    }

    // Función para proporcionar el iterador de final para el bucle for basado en rango
    Nodo<T>* end() const {
        return nullptr;  // Puedes necesitar ajustar esto según tu implementación específica
    }
protected:
private:
    Nodo<T>* cabeza;
    Nodo<T>* cola;
    Nodo<T>* siguiente;
    Nodo<T>* anterior;
};

#endif // LISTADOBLE_H_INCLUDED
