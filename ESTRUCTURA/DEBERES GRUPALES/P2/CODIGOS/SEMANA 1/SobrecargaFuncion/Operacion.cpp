#include "Metodo.h"

int Multiplicar::multiplicar(int valor1, int valor2) {
	result = valor1 * valor2;
	return result;
}
int Multiplicar::multiplicar(int valor1, int valor2, int valor3) {
	result = (valor1 * valor2) * valor3;
	return result;
}