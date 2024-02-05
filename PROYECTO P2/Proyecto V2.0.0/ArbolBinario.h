/***********************************************************************
 UFA - ESPE
 * Module:  ArbolBinario.h
 * Author:  Chiliquinga Yeshua, Marin Alquinga,Salcedo Micaela
 * Modified: domingo, 4 de enero de 2024
 * Purpose: Implementation of the class ArbolBinario
 ***********************************************************************/
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
    void buscarCedula(const std::string& cedulaBuscada,const std::string& nombreArchivo);
    void leerCedulas(const std::string& archivo);
    void inordenRecursivoConFlechas(NodoArbol* nodo);
};

#endif // ARBOLBINARIO_H
