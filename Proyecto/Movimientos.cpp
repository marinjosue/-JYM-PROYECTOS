#include "Movimientos.h"

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
    validate = true;
    while (validate) {
        cout << "\nIngrese la fecha de primer pago en formato (dd-mm-AAAA): "<< endl;
        cin >> date;
        // Puedes agregar validaciones adicionales para el formato de la fecha si es necesario
        // Ejemplo: verificar que la longitud sea la adecuada, que los separadores sean correctos, etc.
        validate = false;  // Se supone que la entrada es correcta; puedes agregar validaciones según tus necesidades
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

    validate = true;
    cout << "\nIngrese el tipo de Amortización (A/Aleman o cualquier otro para otro tipo): ";
    cin >> typeAmt;

    if (typeAmt == 'A' || typeAmt == 'a' || typeAmt == 'Aleman') {
        // Algoritmo de Amortización Aleman
    } else {
        // Algoritmo de Amortización Francesa u otro tipo
    }

    // Aquí deberías agregar la lógica para guardar el crédito en un archivo TXT

    cout << "\n\tSE HA AGREGADO EL CRÉDITO CON ÉXITO" << endl;
    system("pause");

  }
