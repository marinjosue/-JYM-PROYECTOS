/*************************
 UFA - ESPE
 * Module:  CalculosCredito.cpp
 * Author:  Chiliquinga Yeshua, Marin Alquinga,Salcedo Micaela
 * Modified: domingo, 17 de diciembre de 2023
 * Purpose: Implementacion de clase Fecha
 ***********************************************************************/

#include <iostream>
#include "Fecha.h"
#include <ctime>
#include <iomanip>

Fecha::Fecha(){
    std::time_t tiempo_actual = std::time(nullptr);
    std::tm tm_actual = *std::localtime(&tiempo_actual);
    std::mktime(&tm_actual);

    dia = tm_actual.tm_mday;
    mes = tm_actual.tm_mon + 1;
    anuario = tm_actual.tm_year + 1900;
    hora = tm_actual.tm_hour;
    minutos = tm_actual.tm_min;
    segundos = tm_actual.tm_sec;
}

Fecha::Fecha(int _anuario, int _mes, int _dia){
    anuario = _anuario;
    set_mes(_mes);
    set_dia(_dia);
    hora = 0;
    minutos = 0;
    segundos = 1;
}

Fecha::Fecha(int _anuario, int _mes, int _dia, int _hora, int _minutos, int _segundos){
    anuario = _anuario;
    mes = _mes;
    dia = _dia;
    hora = _hora;
    minutos = _minutos;
    segundos = _segundos;
}

void Fecha::set_dia(int nuevo_dia){
    int ndias_mes_pasado = 0;

    if(nuevo_dia>28){
        if (mes==2){
            if(anuario%4!=0){
                ndias_mes_pasado = 28;
            }
            else {
                ndias_mes_pasado = (nuevo_dia > 29) ? 29 : 0;
            }
        }
        else if (((mes < 8) && mes%2!=0)||(mes >= 8) && mes%2==0){
            ndias_mes_pasado = (nuevo_dia > 31) ? 31 : 0;
        }
        else {
            ndias_mes_pasado = (nuevo_dia > 30) ? 30 : 0;
        }
    }

    dia = nuevo_dia - ndias_mes_pasado;

    if(ndias_mes_pasado>0)set_mes(mes+1);
}


std::string Fecha::to_string(){
    std::ostringstream oss;
        oss << std::setfill('0') << std::setw(2) << dia << "/";
        oss << std::setfill('0') << std::setw(2) << mes << "/";
        oss << anuario;
        return oss.str();
}

void Fecha::imprimir(){
    printf("%d", dia);
    printf("/%d", mes);
    printf("/%d", anuario);
}

bool Fecha::es_dia_habil(){
    bool habil = true;
    if(es_finde()){
        habil = false;
    }
    else if(es_feriado()){
        habil = false;
    }
    return habil;
}

bool Fecha::es_feriado(){
    bool es_feriado = false;

    if(mes==1){
        if(dia ==1) es_feriado = true;
    }
    else if(mes==2){
        if(dia == 12 || dia == 13) es_feriado = true;
    }

    else if(mes==3){
        if(dia == 29) es_feriado = true;
    }
    else if(mes==4){

    }
    else if(mes==5){
        if(dia == 1 || dia == 24) es_feriado = true;
    }
    else if(mes==6){

    }
    else if(mes==7){

    }
    else if(mes==8){
        if(dia == 10)es_feriado = true;
    }
    else if(mes==9){
         if(dia == 26)es_feriado = true;
    }
    else if(mes==10){
         if(dia == 9)es_feriado = true;
    }
    else if(mes==11){
        if(dia == 2 || dia == 3)es_feriado = true;
    }

    else if(mes==12){
        if(dia == 24 || dia == 25 || dia == 31) es_feriado = true;
    }

    return es_feriado;
}

bool Fecha::es_finde(){
    std::tm tm_fecha = {};
    tm_fecha.tm_mday = dia;
    tm_fecha.tm_mon = mes - 1;
    tm_fecha.tm_year = anuario - 1900;

    std::mktime(&tm_fecha);

    int dia_semana = tm_fecha.tm_wday;

    return (dia_semana == 0 || dia_semana == 6);
}

void Fecha::imprimir_feriados(int anio){
         printf("\n");
         printf("01 /1  /%d_Anio nuevo\n",anio);
         printf("12 /2  /%d_Carnaval\n",anio);
         printf("13 /2  /%d_Carnaval\n",anio);
         printf("29 /3  /%d_Viernes Santo\n",anio);
         printf("01 /5  /%d_Dia del trabajo\n",anio);
         printf("24 /5  /%d_Batalla de prichincha\n",anio);
         printf("10 /08 /%d_Dia de la independencia\n",anio);
         printf("09 /10 /%d_Independencia de Guayaquil\n",anio);
         printf("02 /11 /%d_Dia de los difuntos\n",anio);
         printf("03 /11 /%d_Independencia de Cuenca\n",anio);
         printf("24 /12 /%d_Navidad\n",anio);
}


int Fecha::obtenerAnioActual() {
    std::time_t tiempoActual = std::time(nullptr);
    std::tm* fechaActual = std::localtime(&tiempoActual);
    return fechaActual->tm_year + 1900;
}

int Fecha::get_anuario(){
    return anuario;
}
void Fecha::set_anuario(int nuevo_anuario){
    anuario = nuevo_anuario;
}

int Fecha::get_mes(){
    return mes;
}
void Fecha::set_mes(int nuevo_mes){
    int meses_pasados = (nuevo_mes >12) ? 12 : 0;

    mes = nuevo_mes - meses_pasados;

    if(meses_pasados>0)set_anuario(anuario+1);
}

int Fecha::get_dia(){
    return dia;
}
