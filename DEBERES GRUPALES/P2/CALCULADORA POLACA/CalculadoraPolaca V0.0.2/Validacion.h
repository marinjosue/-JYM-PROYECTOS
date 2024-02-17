#pragma once
#include <iostream>
using namespace ::std;

class Validacion
{
public:
    bool validar_Sen(string);
    bool validar_Cos(string);
    bool validar_Tan(string);
    bool validar_Pi(string);
    bool vaidar_Escritura(string);
    string texto(string, int);
    string textoCos(string, int);
    bool validarAnterior(string, int);
    bool esOperador(char);
    bool Parentesis_Balanceados(string);
    bool Parentesis_Sintaxis(string);
    bool Operadores_Sintaxis(string);
    bool validar_Ceros(string);
};