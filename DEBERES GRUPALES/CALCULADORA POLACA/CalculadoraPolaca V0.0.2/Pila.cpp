#include "Pila.h"

template<class T>
Pila<T>::Pila()
{
    this->ultimo = nullptr;
}

template<class T>
Pila<T>::~Pila()
{
    while (ultimo)
        Pop();
}

template<class T>
void Pila<T>::Push(T valor)
{
    Nodo<T>* nuevo = new Nodo<T>(valor, ultimo);
    ultimo = nuevo;
}

template<class T>
T Pila<T>::Pop()
{
    Nodo<T>* nodo = ultimo;
    T valor{};
    if (!ultimo) {
        return {};
    }
    ultimo = ultimo->getSiguiente();
    valor = nodo->getValor();
    delete nodo;
    return valor;
}

template<class T>
T Pila<T>::Peek()
{
    T valor{};
    if (!ultimo) {
        return 0;
    }
    valor = ultimo->getValor();
    return valor;
}

template<class T>
bool Pila<T>::isEmpty()
{
    return !ultimo;
}

// Explicit instantiation for supported types
template class Pila<char>;
template class Pila<float>;
// Add other instantiations as needed
