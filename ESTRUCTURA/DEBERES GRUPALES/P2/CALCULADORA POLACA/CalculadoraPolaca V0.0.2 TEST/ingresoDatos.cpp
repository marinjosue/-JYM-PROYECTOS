
#include "ingresoDatos.h"
#include <conio.h>
using namespace std;


int  ingresoDatos::ingresar_Datosenteros()
{
	char* dato = new char[10], c;
	int i = 0;
	printf("Seleccione una opcion: ");
	while ((c = _getch()) != 13) {
		if (c >= '0' && c <= '9') {
			printf("%c", c);
			dato[i++] = c;
		}
		else if (c == 8 || c == 127) {
			printf("\b \b");
			dato[i--] = 0;
		}
	}
	dato[i] = '\0';
	return atoi(dato);
}

string ingresoDatos::ingresoTransformacion()
{
	char c;
	string expresion = "";
	printf("Ingrese la expresion:  ");

	while ((c = _getch()) != 13) {
		if ((c >= 40 && c <= 57) || c == 97 || c == 99 || (c >= 110 && c <= 116) || c == 105 || c == 94 || c == 37) {
			printf("%c", c);
			expresion.push_back(c);
		}
		else if (c == 8 || c == 127) {
			printf("\b \b");
			expresion.pop_back();
		}
	}

	return expresion;

}

int ingresoDatos::convertirStringAEntero(const string& str)
{
    // Asumiendo que el string solo contiene un carácter numérico
    return str.empty() ? 0 : str[0] - '0';
}
