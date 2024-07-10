/*************************
 UFA - ESPE
 * Module:  Nodo.h
 * Author:  Chiliquinga Yeshua, Marin Alquinga,Salcedo Micaela
 * Modified: domingo, 17 de diciembre de 2023
 * Purpose: Declaracion del encabezado Nodo con Template
 ***********************************************************************/

#if !defined(__Class_Diagram_1_Nodo_h)
#define __Class_Diagram_1_Nodo_h
#include "Persona.h"
template <typename T>
class Nodo
{
public:
    Nodo<T>(T _valor, Nodo* _siguiente, Nodo* _anterior);
    Nodo<T>(T _valor, Nodo* _siguiente);
    Nodo<T>();
    ~Nodo<T>();
    T get_valor();
    void set_valor(T new_valor);
    Nodo<T>* get_siguiente();
    void set_siguiente(Nodo<T>* new_siguiente);
    Nodo<T>* get_anterior();
    void set_anterior(Nodo<T>* new_anterior);
    Nodo<T>(Persona* persona) : valor(persona), siguiente(nullptr), anterior(nullptr) {}
private:
   T valor;
   Nodo<T>* siguiente;
   Nodo<T>* anterior;
};

#endif
