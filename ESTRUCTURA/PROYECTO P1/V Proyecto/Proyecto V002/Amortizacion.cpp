#include "Amortizacion.h"
#include <iostream>
#include <iomanip>

int Amortizacion::getAnio(void) {
    return anio;
}

void Amortizacion::setAnio(int newAnio) {
    anio = newAnio;
}

int Amortizacion::getSaldoInicial(void) {
    return saldoInicial;
}

void Amortizacion::setSaldoInicial(int newSaldoInicial) {
    saldoInicial = newSaldoInicial;
}

double Amortizacion::getInteres(void) {
    return interes;
}

void Amortizacion::setInteres(double newInteres) {
    interes = newInteres;
}

double Amortizacion::getAmortizacion(void) {
    return calculo_amortizacion;
}

void Amortizacion::setAmortizacion(double newAmortizacion) {
    calculo_amortizacion = newAmortizacion;
}

double Amortizacion::getPago(void) {
    return pago;
}

void Amortizacion::setPago(double newPago) {
    pago = newPago;
}

double Amortizacion::getSaldoFinal(void) {
    return saldo_Final;
}

void Amortizacion::setSaldoFinal(double newSaldoFinal) {
    saldo_Final = newSaldoFinal;
}

int Amortizacion::getDia(void) {
    return dia;
}

void Amortizacion::setDia(int newDia) {
    dia = newDia;
}

int Amortizacion::getMes(void) {
    return mes;
}

void Amortizacion::setMes(int newMes) {
    mes = newMes;
}

Amortizacion::Amortizacion() {
}

double Amortizacion::calculoInteres(double saldoFinal, double interes) {
    return saldoFinal * (interes / 100);
}

double Amortizacion::calculoAmortizacion(double prestamo, double cuotas) {
    return prestamo / cuotas;
}

double Amortizacion::calculoPago(double interes, double amortizacion) {
    return interes + amortizacion;
}

double Amortizacion::saldoFinal(double saldoInicial, double amortizacion) {
    return saldoInicial - amortizacion;
}

void Amortizacion::generarTablaAmortizacion(int numMeses) {
    // Muestra el encabezado de la tabla
    std::cout << std::setw(5) << "N" << std::setw(15) << "Día" << std::setw(15) << "Capital"
              << std::setw(15) << "Interés" << std::setw(15) << "Total Restante" << std::endl;

    // Calcula y muestra las filas de la tabla de amortización
    double saldoRestante = saldoInicial;
    for (int n = 1; n <= numMeses; ++n) {
        double pagoInteres = saldoRestante * (interes / 100);
        double pagoCapital = calculoAmortizacion(saldoRestante, numMeses - n + 1);
        double pagoMensual = pagoInteres + pagoCapital;

        saldoRestante -= pagoCapital;

        // Mostrar datos de la fila
        std::cout << std::setw(5) << n << std::setw(15) << "1" << std::setw(15)
                  << std::fixed << std::setprecision(2) << pagoCapital << std::setw(15) << pagoInteres
                  << std::setw(15) << saldoRestante << std::endl;
    }
}
