#ifndef MENU_H
#define MENU_H

class Menu {
public:
    void gotoxy(int x, int y);
    void color(int foreground, int background);
    void submenu1();
    void submenu2();
    void menuSeleccion(const char *opciones[], int numeroOpciones, int &selec);
    void imprimirMenu();
};

#endif // MENU_H
