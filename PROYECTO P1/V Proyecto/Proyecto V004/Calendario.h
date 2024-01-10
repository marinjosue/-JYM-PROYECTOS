#pragma once
#include <string>

using namespace std;

class Calendario{

protected:
	private:
        int anio;
        int mes;
        int dia;

	public:
        Calendario(int anio,int mes, int dia);
        void calendarioM(int, int,int );
        string  nombreMes(int );
        int calcularDiasMes(int, int);
        bool esBisiesto(int );
        int zeller(int, int);
        int marcarDia(int );

};
