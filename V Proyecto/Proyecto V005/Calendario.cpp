#include <stdio.h>

#include "Calendario.h"


bool Calendario::calendarioM(int dia, int mes, int anio) {
    if (mes < 1 || mes > 12 || anio < 2000 || anio > 2024) {
        printf("\nFecha incorrecta: el mes o el anio están fuera de rango.");
        return false;  // Cambiado a false
    }

    int diasMes = calcularDiasMes(anio, mes);
    if (dia < 1 || dia > diasMes) {
        printf("\nFecha incorrecta: el dia no puede ser mayor que el numero de dias del mes.");
        return false;  // Cambiado a false
    }

    if (mes == 2 && !esBisiesto(anio) && dia > 28) {
        printf("\n Fecha incorrecta: el anio no es bisiesto y febrero no tiene tantos dias.");
        return false;  // Cambiado a false
    }

    // Devolver true solo si la fecha es válida
    return true;
}

string  Calendario::nombreMes(int mes){

	switch(mes){
		case 1: return "";
		case 2: return "Febrero";
		case 3: return "Marzo";
		case 4: return "Abril";
		case 5: return "Mayo";
		case 6: return "Junio";
		case 7: return "Julio";
		case 8: return "Agosto";
		case 9: return "Septiembre";
		case 10: return "Octubre";
		case 11: return "Noviembre";
		case 12: return "Diciembre";
	}

}

int Calendario::zeller(int anio, int mes){
	int a=(14-mes)/12;
	int y = anio-a;
	int m = mes +12*a - 2;
	int dia=1, d ;
	d=(dia+y+y/4-y/100 + y /400+ (31*m) /12) %7;
	return d;

}

int Calendario::marcarDia(int dia ) {

return dia;
}

int Calendario::calcularDiasMes(int anio,int mes) {

	if(mes==1||mes==3 || mes==5||mes==7||mes==8 || mes==10|| mes==12){

		return 31;
	}
	if(mes==2){

		if(esBisiesto(anio)){
			return 29;

		}
		else return 28;
	}

	return 30;
}

bool Calendario::esBisiesto(int anio){

	if(anio%4 !=0)return false;
	if(anio%100 !=0)return true;
	if(anio%400 !=0)return false;

	return true;
}

Calendario::Calendario(int a,int m, int d){
    anio = a;
    mes = m;
    dia=d;
}

