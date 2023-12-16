#include <stdio.h>
#include <conio.h>
#include <windows.h>
#include "menu.h"


void Menu::gotoxy(int x, int y) {
    COORD coord;
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void Menu::color(int foreground, int background) {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), foreground + (background * 16));
}

void Menu::submenu1() {
    // Lógica para el Submenú 1
    printf("\Menu 1");
    printf("\n");
    system("pause");
}

void Menu::submenu2() {
    // Lógica para el Submenú 2
    printf("\nMenu 2");
    printf("\n);
    system("pause");
}

void Menu::menuSeleccion(const char *opciones[], int numeroOpciones, int &selec) {
    int tecla;
    bool aux = true;

    do {
        system("cls");
        gotoxy(30, 2);
        printf("MENU DE OPCIONES");

        for (int i = 0; i < numeroOpciones; i++) {
            gotoxy(30, 5 + i);
            if ((i + 1) == selec) {
                color(3, 10);  // Highlighted color
                printf("%s", opciones[i]);
                color(15, 0);  // Reset color
            } else {
                printf("%s", opciones[i]);
            }
        }

        do {
            fflush(stdin);
            tecla = getch();
        } while ((tecla != 72) && (tecla != 80) && (tecla != 13));  // Arrow up, arrow down, enter

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
                switch (selec) {
                    case 1:
                        submenu1();  // Llamada al Submenú 1
                        break;
                    case 2:
                        submenu2();  // Llamada al Submenú 2
                        break;
                    // Puedes agregar más casos para otras opciones
                }
                break;
        }
    } while (aux);
}

void Menu::imprimirMenu() {
    const char *opciones[] = {"Opcion1", "Otra opcion", "Otra opcion", "Salir"};
    int numeroOpciones = 4;
    int selec = 1;
    menuSeleccion(opciones, numeroOpciones, selec);
}
