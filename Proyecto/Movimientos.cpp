#include "Movimientos.h"
#include "menu.h"
#include "Calendario.h"
#include <iostream>
#include <string>

using namespace std;

void Movimiento::crear_Credito (){
    double cantidad = 0.0;
    int interes = 0;
    int mes_tiempo = 0;

    string dato;
    char typeAmt;

    bool validate = true;
    while (validate) {
        printf("\n\tSISTEMA DE AMORTIGUACION FRANCES");
        cantidad = ingresar_reales("\nIngrese monto de credito a solicitar: ");
        validate = cantidad;
        if (cantidad >= 1000 && cantidad <= 100000.0) {
            validate = false;
        } else {
            validate = true;
        }
    }

    validate = true;
    while (validate) {
        mes_tiempo = ingresar_enteros("\nIngrese numero de meses a pagar: ");
        validate = mes_tiempo;
        if (mes_tiempo >= 3 && mes_tiempo <= 240) {
            validate = false;
        } else {
            validate = true;
        }
    }

    int dia, mes, anio;
    int caracteres = cin.gcount();

    validate = true;
    while (validate) {
            printf("\nIngrese la fecha de primer pago en formato (dd-mm-AAAA): \n");

            dia= ingresar_enteros("dia:");
            printf("\n");
            mes= ingresar_enteros("mes:" );
            printf("\n");
            anio =ingresar_anio("anio:\n");
            printf("\n");
            Calendario calendario(dia, mes, anio);
            calendario.calendarioM(dia, mes, anio);
            validate = false;
        }

    validate = true;
    while (validate) {
        interes = ingresar_enteros("\nIngrese Tasa de Interes %: ");
        validate = interes;
        if (interes >= 5 && interes <= 30) {
            validate = false;
        } else {
            validate = true;
        }
    }

        validate = true;
        printf( "\nAmortización FRANCESA: ");


     // AQUI LLAMAR A LA FUNCION DE LA AMORTIAZCION
       // amortizacion loan;

     //  loan = Doubt( cantidad, dato, mes_tiempo, "FRANCESA", interes);

    cout << "\n\tSE HA AGREGADO EL CRÉDITO CON ÉXITO" << endl;
    system("pause");

  }

