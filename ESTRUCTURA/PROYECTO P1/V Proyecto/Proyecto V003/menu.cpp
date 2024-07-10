#include <stdio.h>
#include <conio.h>
#include <windows.h>
#include "menu.h" // Incluye la clase Movimiento
#include "Amortizacion.h"
#include "validaciones.h"

using namespace std;
void Menus::gotoxy(int x, int y) {
    COORD coord;
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void Menus::color(int foreground, int background) {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), foreground + (background * 16));
}


void Menus::menuSeleccion(const char *titulo, const char *opciones[], int numeroOpciones, int &selec) {
    int tecla;
    bool aux = true;

    do {
        system("cls");
        gotoxy(15, 2);
        printf("\t\t%s",titulo);
        for (int i = 0; i < numeroOpciones; i++) {
            gotoxy(30, 5 + i);
            if ((i + 1) == selec) {
                color(15, 9);  // Highlighted color
                printf("%s", opciones[i]);
                color(15, 0); /// Highlighted color
            } else {
                printf("%s", opciones[i]);
            }
        }

        do {
            fflush(stdin);
            tecla = getch();
        } while ((tecla != 72) && (tecla != 80) && (tecla != 13));

        switch (tecla) {
            case 72:  // Up arrow
                selec--;
                if (selec < 1) {
                    selec = numeroOpciones;
                }
                aux = true;
                break;
            case 80:  // Down arrow
                selec++;
                if (selec > numeroOpciones) {
                    selec = 1;
                }
                aux = true;
                break;
            case 13:  // Enter
                aux = false;
                break;
        }
    } while (aux);
}

void Menus::Menu_Principal() {
    bool aux = true;
    const char *titulo ="\t\tTABLA DE AMORTIZACION";
    const char *opciones[] = {"\t\tCREAR CREDITO", "\t\tMOSTRAR TABLA DE AMORTIZACION", "\t\tAYUDA", "\t\tEXTRAS","\t\tSALIR"};
    int numeroOpciones = 5;
    int selec = 1;
    do{
    menuSeleccion(titulo,opciones, numeroOpciones, selec);
     switch (selec) {
                    case 1:
                        system("cls");
                        Menu_Credito();
                        system("pause");
                        break;
                    case 2:
                        system("cls");
                        //                        prestamo.generarTablaAmortizacion(months);
                        system("pause");
                        break;
                    case 3:
                        system("cls");
                        submenu2();  // Llamada al Submen� 2
                        system("pause");
                        break;
                    case 4:
                        system("cls");
                        Menu_Extras();  // Llamada al Submen� 2
                        system("pause");
                        break;
                    case 5:
                        system("cls");
                        submenu2();  // Llamada al Submen� 2
                        system("pause");
                        break;
                    // Puedes agregar m�s casos para otras opciones
                }
        } while (aux);
}

void ingresar_datos_credito(){
    system("cls");
    Fecha sacado;
    double monto=0, tasa_interes=0;
    int ncuotas=0;

    while(monto<=0 || monto > 99999999.99){
        monto = ingresar_reales("\nIngrese el monto del credito");

        if(monto<=0 || monto > 99999999.99){
            printf("El monto debe ser mayor a 0 y menor a 100M");
        }else{
            printf("                                                           ");
        }
    }
    while(ncuotas<=0 || ncuotas > 500){
        
        ncuotas = ingresar_enteros("\nIngrese el numero de cuotas a pagar del credito");

        if(ncuotas<=0 || ncuotas > 500){
            printf("El numero de cuotas debe ser mayor a 0 y menor a 500");
        }else{
            printf("                                                           ");
        }
    }
    while(tasa_interes<=0 || tasa_interes>99.99){
        tasa_interes = ingresar_reales("\nIngrese la tasa de interes del credito");

        if(tasa_interes<=0 || tasa_interes>99.99){
            printf("La tasa de interes debe ser mayor a 0 y menor a 100%");
        }else{
            printf("                                                           ");
        }
    }
    Credito credito(ncuotas, monto, sacado, tasa_interes);
    Amortizacion tabla(credito);
    printf("\n");
    tabla.imprimir();

    // Guardar la tabla en un archivo (puedes cambiar el nombre de archivo según tus necesidades)
    printf("\nTABLA GUARDADA CORRECTAMENTE");
    tabla.guardarTabla("tabla_amortizacion.txt");

    printf("\n");
    // Pausa para mostrar el mensaje y esperar la acción del usuario
    system("pause");
}


void Menus::Menu_Credito() {
    bool aux = true;
    Menus menu;
    const char *titulo="\t\tDESEA CREAR UN CREDITO:";
    const char *opciones[] = {"\t\tSI", "\t\tNO"};
    int numeroOpciones = 2;
    int selec = 1;
    do{
    menuSeleccion(titulo,opciones, numeroOpciones, selec);
     switch (selec) {
                   case 1:
                        system("cls");
                        ingresar_datos_credito();
                        menu.Menu_Credito();
                        break;
                    case 2:
                        system("cls");
                        Menu_Principal();
                        system("pause");
                        break;
        }
    } while (aux);

}

void Menus::Menu_Extras() {
    bool aux = true;

    const char *titulo="\t\tMENU EXTRAS:";
    const char *opciones[] = {"\t\tAYUDA", "\t\tIMAGEN","\t\tSALIR"};
    int numeroOpciones = 3;
    int selec = 1;
    do{
    menuSeleccion(titulo,opciones, numeroOpciones, selec);
     switch (selec) {
                   case 1:
                        system("cls");
                        Menu_Principal();
                        system("pause");
                        break;
                    case 2:

                        Menu_Principal();
                        system("pause");
                        break;
                    case 3:

                        Menu_Principal();
                        system("pause");
                        break;
        }
    } while (aux);

}

void Menus::submenu2() {
    // L�gica para el Submen� 2
    printf("\nMenu 2");
    printf("\n");
    system("pause");
}
