#pragma once
#include <iostream>

using namespace std;

template <class T>
class Nodo {
private:
    T data;
    Nodo<T>* next;

public:
    Nodo(const T&);
    T getData(void) const;
    Nodo<T>* getNext(void) const;
    void setNext(Nodo<T>*);
    
};

