#include "Operaciones.h"
#include <iostream>
#include "Validacion.h"
using namespace std;
double Operaciones::sin(double angulo )
{
    double x = angulo;
    double result,precission;
    result = 0;
    precission = 0;
    int sign=0,final_sign;
    final_sign = 0;
    const double pi = 3.141592654;
    while (x > pi) {
        x = x - pi;
        final_sign = final_sign + 1;
    }
    for (int i = 1; i <= 11; i = i + 2) {
        precission = potencia(-1, sign)*(potencia(x,i) / factorial(i));

        result = result + precission;
        sign = sign + 1;
        
    }
    if (final_sign % 2 != 0) {
        result = result * -1;
    }
    return result;
}


double Operaciones::cos(double angulo)
{
    
    double result = 0; 
    int presicion = 8; 
    const double pi = 3.141592654;
    int cont = 0;
    while (angulo > pi) {
        angulo = angulo - pi;
        cont++;
 
    }
    for (int i = 0; i < presicion; i++)
    {
        result += ((potencia(-1, i)) / factorial(2 * i)) * potencia(angulo, 2 * i);
    }
    if (cont%2==1) {
       result = result * -1;
    }
    return result;
}

double Operaciones::tan(double angulo)
{
    double tan;
    tan = Operaciones::sin(angulo) / Operaciones::cos(angulo);
    return tan;
}

long Operaciones::factorial(int n)
{
    //Funciona hasta 16! 
    if (n < 1) {
        return 1;
    }
    else {
        return n * factorial(n - 1);
    }
}

double Operaciones::potencia(double num, double pot){
    if (pot == 0) {
        return 1;
    }
    if (pot == 1) {
        return num;
    }
    if (pot == 0.5) {
        double raiz = raizCuadrada(num);
        return raiz;
    }
    if (pot < 0) {
        double inversoPot = 1.0 / potencia(num, -pot);
        return inversoPot;
    }
    double result = 1.0;
    for (int i = 0; i < pot; i++) {
        result *= num;
    }
    return result;
}

double Operaciones::raizCuadrada(double num) {
    if (num < 0) {
        throw std::domain_error("No se puede calcular la raiz cuadrada de un numero negativo.");
    }

    double raiz = 0;
    while ((num - raiz * raiz) > 0.00001) {
        raiz = raiz + 0.00001;
    }
    
    return raiz;
}


double Operaciones::raizCubica(double num) {
    double raiz;
    if (num == 0) {
        return 0;
    } else if (num > 0) {
        raiz = num;
    } else {
        raiz = -num;
    }

    double aproximacionAnterior = raiz;
    double epsilon = 0.00001;

    while (true) {
        double aproximacionActual = (2 * aproximacionAnterior + raiz / (aproximacionAnterior * aproximacionAnterior)) / 3;

        if (std::abs(aproximacionActual - aproximacionAnterior) < epsilon) {
            break;
        }

        aproximacionAnterior = aproximacionActual;
    }

    if (num < 0) {
        return -aproximacionAnterior;
    } else {
        return aproximacionAnterior;
    }
}


bool Operaciones::validarString(string infix){
	bool v= false;
	Validacion val;
	if (val.Parentesis_Sintaxis(infix)) {
		if (val.Operadores_Sintaxis(infix)) {
			if (val.vaidar_Escritura(infix)) {
				v = true;
						}
			else {
				cout << "\nIngrese correctamente su expresion" << endl;
			}
		}
		else
		{
			cout << "\nERROR SINTAXIS DE LOS OPERADORES" << endl;
		}
	}
	else {
		cout << "\nERROR SINTAXIS DE LOS PARENTESIS" << endl;
	}
	return v;
}
