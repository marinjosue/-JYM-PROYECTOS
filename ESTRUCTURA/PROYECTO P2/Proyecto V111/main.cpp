/***********************************************************************
 * Module:  main.cpp
 * Author:  Josue Marin
 * Modified: viernes, 1 de diciembre de 2023 12:05:38 a. m.
 * Purpose: Declaration of the class main
 ***********************************************************************/

#include <iostream>
#include "Nodo.h"
#include "menu.h"
#include "ListaDoble.cpp"
int main()
{
    ListaDoble<Persona*> listaPersonas;
    Menus menu;
    menu.Menu_Principal(listaPersonas);
    return 0;
}
