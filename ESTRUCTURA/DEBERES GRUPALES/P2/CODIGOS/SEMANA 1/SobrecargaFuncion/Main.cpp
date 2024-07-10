#include <iostream>
#include "Metodo.h"
using namespace std;
int main() {
    
    system("cls");
    int a,b,c;
    Multiplicar m;
    cout <<"\tOPERADOR SOBRECARGADOS"<<endl;
    cout << "MULTIPLICACION DE DOS NUMEROS : " <<endl;
    cout << "Ingrese el primer numero: ";
    cin >> a; 
    cout << "Ingrese el segundo numero: ";
    cin >> b; 
    cout << "La multiplicacion es: " << m.multiplicar(a, b)<<endl;
    cout << "MULTIPLICACION DE TRES NUMEROS: " <<endl;
    cout << "Ingrese el primer numero: ";
    cin >> a; 
    cout << "Ingrese el segundo numero: ";
    cin >> b; 
    cout << "Ingrese el tercer numero: ";
    cin >> c; 
    cout << "La multiplicacion de tres numeros es: " << m.multiplicar(a, b,c) << endl;
    return 0;
 }