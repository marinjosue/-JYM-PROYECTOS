#pragma once
#include <iostream>

using namespace std;

template <class T>
class Nodo
{
private:
    T valor;
    Nodo<T>* siguiente;
public:
    Nodo(T v, Nodo<T>* sig = NULL);
    T getValor();
    Nodo<T>* getSiguiente();
    void setValor(T v);
    void setSiguiente(Nodo<T>* nodo);
};

template<class T>
inline Nodo<T>::Nodo(T v, Nodo<T>* sig)
{
    this->valor = v;
    this->siguiente = sig;
}

template<class T>
inline T Nodo<T>::getValor()
{
    return valor;
}

template<class T>
inline Nodo<T>* Nodo<T>::getSiguiente()
{
    return siguiente;
}

template<class T>
inline void Nodo<T>::setValor(T v)
{
    valor = v;
}

template<class T>
inline void Nodo<T>::setSiguiente(Nodo<T>* nodo)
{
    siguiente = nodo;
}
