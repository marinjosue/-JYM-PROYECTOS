#pragma once
#include <string>
#include "Operaciones.h"
#include "Pila.cpp"
#include "Nodo.cpp"

using namespace std;

class Polaca {
public:
	Polaca(void);
	bool isOperador(char);
	bool isFuncion(char);
	bool isOperadorStr(string);
	bool isFuncionStr(string);
	int obtenerPrecedencia(string);
	string convertirExpresionInfijaAPrefija(string);
	Pila<string> convertirExpresionInfijaAPosfija(string);
	double calcular(Pila<string>&);
	string reverso(string);
	bool validarString(string);
	string postFix1(string infix);
	int esOperador(char ch);
	int prioridades(char ch);
	
};


