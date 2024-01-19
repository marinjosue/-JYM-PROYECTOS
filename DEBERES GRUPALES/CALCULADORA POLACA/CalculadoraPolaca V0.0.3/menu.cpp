
#pragma once
#include <stdio.h>
#include <conio.h>
#include <windows.h>
#include <iostream>
#include "Polaca.h"
using namespace std;

class Menu {
public:
    void MenuPrincipal() {
        Polaca polaca;
        Polaca tran;
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
                    expresion = ingresoTransformacion();
                    Pila<string> posfijo = polaca.convertirExpresionInfijaAPosfija(expresion);

                    // Invertir la pila posfija
                    Pila<string> posfijoInvertido;
                    while (!posfijo.empty()) {
                        posfijoInvertido.push(posfijo.top());
                        posfijo.pop();
                    }
                    cout << "\nExpresion en notacion posfija invertida: ";
                    posfijoInvertido.print();  // Suponiendo que tienes una función print() en tu clase Pila

                    resultado = polaca.calcular(posfijoInvertido);

                    cout << "\n El resultado es el siguiente: " << resultado << endl;
                    cout << "\nPresione Enter para continuar...";
                    system("pause");

                    break;
                }
            case 2:
                {
                    system("cls");
                    expresion = ingresoTransformacion();

                    // Call the function to convert infix to prefix
                    string prefijo = polaca.convertirExpresionInfijaAPrefija(expresion);

                    // Display the infix and prefix expressions
                    cout << "\nExpresion original: " << expresion << endl;
                    cout << "Expresion en notacion prefija: ";
                    cout << prefijo;

                    cout << "\nPresione Enter para continuar...";
                    system("pause");
                    break;
                }

            case 3:
                {
                    /*system("cls");
                    resultado = tran.calcular(posfijo);
                    cout << " El resultado es el siguiente:" << resultado << endl;
                    cout << "Presione Enter para continuar...";
                    getchar();
                    break;*/
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


string ingresoTransformacion()
{
	char c;
	string expresion = "";
	printf("Ingrese la expresion:  ");

	while ((c = _getch()) != 13) {
		if ((c >= 40 && c <= 57) || c == 97 || c == 99 || (c >= 110 && c <= 116) || c == 105 || c == 94 || c == 37) {
			printf("%c", c);
			expresion.push_back(c);
		}
		else if (c == 8 || c == 127) {
			printf("\b \b");
			expresion.pop_back();
		}
	}

	return expresion;

}

/*

int main() {
    Polaca polaca;
    string expresion;
    Operaciones op;
    Validacion v;
    bool validacion;

    do {
    	system("cls");
        try {
            mostrarMenu();
            expresion= polaca.convertirExpresionInfijaAPosfija(expresion);
            if(validacion==false){
                Pila<string> prefijo = polaca.convertirExpresionInfijaAPrefija(expresion);
                Pila<string> posfijo = polaca.convertirExpresionInfijaAPosfija(expresion);

                cout << endl << "Expresion original: " << expresion << endl;
                cout << "Expresion en notacion prefijo: ";
                prefijo.print();
                cout << "Expresion en notacion posfija: ";
                posfijo.print();

                printf("resultado:  %.10lf\n", polaca.calcular(posfijo));
            }
            cout<<endl;
            system("pause");

        } catch (const runtime_error& error) {
            cout << "Error: " << error.what() << endl;
        }
    } while (!expresion.empty());

    return 0;
}


*/

























































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

