// En ArbolBinario.cpp

#include "ArbolBinario.h"

// Implementación de la clase NodoArbol
NodoArbol::NodoArbol(std::string cedula) : cedula(cedula), izquierdo(nullptr), derecho(nullptr) {}

NodoArbol::~NodoArbol() {
    delete izquierdo;
    delete derecho;
}

// Implementación de la clase ArbolBinario
ArbolBinario::ArbolBinario() : raiz(nullptr) {}

ArbolBinario::~ArbolBinario() {
    delete raiz;
}

void ArbolBinario::insertar(std::string cedula) {
    raiz = insertarRecursivo(raiz, cedula);
}

NodoArbol* ArbolBinario::insertarRecursivo(NodoArbol* nodo, std::string cedula) {
    if (nodo == nullptr) {
        return new NodoArbol(cedula);
    }

    if (cedula < nodo->cedula) {
        nodo->izquierdo = insertarRecursivo(nodo->izquierdo, cedula);
    } else if (cedula > nodo->cedula) {
        nodo->derecho = insertarRecursivo(nodo->derecho, cedula);
    }

    return nodo;
}

void ArbolBinario::imprimirEnOrden() {
    inordenRecursivo(raiz);
}

void ArbolBinario::inordenRecursivo(NodoArbol* nodo) {
    if (nodo != nullptr) {
        inordenRecursivo(nodo->izquierdo);
        std::cout << nodo->cedula << std::endl;
        inordenRecursivo(nodo->derecho);
    }
}

void ArbolBinario::buscarCedula(const std::string& cedulaBuscada) {
    if (buscarCedulaRecursivo(raiz, cedulaBuscada)) {
        std::cout << "Cuenta encontrada: " << cedulaBuscada << std::endl;
    } else {
        std::cout << "La cuenta " << cedulaBuscada << " no se encontro." << std::endl;
    }
}

bool ArbolBinario::buscarCedulaRecursivo(NodoArbol* nodo, const std::string& cedulaBuscada) {
    if (nodo == nullptr) {
        return false;
    }

    if (nodo->cedula == cedulaBuscada) {
        return true;
    }

    if (cedulaBuscada < nodo->cedula) {
        return buscarCedulaRecursivo(nodo->izquierdo, cedulaBuscada);
    } else {
        return buscarCedulaRecursivo(nodo->derecho, cedulaBuscada);
    }
}

void ArbolBinario::leerCedulas(const std::string& archivo) {
    std::ifstream file(archivo);
    std::string cedula;

    if (file.is_open()) {
        while (file >> cedula) {
            insertar(cedula);
        }
        file.close();
    } else {
        std::cerr << "No se pudo abrir el archivo: " << archivo << std::endl;
    }
}
