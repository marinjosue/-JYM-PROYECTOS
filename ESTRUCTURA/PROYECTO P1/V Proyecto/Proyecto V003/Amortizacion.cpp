/*************************
 UFA - ESPE
 * Module:  CalculosCredito.cpp
 * Author:  Chiliquinga Yeshua, Marin Alquinga,Salcedo Micaela
 * Modified: domingo, 17 de diciembre de 2023
 * Purpose: Implementacion de clase Amortizacion
 *************************/
#include <iostream>
#include <fstream>
#include "Amortizacion.h"
#include "CalculosCredito.h"
#include "Fecha.h"
#include "ListaDoble.cpp"
#include "Nodo.cpp"
#include <iomanip>
#include <ctime> // Necesario para obtener la fecha y hora actuales

Amortizacion::Amortizacion(Credito credito_usar){
    credito = credito_usar;
    cuotas_ord = new ListaDoble<int>();
    saldos_capital= new ListaDoble<double>();
    intereses= new ListaDoble<double>();
    pagos_capital= new ListaDoble<double>();
    valor_cuotas= new ListaDoble<double>();
    fechas_pago= new ListaDoble<Fecha>();
    llenar_tabla_amortizacion();
}

void Amortizacion::llenar_tabla_amortizacion(){
    CalculosCredito calculos(15);
    double v_cuotas = calculos.calcular_valor_cuotas(credito.get_n_cuotas_pagar(), credito.get_monto());
    int n_ord = 1;
    while(n_ord<=credito.get_n_cuotas_pagar()){
        cuotas_ord->insertar_cola(n_ord);
        valor_cuotas->insertar_cola(v_cuotas);
        n_ord++;
    }

    calculos.calcular_valor_intereses(credito.get_n_cuotas_pagar(), credito.get_monto(), v_cuotas, intereses);
    calculos.calcular_capitales_pagados(v_cuotas, pagos_capital, intereses->get_cabeza());
    calculos.calcular_saldos_restantes(credito.get_monto(), v_cuotas, saldos_capital, pagos_capital->get_cabeza());
    generar_fechas_pago();
}

void Amortizacion::generar_fechas_pago(){
    Fecha fecha_sacado = credito.get_fecha_realizado();
    int ncuotas = credito.get_n_cuotas_pagar();
    int meses_gracia = credito.get_meses_gracia();
    int intervalo_pagos_mes = credito.get_intervalo_pagos_mes();
    Fecha fecha_gen = fecha_sacado;
    fecha_gen.set_mes(fecha_gen.get_mes() + meses_gracia);
    int n_gen = 0;

    while(fecha_gen.es_finde() || fecha_gen.es_feriado()){
        fecha_gen.set_dia(fecha_gen.get_dia()+1);
    }
    fechas_pago->insertar_cola(fecha_gen);
    n_gen++;

    while(n_gen<ncuotas){
        fecha_gen.set_mes(fecha_gen.get_mes() + intervalo_pagos_mes);
        while(fecha_gen.es_finde() || fecha_gen.es_feriado()){
            fecha_gen.set_dia(fecha_gen.get_dia()+1);
        }
        fechas_pago->insertar_cola(fecha_gen);
        n_gen++;
    }
}



void Amortizacion::imprimir(){
    int n_mostrados = 0;
    int n_mostrar = credito.get_n_cuotas_pagar();
    Nodo<int>* ord = cuotas_ord->get_cabeza();
    Nodo<double>* saldo_cap = saldos_capital->get_cabeza();
    Nodo<double>* interes = intereses->get_cabeza();
    Nodo<double>* capital_pag = pagos_capital->get_cabeza();
    Nodo<double>* valor_cuota = valor_cuotas->get_cabeza();
    Nodo<Fecha>* aux_fecha_pagar = fechas_pago->get_cabeza();
    Fecha fecha_pagar;
    std::cout << "N        VALOR CUOTA           CAPITAL     INTERES          SALDO             FECHA" << std::endl;
    printf("\n");
    while (n_mostrados < n_mostrar) {
        fecha_pagar = aux_fecha_pagar->get_valor();
        std::cout << ord->get_valor() << "\t|\t" << static_cast<int>(valor_cuota->get_valor() * 100) / 100.0;
        std::cout << "\t|\t" << static_cast<int>(capital_pag->get_valor() * 100) / 100.0 << "\t|\t" << static_cast<int>(interes->get_valor() * 100) / 100.0;
        std::cout << "\t|\t" << static_cast<int>(saldo_cap->get_valor() * 100) / 100.0 << "\t|\t";
        fecha_pagar.imprimir();
        printf("\n");

        ord = ord->get_siguiente();
        saldo_cap = saldo_cap->get_siguiente();
        interes = interes->get_siguiente();
        capital_pag = capital_pag->get_siguiente();
        valor_cuota = valor_cuota->get_siguiente();
        aux_fecha_pagar = aux_fecha_pagar->get_siguiente();
        n_mostrados++;
    }
}

