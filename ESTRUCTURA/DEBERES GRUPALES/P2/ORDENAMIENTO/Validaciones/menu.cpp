/*************************
            UFA - ESPE
 * Module:  menu.cpp
 * Author:  Chiliquinga Yeshua, Marin Alquinga,Salcedo Micaela
 * Modified: domingo, 17 de diciembre de 2023
 * Purpose: Implementacion de clase menu
 ***********************************************************************/
#include <stdio.h>
#include <conio.h>
#include <windows.h>
#include "menu.h"
#include "Persona.h"
#include "ListaDoble.cpp"



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

    Persona gestorPersonas;
    ListaDoble <Persona*> listaPersonas;

    bool aux = true;

    const char *titulo ="\t\tREGISTRO DE PERSONAS";
    const char *opciones[] =
    {"\t\tInsertar datos a la lista por la cabeza",
    "\t\tInsertar datos a la lista por la cola",
    "\t\tImprimir datos de la lista",
    "\t\tEliminar dato de la lista por la cola",
    "\t\tEliminar dato de la lista por la cabeza",
    "\t\tSalir"};
    int numeroOpciones = 6;
    int selec = 1;
    do{
    menuSeleccion(titulo,opciones, numeroOpciones, selec);
     switch (selec) {
                    case 1:
                        {
                        system("cls");
                        Persona nuevaPersona = Persona::ingresarPersona();
                        listaPersonas.insertarAlInicio(nuevaPersona);
                        system("pause");
                        break;
                        }

                    case 2:
                     {
                        system("cls");
                        Persona nuevaPersona = Persona::ingresarPersona();
                        listaPersonas.insertarAlFinal(nuevaPersona);
                        system("pause");
                        break;
                        }
                    case 3:
                        system("cls");
                        listaPersonas.mostrarLista();
                        system("pause");
                        break;
                    case 4:
                        system("cls");
                        listaPersonas.eliminarAlFinal();
                        system("pause");
                        break;
                    case 5:
                        system("cls");
                        listaPersonas.eliminarAlInicio();
                        system("pause");
                        break;
                    case 6:
                        system("cls");
                        printf("\n");
                        printf("Gracias por su tiempo!");
                        printf("\n");
                        aux = false;
                        break;
                }
        } while (aux);
}

Persona Persona::ingresarPersona() {
   ListaDoble <Persona*> lista;
    std::string newCedula, newNombre, newApellido, newId;

    // Input and validation for Cédula
    do {
        newCedula = ingresar_numeros_como_string("\nIngrese el numero de cedula: ");

        if (validarCedula(newCedula)) {
            // Check if the Cédula already exists in the ListaDoble
            if (lista.buscarCedulaExistente(newCedula)) {
                cout << "\nLa cedula ingresada ya existe. Vuelva a intentarlo." << endl;
            } else {
                break; // Cédula is valid and not duplicate
            }
        } else {
            cout << "\nLa cedula ingresada es invalida. Vuelva a intentarlo." << endl;
        }
    } while (true);

    // Input for Nombre and Apellido
    newNombre = mayusculas_primeras(ingresar_alfabetico_con_un_espacio("\nIngrese el nombre: "));
    newApellido = mayusculas_primeras(ingresar_alfabetico_con_un_espacio("\nIngrese el apellido: "));

    // Automatically generate the ID using the member function of ListaDoble
newId = Persona::generarSiguienteId();
  std::cout << "\nSu id unico es: "<< newId << std::endl;
    // Crear y retornar un objeto Persona con los valores ingresados
    return Persona(newNombre, newApellido, newCedula, newId);
}

