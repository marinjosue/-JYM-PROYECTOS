#include <stdio.h>
#include <conio.h>
#include <windows.h>

void gotoxy(int x, int y) {
    COORD coord;
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void color(int foreground, int background) {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), foreground + (background * 16));
}

void menuSeleccion(const char *opciones[], int numeroOpciones, int &selec) {
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
                break;
        }
    } while (aux);
}

int main() {
    const char *opciones[] = {"Opcion 1", "Opcion 2", "Opcion 3"};
    int numeroOpciones = 3;
    int selec = 1;

    menuSeleccion(opciones, numeroOpciones, selec);

    printf("\n\nSeleccionaste la opcion %d\n", selec);

    return 0;
}
