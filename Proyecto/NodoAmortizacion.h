#ifndef GENERADOR_AMORTIZACION_H
#define GENERADOR_AMORTIZACION_H

#include "NodoAmortizacion.h"

class GeneradorAmortizacion {
public:
    GeneradorAmortizacion(double prestamo, double tasaInteresAnual, int numMeses);
    ~GeneradorAmortizacion();

    void generarTablaAmortizacion();
    void mostrarTablaAmortizacion() const;

private:
    double prestamo;
    double tasaInteresAnual;
    int numMeses;
    NodoAmortizacion* inicio;

    double calcularPagoMensual() const;
    void agregarNodoAmortizacion(int numeroCuota, const std::string& fechaPago,
                                 double pagoCapital, double pagoInteres, double saldoRestante);
};

#endif // GENERADOR_AMORTIZACION_H