std::string obtenerFechaHoraActual() {
    time_t tiempoActual = time(nullptr);
    tm* tmActual = localtime(&tiempoActual);

    std::string fechaHora = std::to_string(tmActual->tm_mday) + "/" +
                            std::to_string(tmActual->tm_mon + 1) + "/" +
                            std::to_string(tmActual->tm_year + 1900) + " a las " +
                            std::to_string(tmActual->tm_hour) + ":" +
                            std::to_string(tmActual->tm_min) + ":" +
                            std::to_string(tmActual->tm_sec);
    return fechaHora;
}

void Amortizacion::guardarTabla(const std::string& nombreArchivo) {
    std::ofstream archivo(nombreArchivo);

    if (!archivo.is_open()) {
        std::cerr << "Error al abrir el archivo: " << nombreArchivo << std::endl;
        return;
    }

    // Obtener la fecha y hora actual utilizando la nueva función
    std::string fechaHoraGeneracion = obtenerFechaHoraActual();

    // Imprimir la fecha y hora de generación de la tabla
    archivo << "Tabla generada el " << fechaHoraGeneracion << "\n\n";

    int n_mostrados = 0;
    int n_mostrar = credito.get_n_cuotas_pagar();
    Nodo<int>* ord = cuotas_ord->get_cabeza();
    Nodo<double>* saldo_cap = saldos_capital->get_cabeza();
    Nodo<double>* interes = intereses->get_cabeza();
    Nodo<double>* capital_pag = pagos_capital->get_cabeza();
    Nodo<double>* valor_cuota = valor_cuotas->get_cabeza();
    Nodo<Fecha>* aux_fecha_pagar = fechas_pago->get_cabeza();
    Fecha fecha_pagar;


    archivo << "N    VALOR CUOTA   CAPITAL     INTERES      SALDO      FECHA\n";

    while (n_mostrados < n_mostrar) {
        fecha_pagar = aux_fecha_pagar->get_valor();
        archivo << ord->get_valor() << "\t|\t" << std::fixed << std::setprecision(2) << valor_cuota->get_valor();
        archivo << "\t|\t" << std::fixed << std::setprecision(2) << capital_pag->get_valor() << "\t|\t" << std::fixed << std::setprecision(2) << interes->get_valor();
        archivo << "\t|\t" << std::fixed << std::setprecision(2) << saldo_cap->get_valor() << "\t|\t";
        archivo << fecha_pagar.to_string() << "\n";  // Suponiendo que el método imprimir() devuelve un string o un tipo que se pueda imprimir
        //archivo << fecha_pagar.imprimir() << "\n";

        ord = ord->get_siguiente();
        saldo_cap = saldo_cap->get_siguiente();
        interes = interes->get_siguiente();
        capital_pag = capital_pag->get_siguiente();
        valor_cuota = valor_cuota->get_siguiente();
        aux_fecha_pagar = aux_fecha_pagar->get_siguiente();

        n_mostrados++;
    }

    archivo.close();
}

Credito Amortizacion::get_credito(){
    return credito;
}

ListaDoble<int>* Amortizacion::get_cuotas_ord(){
    return cuotas_ord;
}

ListaDoble<double>* Amortizacion::get_saldos_capital(){
    return saldos_capital;
}

ListaDoble<double>* Amortizacion::get_intereses(){
    return intereses;
}

ListaDoble<double>* Amortizacion::get_pagos_capital(){
    return pagos_capital;
}

ListaDoble<double>* Amortizacion::get_valor_cuotas(){
    return valor_cuotas;
}

ListaDoble<Fecha>* Amortizacion::get_fechas_pago(){
    return fechas_pago;
}

void Amortizacion::set_credito(Credito nuevo_credito){
    credito = nuevo_credito;
}

void Amortizacion::set_cuotas_ord(ListaDoble<int>* nuevo_cuotas_ord){
    cuotas_ord = nuevo_cuotas_ord;
}

void Amortizacion::set_saldos_capital(ListaDoble<double>* nuevo_saldos_capital){
    saldos_capital = nuevo_saldos_capital;
}

void Amortizacion::set_intereses(ListaDoble<double>* nuevo_intereses){
    intereses = nuevo_intereses;
}

void Amortizacion::set_pagos_capital(ListaDoble<double>* nuevo_pagos_capital){
    pagos_capital = nuevo_pagos_capital;
}

void Amortizacion::set_valor_cuotas(ListaDoble<double>* nuevo_valor_cuotas){
    valor_cuotas = nuevo_valor_cuotas;
}

void Amortizacion::set_fechas_pago(ListaDoble<Fecha>* nuevo_fechas_pago){
    fechas_pago = nuevo_fechas_pago;
}