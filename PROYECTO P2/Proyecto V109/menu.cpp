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
#include <fstream>
#include <string>
#include <sstream>
#include <iostream>
#include "menu.h"
#include "Persona.h"
#include "ListaDoble.cpp"
#include "Nodo.h"
#include "validaciones.h"
#include "Fecha.h"
#include "Extra.h"
#include "Imagen.h"
#include "Amortizacion.h"
#include "Cuenta.cpp"
#include <iomanip>
#include "Movimientos.h"

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

void Menus::Menu_Principal(ListaDoble<Persona*> listaPersonas) {
     validaciones valida;
     Fecha f;
    int anioActual = f.obtenerAnioActual();
     bool aux = true;
    std::string nombreArchivo = "tabla_amortizacion.txt";
    const char *titulo ="\t\tPRESTAMOS";
    const char *opciones[] =
    {
     "\t\t[1]USUARIO",
     "\t\t[2]CUENTA",
     "\t\t[3]MOVIMIENTOS",
     "\t\t[4]CREAR CREDITO",
     "\t\t[5]LEER TABLA",
     "\t\t[6]EXTRAS",
     "\t\t[7]SALIR"
      };
    int numeroOpciones = 7;
    int selec = 1;
    do{
    menuSeleccion(titulo,opciones, numeroOpciones, selec);
     switch (selec) {
                    case 1:
                        system("cls");
                        Menu_Usuario(listaPersonas);
                        system("pause");
                        break;
                    case 2:
                        system("cls");
                        Menu_Cuenta(listaPersonas);
                        system("pause");
                        break;
                    case 3:
                        system("cls");
                        Menu_Movimientos();
                        system("pause");
                        break;
                    case 4:
                        system("cls");
                        Menu_Credito(listaPersonas);
                        system("pause");
                        break;
                    case 5:
                        system("cls");
                        imprimirContenidoArchivo(nombreArchivo);
                        system("pause");
                        Menu_Principal(listaPersonas);
                        system("pause");
                        break;
                    case 6:
                        system("cls");
                        Menu_Extras(listaPersonas);
                        system("pause");
                        break;
                    case 7:
                        system("cls");
                        std::cout << "Gracias por usar el programa. Hasta luego!\n";
                        aux = false;
                        break;
                }
        } while (aux);
}

void Menus::Menu_Usuario(ListaDoble<Persona*> &listaPersonas) {
validaciones valida;
    Persona persona;
    std::string nombreArchivo2 = "Personas.txt";
    std::string ultimoIdUtilizado = Persona::obtenerUltimoIdUtilizado(nombreArchivo2);
    std::cout << "Ultimo ID utilizado: " << ultimoIdUtilizado << std::endl;
    bool aux = true;
    Menus menu;
    const char *titulo = "\t\tDESEA REGISTRAR UNA PERSONA:";
    const char *opciones[] = {
        "\t\t[1]REGISTRAR PERSONA",
        "\t\t[2]LISTADO DE PERSONAS",
        "\t\t[3]SALIR"};
    int numeroOpciones = 3;
    int selec = 1;
    do {
        menuSeleccion(titulo, opciones, numeroOpciones, selec);
        switch (selec) {
            case 1: {
                system("cls");
                Persona nuevaPersona = Persona::ingresarPersona(listaPersonas);
                system("pause");
                if(Menu_ConfirmarGuardar()){
                    nuevaPersona.guardarEnArchivo("Personas.txt");
                }
                Menu_Usuario(listaPersonas);
                break;
            }
            case 2:
                system("cls");
                persona.mostrarRegistroPersona();
                system("pause");
                Menu_Usuario(listaPersonas);
                break;
            case 3:
                system("cls");
                Menu_Principal(listaPersonas);
                system("pause");
                break;
        }
    } while (aux);
}

void Menus::Menu_Cuenta(ListaDoble<Persona*> &listaPersonas) {
    Cuenta cuenta;
    Persona persona;
    Movimientos movimiento;
    bool aux = true;
    const char *titulo ="\t\tCUENTAS DE CLIENTES";
    const char *opciones[] =
    {
    "\t\t[1]CREAR CUENTA",
    "\t\t[2]MOVIMIENTOS",
    "\t\t[3]BUSCAR CUENTA",
    "\t\t[4]MOSTAR USUARIOS",
    "\t\t[5]SALIR"
    };
    int numeroOpciones = 5;
    int selec = 1;
    do{
    menuSeleccion(titulo,opciones, numeroOpciones, selec);
     switch (selec) {
                     case 1: {
                        system("cls");
                        Cuenta nuevaCuenta = Cuenta::crear_cuenta();
                        std::string cedulaBuscada = nuevaCuenta.getCedula();
                        system("pause");
                        Menu_Cuenta(listaPersonas);
                        break;
                        }

                    case 2:
                     {
                        system("cls");
                        Menu_Movimientos();
                        break;
                        }
                    case 3:
                     {
                        system("cls");


                        break;
                        }
                    case 4:
                        system("cls");
                        cuenta.mostrarDatosUsuarios("Usuarios.txt");
                        system("pause");
                        Menu_Cuenta(listaPersonas);
                        break;
                    case 5:
                        system("cls");
                        Menu_Principal(listaPersonas);
                        break;
                }
        } while (aux);
}

