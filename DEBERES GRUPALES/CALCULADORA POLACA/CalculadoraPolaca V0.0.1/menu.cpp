
#pragma once
#include <stdio.h>
#include <conio.h>
#include <windows.h>
#include <iostream>
#include "Transformacion.h"
using namespace std;

class Menu {
public:
    void MenuPrincipal() {
        Transformacion tran;
        ingresoDatos ing;
        string expresion, post, pref;
        float resultado = 0.0;
        int op = 0;
        bool aux = true;
            string ecuacion;
            const char *titulo = "\t\t<<<<<EVALUADOR DE EXPRESIONES>>>>>";
            const char *opciones[] =
            {
                "\t\tINFIJO A POSTFIJO ",
                "\t\tINFIJO A PREFIJO  ",
                "\t\tCALCULAR  ",
                "\t\tSALIR  ",
            };
    int numeroOpciones = 4;
    int selec = 1;
        do {
                 menuSeleccion(titulo, opciones, numeroOpciones, selec);
        switch (selec) {
            case 1:
                {
                    system("cls");
                    expresion = ing.ingresoTransformacion();
                    post = tran.postFix(expresion);
                    cout << "\n";
                    cout << "\n EXPRESION CONVERTIDA A POSTFIJA: " << post << endl;
                     resultado = tran.calcular(expresion, post);
                    cout << "El resultado es el siguiente:" << resultado << endl;
                    cout << "\nPresione Enter para continuar...";
                    getchar();
                    getchar();
                    break;
                }
            case 2:
                {   
                    system("cls");
                    expresion = ing.ingresoTransformacion();
                    if (tran.validarString(expresion)) {
                        pref = tran.preFix(expresion);
                    }
                    cout << "\n";
                    cout << "\n EXPRESION CONVERTIDA A PREFIJA:" << pref << endl;
                    pref = "";
                    resultado = tran.calcular(expresion, post);
                    cout << "El resultado es el siguiente:" << resultado << endl;
                    cout << "\nPresione Enter para continuar...";
                    getchar();
                    getchar();
                    break;
                }
            case 3:
                {
                    system("cls");
                    resultado = tran.calcular(expresion, post);
                    cout << "El resultado es el siguiente:" << resultado << endl;
                    cout << "Presione Enter para continuar...";
                    getchar();
                    getchar();
                    break;
                }            
            case 4:
                {    system("cls");
                    exit(1);
                    cout << "Presione Enter para continuar...";
                    getchar();
                    getchar();
                    break;
                }
                
             } 
        }while (aux);
    }


void gotoxy(int x, int y) {
    COORD coord;
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void color(int foreground, int background) {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), foreground + (background * 16));
}

void menuSeleccion(const char *titulo, const char *opciones[], int numeroOpciones, int &selec) {
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


};

