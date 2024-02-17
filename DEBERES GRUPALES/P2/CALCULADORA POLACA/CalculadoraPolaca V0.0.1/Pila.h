#pragma once
#include "Nodo.h"
#include <iostream>
template<class T>
class Pila
{
public: 
	Pila();
	~Pila();
	void Push(T);
	T Pop();
	T Peek();
	bool isEmpty();
private:
	Nodo <T>* ultimo;

};

template<class T>
inline Pila<T>::Pila()
{
	this->ultimo = NULL;
}

template<class T>
inline Pila<T>::~Pila()
{
	while (ultimo) Pop();
}

template<class T>
inline void Pila<T>::Push(T valor)
{
	Nodo<T> *nuevo = new Nodo<T>(valor,ultimo);
	
	ultimo = nuevo;
}

template<class T>
inline T Pila<T>::Pop()
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
inline T Pila<T>::Peek()
{
	T valor{};
	if (!ultimo) {
		return 0;
	}
	valor = ultimo->getValor();
	return valor;
}

template<class T>
inline bool Pila<T>::isEmpty()
{	
	bool estado = false;
	if (!ultimo) {
		estado = true;
	}
	return estado;
}
