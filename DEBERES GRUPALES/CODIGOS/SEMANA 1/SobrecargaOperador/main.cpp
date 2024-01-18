/*************************
 * Module:  Frac.h
 * Author:  Yeshua Chiliquinga, Josue Marin
 * Modified: miercoles, 23 de noviembre de 2023
 * Purpose: Exercise of Overide
 *************************/

#include <iostream>
#include "Frac.h"

int main(){
    Frac F1, F2, result;

    system("cls");

    cout << "Ingresar la primera fracion:  " << endl;
    F1.in();

    cout << "Ingresar la segunda fracion:  " << endl;
    F2.in();

    result = F1 * F2;
    result.out();

    return 0;
}
