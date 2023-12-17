#include "Movimientos.h"
#include "Calendario.h"
#include "menu.h"
#include <iostream>
#include <string>

using namespace std;

void Movimiento::crear_Credito (){
    double amount = 0.0;
    int interest = 0;
    int months = 0;

    string date;
    char typeAmt;

    bool validate = true;
    while (validate) {
        amount = ingresar_reales("\nIngrese monto de credito a solicitar: ");
        validate = amount;
        if (amount >= 1000 && amount <= 100000.0) {
            validate = false;
        } else {
            printf("hola");
            validate = true;
        }
    }

    validate = true;
    while (validate) {
        months = ingresar_enteros("\nIngrese numero de meses a pagar: ");
        validate = months;
        if (months >= 3 && months <= 240) {
            validate = false;
        } else {
            validate = true;
        }
    }

    // Corregido, inicializar date como cadena vacía
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
        interest = ingresar_enteros("\nIngrese Tasa de Interes %: ");
        validate = interest;
        if (interest >= 5 && interest <= 30) {
            validate = false;
        } else {
            validate = true;
        }
    }

    printf("\t\tAmortizacion Tipo Francesa");



    cout << "\n\tSE HA AGREGADO EL CRÉDITO CON ÉXITO" << endl;
    system("pause");

  }
