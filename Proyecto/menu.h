#ifndef MENU_H
#define MENU_H
//#include "Movimientos.h"
#include "validaciones.h"
class Menus {
public:
    void gotoxy(int x, int y);
    void color(int foreground, int background);
    void submenu2();
    void menuSeleccion(const char* titulo,const char *opciones[], int numeroOpciones, int &selec);
    void Menu_Principal();
    void Menu_Credito();
};

#endif // MENU_H
