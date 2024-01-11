/*************************
                UFA - ESPE
 * Module:  main.cpp
 * Author:  Chiliquinga Yeshua, Marin Alquinga,Salcedo Micaela
 * Modified: domingo, 17 de diciembre de 2023
 * Purpose: Crear una tabla de credito de amortizacion Francesa
 ***********************************************************************/
#include <iostream>
#include "Menu.cpp"
#include "ListaDoble.h"

using namespace std;

int main()
{
    ListaDoble<Persona*> listaPersonas;
    Menus menu;
    menu.Menu_Principal(listaPersonas);
    return 0;
}

