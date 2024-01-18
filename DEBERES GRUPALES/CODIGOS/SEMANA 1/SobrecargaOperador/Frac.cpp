#include <iostream>
#include "Frac.h"
using namespace std;
void Frac::in(){
    cout << "Ingrese el  numerador : ";
    cin >> a;
    cout<< "Ingrese el denominador : ";
    cin >> b;
}
// Overload the * operator
Frac Frac::operator*(const Frac &obj){
    Frac temporal;
    temporal.a = a * obj.a;
    temporal.b = b * obj.b;
    return temporal;
}
void Frac::out(){
    cout << "La multiplicacion de la fraccion es: " << a << "/" << b <<endl;
}


