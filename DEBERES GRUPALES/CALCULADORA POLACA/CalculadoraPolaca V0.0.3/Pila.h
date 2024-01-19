#pragma once
#include "Nodo.h"

template <class T>
class Pila {
private:
    Nodo<T>* topNode;

public:
    Pila();
    ~Pila();
    T top() const;
    T pop();
    bool empty() const;
    void push(const T&);
    int size() const;
    void print() const;
    T peek() const;

};

