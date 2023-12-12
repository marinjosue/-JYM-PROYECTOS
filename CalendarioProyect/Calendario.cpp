#include <stdio.h>
#include "Calendario.h"


void Calendario::calendarioM(int anio){

	for (int mes = 1 ; mes<=12 ; mes++){

		cout<<"Mes: " <<nombreMes(mes)<<"\n";
		cout<< "Dom Lun Mar Mie Jue Vie Sab \n";
		int z= zeller(anio,mes);
		for(int i=0;i<z;i++){

			cout<<"    ";
		}
		int diaMes=calcularDiasMes(anio,mes);
		for(int dia=1;dia<=diaMes;dia++){
                if(dia==marcarDia(dia)){
                    dia=printf("X");
                }else{
			printf("%3d ",dia);}
			z++;
			if(z % 7==0) {
				cout<< "\n";

			}
		}cout<< "\n\n";
	}

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

































Calendario::Calendario(int a,int m, int d)
{
    anio = a;
    mes = m;
    dia=d;
}




