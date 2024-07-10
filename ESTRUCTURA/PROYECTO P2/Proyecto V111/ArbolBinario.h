// En ArbolBinario.h

#ifndef ARBOLBINARIO_H
#define ARBOLBINARIO_H

#include <iostream>
#include <fstream>
#include <sstream>

class NodoArbol {
public:
    std::string cedula;
    NodoArbol* izquierdo;
    NodoArbol* derecho;

    NodoArbol(std::string cedula);
    ~NodoArbol();
};

class ArbolBinario {
private:
    NodoArbol* raiz;
    NodoArbol* insertarRecursivo(NodoArbol* nodo, std::string cedula);
    void inordenRecursivo(NodoArbol* nodo);
    bool buscarCedulaRecursivo(NodoArbol* nodo, const std::string& cedulaBuscada);

public:
    ArbolBinario();
    ~ArbolBinario();
    void insertar(std::string cedula);
    void imprimirEnOrden();
    void buscarCedula(const std::string& cedulaBuscada);
    void leerCedulas(const std::string& archivo);
};

#endif // ARBOLBINARIO_H