void Menus::Menu_Movimientos(){
    
    Cuenta cuenta;
    Persona persona;
    Movimientos movimiento;
    ListaDoble<Persona*> listaPersonas;
    bool aux = true;
    const char *titulo ="\t\tMOVIMEINTOS";
    const char *opciones[] =
    {
    "\t\t[1]AVONAR",
    "\t\t[2]RETIRAR",
    "\t\t[3]BUSCAR TABLA",
    "\t\t[4]ELIMINAR",
    "\t\t[5]SALIR"
    };

    int numeroOpciones = 5;
    int selec = 1;
    do{
    menuSeleccion(titulo,opciones, numeroOpciones, selec);
     switch (selec) {
                     case 1: {
                        system("cls");
                       
                        break;
                        }

                    case 2:
                     {
                        system("cls");


                        break;
                        }
                    case 3:
                     {
                        system("cls");
                        movimiento.mostrarMovimientosPorCedula();
                        system("pause");
                        break;
                        }
                    case 4:
                        system("cls");
                       
                        break;
                    case 5:
                        system("cls");
                        Menu_Principal(listaPersonas);
                        break;
                }
        } while (aux);








}










bool Menus::Menu_ConfirmarGuardar() {
    validaciones valida;
    bool aux = true;
    Menus menu;
    const char *titulo = "\t\tDESEA GUARDAR EN EL REGISTRO?:";
    const char *opciones[] = {
        "\t\t[1]SI",
        "\t\t[2]NO"};
    int numeroOpciones = 2;
    int selec = 1;
    do {
        menuSeleccion(titulo, opciones, numeroOpciones, selec);
        switch (selec) {
            case 1: {
                system("cls");
                return 1;
                break;
            }
            case 2:
                system("cls");
                return 0;
                break;
        }
    } while (aux);
}

void Menus::Menu_Credito(ListaDoble<Persona*> listaPersonas) {
    validaciones valida;
    Amortizacion tabla;
    bool aux = true;
    Menus menu;
    const char *titulo="\t\tDESEA CREAR UN CREDITO:";
    const char *opciones[] =
    {
        "\t\t[1]SI",
        "\t\t[2]NO"
    };
    int numeroOpciones = 2;
    int selec = 1;
    do{
    menuSeleccion(titulo,opciones, numeroOpciones, selec);
     switch (selec) {
                   case 1:
                        system("cls");
                        tabla.ingresar_datos_credito();
                        menu.Menu_Credito(listaPersonas);
                        break;
                    case 2:
                        system("cls");
                        Menu_Principal(listaPersonas);
                        system("pause");
                        break;
        }
    } while (aux);

}


void Menus::Menu_Extras(ListaDoble<Persona*> listaPersonas) {

validaciones valida;
    bool aux = true;
    Imagen img("foto.bmp");
    std::string archivoOriginal = "tabla_amortizacion.txt";
    const char *titulo = "\t\tMENU EXTRAS:";
    const char *opciones[] =
    {
        "\t\[1]RESTAURAR BACKUP",
        "\t\[2]AYUDA",
        "\t\[3]IMAGEN",
        "\t\[4]SALIR"
    };
    int numeroOpciones = 4;
    int selec = 1;
    do {
        menuSeleccion(titulo, opciones, numeroOpciones, selec);
        switch (selec) {

          case 1:
           {
                system("cls");
                std::cout << "Archivos TXT en la carpeta 'backup':" << std::endl;
                std::vector<std::string> archivos = listarArchivosTXT("backup");
                imprimirArchivosTXT(archivos);
                std::cout << "Ingrese el nombre del archivo a restaurar: " << std::endl;
                std::string archivoRespaldo;
                std::cin >> archivoRespaldo;
                listarRespaldos(archivoRespaldo);
                restaurarRespaldo(archivoOriginal, archivoRespaldo);
                system("pause");
                break;
             }
             case 2:
                 {
                    system("cls");
                    system("start \"\" .\\Doxygen_Documentacion\\html\\index.html");
                    system("pause");
                break;
                 }

             case 3:
                 {
                const int nuevaAnchura = 300;
                const int nuevaAltura = 300;
                img.imprimirImagenEnConsola();
                system("pause");
                break;
                 }
            case 4:
                system("cls");
                Menu_Principal(listaPersonas);
                system("pause");
                break;
        }
    } while (aux);
}





