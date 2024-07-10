/*************************
    UFA - ESPE
 * Module:  Menus.h
 * Author:  Chiliquinga Yeshua, Marin Alquinga, Salcedo Micaela
 * Modified: domingo, 17 de diciembre de 2023
 * Purpose: Declaracion del encabezado Menus
 ***********************************************************************/
#ifndef MENU_H
#define MENU_H

#include "ListaDoble.h"  // Agrega la inclusi�n del archivo de encabezado de ListaDoble
#include "Persona.h"    // Agrega la inclusi�n del archivo de encabezado de Persona

class Menus {
public:
    void gotoxy(int x, int y);
    void color(int foreground, int background);
    void menuSeleccion(const char* titulo,const char *opciones[], int numeroOpciones, int &selec);
    void Menu_Principal(ListaDoble<Persona*> listaPersonas);
    void Menu_Ordenar(ListaDoble<Persona*> &listaPersonas);


};

#endif // MENU_H
