#include<stdio.h>
#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <iostream>

using namespace std;

class Calendario
{

	private:
	int anio;
	int mes;
	int dia;

	protected:

		public:
	Calendario(int anio,int mes, int dia);
	void calendarioM(int );
	string  nombreMes(int );
	int calcularDiasMes(int, int);
	bool esBisiesto(int );
	int zeller(int, int);
	int marcarDia(int );






};
