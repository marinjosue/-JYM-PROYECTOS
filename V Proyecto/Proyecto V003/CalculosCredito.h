/*************************
 UFA - ESPE
 * Module:  CalculosCredito.cpp
 * Author:  Chiliquinga Yeshua, Marin Alquinga,Salcedo Micaela
 * Modified: domingo, 17 de diciembre de 2023
 * Purpose: Implementacion de clase CalculosCredito
 *************************/

#ifndef CALCULOSCREDITO_H_INCLUDED
#define CALCULOSCREDITO_H_INCLUDED

#include "ListaDoble.h"

class CalculosCredito{
    public:
        CalculosCredito(double);
        double calcular_valor_cuotas(int, double);
        void calcular_valor_intereses(int, double, double, ListaDoble<double>*);
        void calcular_capitales_pagados(double, ListaDoble<double>*, Nodo<double>*);
        void calcular_saldos_restantes(double, double, ListaDoble<double>*, Nodo<double>*);
    private:
        double tasa_interes;
    protected:
};


#endif // CALCULOSCREDITO_H_INCLUDED
