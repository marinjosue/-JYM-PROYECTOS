/***********************************************************************
 UFA - ESPE
 * Module:  Amortizacion.h
 * Author:  Chiliquinga Yeshua, Marin Alquinga,Salcedo Micaela
 * Modified: domingo, 4 de enero de 2024
 * Purpose: Implementation of the class Amortizacion
 ***********************************************************************/

#if !defined(__Amortizacion_Amortizacion_h)
#define __Amortizacion_Amortizacion_h
#include "ListaDoble.h"
#include "Credito.h"
#include "Fecha.h"

class Amortizacion
{
public:
        void llenar_tabla_amortizacion();
        void generar_fechas_pago();
        void imprimirYGuardar(const std::string& cedula);
        Amortizacion(Credito);
        Amortizacion();
        Credito get_credito();
        ListaDoble<int>* get_cuotas_ord();
        ListaDoble<double>* get_saldos_capital();
        ListaDoble<double>* get_intereses();
        ListaDoble<double>* get_pagos_capital();
        ListaDoble<double>* get_valor_cuotas();
        ListaDoble<Fecha>* get_fechas_pago();
        void set_credito(Credito nuevo_credito);
        void set_cuotas_ord(ListaDoble<int>* nuevo_cuotas_ord);
        void set_saldos_capital(ListaDoble<double>* nuevo_saldos_capital);
        void set_intereses(ListaDoble<double>* nuevo_intereses);
        void set_pagos_capital(ListaDoble<double>* nuevo_pagos_capital);
        void set_valor_cuotas(ListaDoble<double>* nuevo_valor_cuotas);
        void set_fechas_pago(ListaDoble<Fecha>* nuevo_fechas_pago);
        void guardarTabla(const std::string& nombreArchivo, const std::string& cedula,
                                const std::string& nombreCompleto, const std::string& id,
                                const std::string& Ncuenta, double monto, int ncuotas,
                                double tasa_interes);
        void ingresar_datos_credito();
        ///////////////////////////////////////////////////////////////////////////////////
       private:
        Credito credito;
        ListaDoble<int>* cuotas_ord;
        ListaDoble<double>* saldos_capital;
        ListaDoble<double>* intereses;
        ListaDoble<double>* pagos_capital;
        ListaDoble<double>* valor_cuotas;
        ListaDoble<Fecha>* fechas_pago;
        void limpiarTabla();
    protected:
};

#endif
