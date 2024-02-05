/*************************
 UFA - ESPE
 * Module:  Credito.h
 * Author:  Chiliquinga Yeshua, Marin Alquinga,Salcedo Micaela
 * Modified: domingo, 17 de diciembre de 2023
 * Purpose: Implementacion del encabezado Credito
 *************************/

#ifndef CREDITO_H_INCLUDED
#define CREDITO_H_INCLUDED

#include "Fecha.h"

class Credito{
    public:
        Credito(){};
        Credito(int num_cuotas, double _monto, Fecha, double _tasa_interes);
        int get_n_cuotas_pagar();
        int get_cuotas_pagadas();
        double get_monto();
        double get_saldo();
        double get_valor_cuota();
        void set_n_cuotas_pagar(int);
        void set_cuotas_pagadas(int);
        void set_monto(double);
        void set_saldo(double);
        void set_valor_cuota(double);
        int get_meses_gracia();
        int get_intervalo_pagos_mes();
        Fecha get_fecha_realizado();
        void set_meses_gracia(int);
        void set_intervalo_pagos_mes(int);
        char* to_string();
    protected:

    private:
        int n_cuotas_pagar;
        int cuotas_pagadas;
        double tasa_interes;
        double monto;
        double saldo;
        double valor_cuota;
        int meses_gracia;
        int intervalo_pagos_mes;
        Fecha fecha_realizado;
};



#endif // CREDITO_H_INCLUDED
