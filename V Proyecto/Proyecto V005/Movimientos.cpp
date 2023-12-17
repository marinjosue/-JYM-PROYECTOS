#include "Movimientos.h"
#include "Calendario.h"
#include "menu.h"
#include "Amortizacion.h"
#include <iostream>
#include <string>

using namespace std;

void Movimiento::crear_Credito() {
    double prestamoInicial = 0.0;
    double tasaInteresAnual = 0;
    int numMeses = 0;
    int dia, mes, anio;

    Amortizacion prestamo;
    bool validate = true;

    while (validate) {
        prestamoInicial = ingresar_reales("\nIngrese monto de credito a solicitar: ");
        validate = prestamoInicial;
        if (prestamoInicial >= 1000 && prestamoInicial <= 100000.0) {
            validate = false;
        } else {
            cout << "Monto no válido." << endl;
            validate = true;
        }
    }

    validate = true;
    while (validate) {
        numMeses = ingresar_enteros("\nIngrese numero de meses a pagar: ");
        validate = numMeses;
        if (numMeses >= 3 && numMeses <= 240) {
            validate = false;
        } else {
            validate = true;
        }
    }

    validate = true;
    while (validate) {
        cout << "\nIngrese la fecha de primer pago en formato (dd-mm-AAAA): \n";
        dia = ingresar_diaMes("dia:");
        cout << "\n";
        mes = ingresar_diaMes("mes:");
        cout << "\n";
        anio = ingresar_anio("anio:\n");
        cout << "\n";

        // Validar la fecha
        Calendario calendario(dia, mes, anio);

        if (calendario.calendarioM(dia, mes, anio)) {
            validate = false;
        } else {
            cout << "Fecha no válida. Por favor, ingrese una fecha válida." << endl;
        }
    }

    validate = true;
    while (validate) {
        tasaInteresAnual = ingresar_reales("\nIngrese Tasa de Interes %: ");
        validate = tasaInteresAnual;
        if (tasaInteresAnual >= 5 && tasaInteresAnual <= 30) {
            validate = false;
        } else {
            validate = true;
        }
    }

    // Configurar datos del préstamo
    prestamo.setSaldoInicial(prestamoInicial);
    prestamo.setInteres(tasaInteresAnual); // La clase espera el interés en porcentaje
    prestamo.setAmortizacion(prestamo.calculoAmortizacion(prestamoInicial, numMeses));

    // Mostrar datos de amortización antes de generar la tabla
    cout << "\nDatos del prestamo:" << endl;
    cout << "Monto del prestamo: $" << prestamo.getSaldoInicial() << endl;
    cout << "Número de meses: " << numMeses << endl;
    cout << "Fecha del primer pago: " << dia << "/" << mes << "/" << anio << endl;
    cout << "Tasa de interes: " << tasaInteresAnual << "%" << endl;
    cout << "Amortizacion mensual: $" << prestamo.getAmortizacion() << endl;

    // Generar tabla de amortización
    prestamo.generarTablaAmortizacion(numMeses);

    cout << "\n\tSE HA AGREGADO EL CRÉDITO CON ÉXITO" << endl;
    system("pause");
}
