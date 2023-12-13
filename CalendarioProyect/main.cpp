#include "Calendario.cpp"
#include<stdio.h>

int main(){
int anio=2023;
int mes=1;
int dia=2;
  // Cr;ea un objeto de la clase Calendario
  Calendario calendario(anio, mes, dia); // Introduce el año, mes y día actual

  // Llama al método calendario para imprimir el calendario del año actual

  calendario.calendarioM(anio);
  //calendario.marcarDia(dia);

  return 0;

	system("pause");




}
