/*************************
 UFA - ESPE
 * Module:  Fecha.h
 * Author:  Chiliquinga Yeshua, Marin Alquinga,Salcedo Micaela
 * Modified: domingo, 17 de diciembre de 2023
 * Purpose: Declaracion de Encabezado Fecha
 ***********************************************************************/

#ifndef FECHA_H_INCLUDED
#define FECHA_H_INCLUDED

#include <iostream>


class Fecha{
    public:
        Fecha();
        Fecha(int _anuario, int _mes, int _dia);
        Fecha(int _anuario, int _mes, int _dia, int _hora, int _minutos, int _segundos);
        int get_anuario();
        void set_anuario(int);
        int get_mes();
        void set_mes(int);
        int get_dia();
        void set_dia(int);
        int get_hora();
        void set_hora(int);
        bool es_dia_habil();
        bool es_feriado();
        bool es_finde();
        std::string to_string();
        void imprimir();
        void imprimir_feriados(int anio);
        int obtenerAnioActual();
        std::string obtenerFechaHoraActual();


    protected:

    private:
        int dia;
        int mes;
        int anuario;
        int hora;
        int minutos;
        int segundos;
};

#endif // FECHA_H_INCLUDED

