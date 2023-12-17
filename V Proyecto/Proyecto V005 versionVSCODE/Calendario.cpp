#include<stdio.h>
#include <cstring>
#include <iostream>
#include "Calendario.h"

void Calendario:: calendarioM(int dia, int mes, int anio){
  if (mes < 1 || mes > 12 || anio < 2000|| anio > 2024) {
    printf("\nFecha incorrecta: el mes o el anio están fuera de rango.");
    return;
  }

  int diasMes = calcularDiasMes(anio, mes);
  if (dia < 1 || dia > diasMes) {
    printf("\nFecha incorrecta: el dia no puede ser mayor que el numero de dias del mes.");
    return;
  }

  if (mes == 2 && !esBisiesto(anio) && dia > 28) {
    printf("\n Fecha incorrecta: el anio no es bisiesto y febrero no tiene tantos dias.");
    return;
  }

//    ...........................................................................................
  diaFestivo(zeller(anio,mes,dia));
  printf("\nFecha correcta: %d/%d/%d", dia, mes, anio);
  feriado(dia,mes);
}
string  Calendario::nombreMes(int mes){

	switch(mes){
		case 1: return "Enero";
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

int Calendario::zeller(int anio, int mes, int dia){
  int a=(14-mes)/12;
  int y = anio - a ;
  int m = mes +12*a-2;
  int d=(dia+y+y/4-y/100+y/400+(31*m)/12)%  7;
  return d;
}
void Calendario::diaFestivo(int posicion_dia){
  // Devolvemos true si la posición es 0 o 6, que son domingo o sábado.
  if (posicion_dia == 0|| posicion_dia == 6) cout << "Incorrecto";
  else if(posicion_dia == 1) cout<<"      .";
  else if(posicion_dia == 2) cout<<"       .";
  else if(posicion_dia == 3) cout<<"        .";
  else if(posicion_dia == 4)  cout<<"       .";
  else if(posicion_dia == 5) cout<<"         .";


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
void Calendario::feriado(int dia, int mes)
{
	if((dia==01)&&(mes==01)){
		std::cout<<"Es anio nuevo";
	}
	else if(((dia==12)&&(mes==02))||((dia==13)&&(mes==02))){
		std::cout<<"Es carnaval";
	}
	else if((dia==29)&&(mes==3)){
		std::cout<<"Es viernes santo";
	}
	else if((dia==01)&&(mes==05)){
		std::cout<<"Es dia del trabajo";
	}
	else if((dia==24)&&(mes==05)){
		std::cout<<"Es la batalla de pichincha";
	}
		else if((dia==10)&&(mes==8)){
		std::cout<<"Es el primer grito de independencia";
	}
		else if((dia==9)&&(mes==10)){
		std::cout<<"Es la independencia de guayaquil";
}
        else if((dia==02)&&(mes==11)){
		std::cout<<"Es el dia de los difuntos";
	}
	 else if((dia==03)&&(mes==11)){
		std::cout<<"Es la independencia de cuenca";
	}
	else if((dia==25)&&(mes==12)){
		std::cout<<"Es navidad";
	}

}
int Calendario::dia_santo(int anio)
{
  int mes_de_viernes_santo;
  int dia_de_viernes_santo;

  mes_de_viernes_santo = 3 + (2 * (anio % 4)) - (anio / 400) + (anio / 100);
  dia_de_viernes_santo = (22 + (2 * mes_de_viernes_santo) - (2 * (anio % 4)) + (anio / 400) - (anio / 100)) % 7;

  if (dia_de_viernes_santo == 0) {
    dia_de_viernes_santo = 7;
  }

  return dia_de_viernes_santo;
}

int Calendario::mes_santo(int anio){
  int mes_de_viernes_santo;


  mes_de_viernes_santo = 3 + (2 * (anio % 4)) - (anio / 400) + (anio / 100);

  return mes_de_viernes_santo;

}