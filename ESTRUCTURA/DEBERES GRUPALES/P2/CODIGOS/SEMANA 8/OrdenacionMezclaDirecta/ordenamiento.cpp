#include "ordenamiento.h"

Nodo* Ordenamiento::fusionarListas(Nodo* izquierda, Nodo* derecha) {
    Nodo* resultado = nullptr;

    if (izquierda == nullptr) {
        return derecha;
    } else if (derecha == nullptr) {
        return izquierda;
    }

    if (izquierda->registro->dato <= derecha->registro->dato) {
        resultado = izquierda;
        resultado->siguiente = fusionarListas(izquierda->siguiente, derecha);
    } else {
        resultado = derecha;
        resultado->siguiente = fusionarListas(izquierda, derecha->siguiente);
    }

    return resultado;
}

Nodo* Ordenamiento::ordenamientoPorMezcla(Nodo* lista) {
    if (lista == nullptr || lista->siguiente == nullptr) {
        return lista;  // Lista vacía o con un solo elemento ya está ordenada
    }

    // Dividir la lista en dos mitades
    Nodo* mitadIzquierda = lista;
    Nodo* mitadDerecha = lista->siguiente;

    while (mitadDerecha != nullptr && mitadDerecha->siguiente != nullptr) {
        lista = lista->siguiente;
        mitadDerecha = mitadDerecha->siguiente->siguiente;
    }

    mitadDerecha = lista->siguiente;
    lista->siguiente = nullptr;  // Separar las dos mitades

    // Llamadas recursivas para ordenar ambas mitades
    Nodo* izquierdaOrdenada = ordenamientoPorMezcla(mitadIzquierda);
    Nodo* derechaOrdenada = ordenamientoPorMezcla(mitadDerecha);

    // Fusionar las listas ordenadas
    return fusionarListas(izquierdaOrdenada, derechaOrdenada);
}
