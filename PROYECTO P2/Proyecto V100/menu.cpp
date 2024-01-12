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
#include "Nodo.h"
#include "validaciones.h"
#include "Fecha.h"
#include "Extra.h"
#include "Imagen.h"
#include "Amortizacion.h"

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
     "\t\t[1]REGISTRO DE USUARIO",
     "\t\t[2]CREAR CREDITO",
     "\t\t[3]FERIADOS",
     "\t\t[4]LEER TABLA",
     "\t\t[5]EXTRAS",
     "\t\t[6]SALIR"
      };
    int numeroOpciones = 6;
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
                        Menu_Credito(listaPersonas);
                        system("pause");
                        break;
                    case 3:
                      system("cls");
                        int anio;

                            do {
                                std::cout << "Ingrese el anio: ";
                                anio = valida.ingresar_anio("  ");

                                if (anio < anioActual) {
                                    std::cout << "\nError! El anio debe ser igual o posterior al actual (" << anioActual << "). Por favor, ingrese nuevamente.\n";
                                }

                                printf("\n");
                            } while (anio < anioActual);

                            f.imprimir_feriados(anio);
                            printf("\n");
                            system("pause");
                            break;
                    case 4:
                        system("cls");
                        imprimirContenidoArchivo(nombreArchivo);
                        system("pause");
                        Menu_Principal(listaPersonas);
                        system("pause");
                        break;
                    case 5:
                        system("cls");
                        Menu_Extras(listaPersonas);
                        system("pause");
                        break;
                    case 6:
                        system("cls");
                        std::cout << "Gracias por usar el programa. Hasta luego!\n";
                        aux = false;
                        break;
                }
        } while (aux);
}

void ingresar_datos_credito(){
validaciones valida;
    system("cls");
    Fecha sacado;
    double monto=0, tasa_interes=0;
    int ncuotas=0;

    while(monto<=999 || monto > 99999999.99){
        monto = valida.ingresar_reales("\nIngrese el monto del credito");

        if(monto<=999 || monto > 99999999.99){
            printf("\nEl monto debe ser mayor a 999 y menor a 100M");
        }else{
            printf("                                                           ");
        }
    }
    while(ncuotas<=0 || ncuotas > 500){

        ncuotas = valida.ingresar_enteros("\nIngrese el numero de cuotas a pagar del credito");

        if(ncuotas<=0 || ncuotas > 500){
            printf("El numero de cuotas debe ser mayor a 0 y menor a 500");
        }else{
            printf("                                                           ");
        }
    }
    while(tasa_interes<=0 || tasa_interes>99.99){
        tasa_interes = valida.ingresar_reales("\nIngrese la tasa de interes del credito");

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
    printf("\nTABLA GUARDADA CORRECTAMENTE");
    tabla.guardarTabla("tabla_amortizacion.txt");
    printf("\n");
    system("pause");
}
void Menus::Menu_Usuario(ListaDoble<Persona*> &listaPersonas){

validaciones valida;
bool aux = true;
    Menus menu;
    const char *titulo="\t\tDESEA REGISTRAR UNA PERSONA:";
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
                       {
                        system("cls");
                        Persona nuevaPersona = Persona::ingresarPersona(listaPersonas);
                        listaPersonas.insertarAlFinal(nuevaPersona);
                        menu.Menu_Usuario(listaPersonas);
                        break;
                       }

                    case 2:
                        system("cls");
                        Menu_Principal(listaPersonas);
                        system("pause");
                        break;
        }
    } while (aux);

}

void Menus::Menu_Credito(ListaDoble<Persona*> listaPersonas) {

validaciones valida;
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
                        ingresar_datos_credito();
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
        "\t\t[2]AYUDA",
        "\t\t[3]IMAGEN",
        "\t\t[4]SALIR"
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
                system("cls");
                system("start \"\" .\\Doxygen_Documentacion\\html\\index.html");
                system("pause");
                break;
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


void Menus::Menu_Ordenar(ListaDoble<Persona*> &listaPersonas) {
     bool aux = true;
    const char *titulo ="\t\tOEDENAR PERSONAS";
    const char *opciones[] =
    {"\t\tOrdenar por Nombre",
    "\t\tOrdenar por Apellido",
    "\t\tOrdenar por Cedula",
    "\t\tSalir"};

    int numeroOpciones = 4;
    int selec = 1;
    do{
    menuSeleccion(titulo,opciones, numeroOpciones, selec);
     switch (selec) {
                     case 1: {
                        system("cls");
                        listaPersonas.mostrarLista();
                        printf("Lista Ordenada por Nombre ");
                        printf("\n");
                        listaPersonas.orden_seleccion([](Persona* p1, Persona* p2) {
                            return p1->getNombre() < p2->getNombre();
                        });
                        printf("\n");
                        listaPersonas.mostrarLista();
                        system("pause");
                        break;
                        }

                    case 2:
                     {
                        system("cls");
                        listaPersonas.mostrarLista();
                        printf("Lista Ordenada por Apellido");
                        printf("\n");
                        listaPersonas.orden_seleccion([](Persona* p1, Persona* p2) {
                            return p1->getApellido() < p2->getApellido();
                        });
                        printf("\n");
                        listaPersonas.mostrarLista();
                        system("pause");
                        break;
                        }
                    case 3:
                        {
                        system("cls");
                        listaPersonas.mostrarLista();
                        printf("Lista Ordenada por Cedula ");
                        printf("\n");
                        listaPersonas.orden_seleccion([](Persona* p1, Persona* p2) {
                            return p1->getCedula() < p2->getCedula();
                        });
                        printf("\n");
                        listaPersonas.mostrarLista();
                        system("pause");
                        break;
                        }

                    case 4:
                        system("cls");
                        Menu_Principal(listaPersonas);
                        break;
                }
        } while (aux);
}

