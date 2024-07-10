#include "Amortizacion.h"
#include "Nodo.h"
#include <iostream>
#include <iomanip>


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

void Amortizacion::insertarNodo(Nodo* nuevoNodo) {
    if (!cabeza) {
        cabeza = nuevoNodo;
    } else {
        Nodo* actual = cabeza;
        while (actual->siguiente) {
            actual = actual->siguiente;
        }
        actual->siguiente = nuevoNodo;
        nuevoNodo->anterior = actual;
    }
}

 Amortizacion::Amortizacion() {
    cabeza=nullptr;
 }


void Amortizacion::generarTablaAmortizacion(int numMeses) {
    std::cout << std::setw(5) << "N" << std::setw(15) << "Día" << std::setw(15) << "Capital"
              << std::setw(15) << "Interés" << std::setw(15) << "Total Restante" << std::endl;

    // Verificar si la cabeza es nullptr antes de acceder a sus miembros
    if (!cabeza) {
        std::cout << "No hay datos para generar la tabla de amortización." << std::endl;
        return;
    }

    Nodo* actual = cabeza;
    double saldoRestante = actual->saldoRestante;

    int n = 1;
    while (actual && n <= numMeses) {
        double pagoInteres = actual->interes* saldoRestante / 100;
        double pagoCapital = calculoAmortizacion(saldoRestante, numMeses - n + 1);
        double pagoMensual = pagoInteres + pagoCapital;

        saldoRestante -= pagoCapital;

        // Mostrar datos de la fila
        std::cout << std::setw(5) << n << std::setw(15) << n << std::setw(15)
                  << std::fixed << std::setprecision(2) << pagoCapital << std::setw(15) << pagoInteres
                  << std::setw(15) << saldoRestante << std::endl;

        // Mover al siguiente nodo si existe
        actual = actual->siguiente;
        ++n;
    }
}


