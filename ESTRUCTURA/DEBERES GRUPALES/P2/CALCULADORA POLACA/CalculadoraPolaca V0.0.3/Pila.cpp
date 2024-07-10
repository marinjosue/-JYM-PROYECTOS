#include "Pila.h"

template <typename T>
Pila<T>::Pila() {
    topNode = nullptr;
} 

template <typename T>
Pila<T>::~Pila() {
    while (!empty()) {
        pop();
    }
}

template <typename T>
T Pila<T>::top() const {
    if (empty()) {
        throw runtime_error("La pila esta vacia");
    }
    return topNode->getData();
}

template<class T>
T Pila<T>::pop()
{
    Nodo<T>* nodo = topNode;
    T valor{};
    if (!topNode) {
        return {};
    }
    topNode = topNode->getNext();
    valor = nodo->getData();
    delete nodo;
    return valor;
}


template <typename T>
bool Pila<T>::empty() const {
    return topNode == nullptr;
}

template <typename T>
void Pila<T>::push(const T& value) {
    Nodo<T>* newNode = new Nodo<T>(value);
    newNode->setNext(topNode);
    topNode = newNode;
}

template <typename T>
int Pila<T>::size() const {
    int count = 0;
    Nodo<T>* current = topNode;

    while (current != nullptr) {
        count++;
        current = current->getNext();
    }

    return count;
}

template <typename T>
void Pila<T>::print() const {
    Nodo<T>* current = topNode;

    while (current != nullptr) {
        cout << current->getData();
        current = current->getNext();
    }

   cout << endl;
}

template <typename T>
T Pila<T>::peek() const {
    if (empty()) {
        throw runtime_error("La pila esta vacia");
    }
    return topNode->getData();
}
