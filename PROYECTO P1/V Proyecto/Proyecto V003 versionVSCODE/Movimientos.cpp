#include "Movimientos.h"
#include "validaciones.h" // Incluye las funciones de validación
#include "Calendario.h"
#include <iostream>
#include <string>

using namespace std;

void Movimiento::crear_Credito (){
    double prestamoInicial = 0.0;
    double tasaInteresAnual = 0;
    int numMeses = 0;
    Amortizacion prestamo;
    bool validate = true;
    while (validate) {
        prestamoInicial = ingresar_reales("\nIngrese monto de credito a solicitar: ");
        validate = prestamoInicial;
        if (prestamoInicial >= 1000 && prestamoInicial <= 100000.0) {
            validate = false;
        } else {
            printf("hola");
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

    // Corregido, inicializar date como cadena vac�a
     int dia, mes, anio;
    int caracteres = cin.gcount();

    validate = true;
    while (validate) {
            printf("\nIngrese la fecha de primer pago en formato (dd-mm-AAAA): \n");

            dia= ingresar_diaMes("dia:");
            printf("\n");
            mes= ingresar_diaMes("mes:" );
            printf("\n");
            anio =ingresar_anio("anio:\n");
            printf("\n");
            Calendario calendario(dia, mes, anio);
            calendario.calendarioM(dia, mes, anio);
            validate = false;
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



    // Configurar datos del pr�stamo
    prestamo.setSaldoInicial(prestamoInicial);
    prestamo.setInteres(tasaInteresAnual); // La clase espera el inter�s en porcentaje
    prestamo.setAmortizacion(prestamo.calculoAmortizacion(prestamoInicial, numMeses));
    prestamo.generarTablaAmortizacion(numMeses);

    cout << "\n\tSE HA AGREGADO EL CR�DITO CON �XITO" << endl;
    system("pause");

  }
