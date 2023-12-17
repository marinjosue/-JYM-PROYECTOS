#include "GeneradorAmortizacion.h"
#include <cmath>

GeneradorAmortizacion::GeneradorAmortizacion(double prestamo, double tasaInteresAnual, int numMeses)
    : prestamo(prestamo), tasaInteresAnual(tasaInteresAnual), numMeses(numMeses), inicio(nullptr) {}

GeneradorAmortizacion::~GeneradorAmortizacion() {
    while (inicio != nullptr) {
        NodoAmortizacion* temp = inicio;
        inicio = inicio->siguiente;
        delete temp;
    }
}

void GeneradorAmortizacion::generarTablaAmortizacion() {
    double tasaInteresMensual = tasaInteresAnual / 12;
    double pagoMensual = calcularPagoMensual();
    double saldoRestante = prestamo;

    for (int n = 1; n <= numMeses; ++n) {
        double pagoInteres = saldoRestante * tasaInteresMensual;
        double pagoCapital = pagoMensual - pagoInteres;

        saldoRestante -= pagoCapital;

        // Puedes ajustar la forma de obtener la fecha de pago según tus necesidades
        std::string fechaPago = "2023-" + (n < 10 ? "0" : "") + std::to_string(n) + "-01";

        agregarNodoAmortizacion(n, fechaPago, pagoCapital, pagoInteres, saldoRestante);
    }
}

void GeneradorAmortizacion::mostrarTablaAmortizacion() const {
    NodoAmortizacion* actual = inicio;

    std::cout << std::setw(5) << "N" << std::setw(15) << "Fecha de Pago" << std::setw(8) << "Día"
              << std::setw(15) << "Capital" << std::setw(15) << "Interés" << std::setw(20) << "Total Restante"
              << std::endl;

    while (actual != nullptr) {
        std::cout << std::setw(5) << actual->numeroCuota << std::setw(15) << actual->fechaPago
                  << std::setw(8) << "1" << std::setw(15) << std::fixed << std::setprecision(2)
                  << actual->pagoCapital << std::setw(15) << actual->pagoInteres
                  << std::setw(20) << actual->saldoRestante << std::endl;

        actual = actual->siguiente;
    }
}

double GeneradorAmortizacion::calcularPagoMensual() const {
    return prestamo * (tasaInteresAnual / 12 * std::pow(1 + tasaInteresAnual / 12, numMeses)) /
           (std::pow(1 + tasaInteresAnual / 12, numMeses) - 1);
}

void GeneradorAmortizacion::agregarNodoAmortizacion(int numeroCuota, const std::string& fechaPago,
                                                     double pagoCapital, double pagoInteres, double saldoRestante) {
    NodoAmortizacion* nuevoNodo = new NodoAmortizacion(numeroCuota, fechaPago, pagoCapital, pagoInteres, saldoRestante);

    if (inicio == nullptr) {
        inicio = nuevoNodo;
    } else {
        NodoAmortizacion* actual = inicio;
        while (actual->siguiente != nullptr) {
            actual = actual->siguiente;
        }

        actual->siguiente = nuevoNodo;
        nuevoNodo->anterior = actual;
    }
}
