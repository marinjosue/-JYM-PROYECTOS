#include "Transformacion.h"
#include <math.h>
#include <cmath>
#include <vector>
#include <cmath>
#include <sstream>
#include <stack>
#include "Validacion.h"
# define MY_PI 3.14159265358979323846
Transformacion::Transformacion() {

}

void Transformacion::calcularImpares(const string& infix) {
    Pila<int> pilaImpares;
    ingresoDatos ingreso;
    int pos = 1;  // Iniciar en la primera posición

    while (pos <= infix.size()) {
        // Obtener el número en la posición actual
        int numero = ingreso.convertirStringAEntero(infix.substr(pos - 1, 1));

        // Si el número es impar, realizar la operación y guardar en la pila
        if (numero % 2 != 0) {
            // Realizar la operación solo si la pila tiene al menos dos elementos
            if (pilaImpares.size() >= 2) {
                int segundoNumero = pilaImpares.Pop();
                int resultado = 0;

                // Realizar la operación específica (puedes ajustar según tus necesidades)
                if (infix[pos - 1] == '+') {
                    resultado = numero + segundoNumero;
                } else if (infix[pos - 1] == '-') {
                    resultado = segundoNumero - numero;
                } else if (infix[pos - 1] == '*') {
                    resultado = numero * segundoNumero;
                } else if (infix[pos - 1] == '/') {
                    if (numero != 0) {
                        resultado = segundoNumero / numero;
                    } else {
                        cout << "Error: División por cero." << endl;
                        // Puedes manejar el error de otra manera si es necesario
                        return;
                    }
                }

                // Guardar el resultado en la pila
                pilaImpares.Push(resultado);
            } else {
                // Si no hay suficientes elementos en la pila, simplemente agregar el número
                pilaImpares.Push(numero);
            }
        }

        // Mover a la siguiente posición impar
        pos += 2;
    }

    // Imprimir el contenido final de la pila
    while (!pilaImpares.isEmpty()) {
        cout << pilaImpares.Pop() << " ";
    }
    cout << endl;
}


int Transformacion::esOperador(char ch) {
	switch (ch) {
	case '+':
	case '-':
	case '*':
	case '/':
	case '^':
	case '%':
	case '(':
	case ')':
		return 1;
		break;
	default:
		return 0;
	}
}
int Transformacion::prioridades(char ch)
{
	int n = 0;
	switch (ch) {
	case '-':
	case '+':
		n = 3;
		break;
	case '*':
	case '/':
	case '%':
		n = 4;
		break;
	case '^':
	case 's':
		n = 6;
		break;
	case '(':
	case ')':
	case '#':
		n = 1;
		break;
	}
	return n;
}
string Transformacion::postFix(string infix)
{
	
	Pila <char> pilaOperadores;
	pilaOperadores.Push('#');
    string postfix= "";
	char aux;
	Validacion val;
	if (val.Parentesis_Sintaxis(infix)) {
		if (val.Operadores_Sintaxis(infix)) {
			if (val.vaidar_Escritura(infix)) {
				if(val.validar_Ceros(infix)){
				for (int i = 0, j = 0; i < infix.size(); i++)
				{
					aux = infix[i];
					if (!esOperador(aux)) {
						postfix += aux;
					}
					else {
						if (aux == '(') {
							pilaOperadores.Push(aux);
						}
						else if (aux == ')') {
							while (pilaOperadores.Peek() != '(') {
								postfix += pilaOperadores.Pop();
							}
							pilaOperadores.Pop();
						}
						else {
							if (prioridades(pilaOperadores.Peek()) < prioridades(aux)) {
								pilaOperadores.Push(aux);
							}
							else {
								while (prioridades(pilaOperadores.Peek()) >= prioridades(aux)) {
									postfix += pilaOperadores.Pop();
								}
								pilaOperadores.Push(aux);
							}

						}
					}
				}
				while (pilaOperadores.Peek() != '#') {
					postfix += pilaOperadores.Pop();
				}
			}else{
				cout<<"\n La division no esta definida"<<endl;
			}	
			}
			else {
				cout << "\n Ingrese correctamente su expresion" << endl;
			}
		}
		else
		{
			cout << "\n ERROR" << endl;
		}
	}
	else {
		cout << "\n ERROR SINTAXIS DE LOS PARENTESIS" << endl;
	}
    return postfix;
}
string Transformacion::reverso(string expresion1)
{
	int i = 0;
	string expresionInvertida;
	for (i = expresion1.length() - 1; i >= 0; i--) {
		if (expresion1.at(i) == '(') {
			expresionInvertida.append(")");
		}
		else if (expresion1.at(i) == ')') {
			expresionInvertida.append("(");
		}
		else {
			expresionInvertida.append(expresion1.substr(i, 1));
		}
	}
	return expresionInvertida;
}

string Transformacion::preFix(string expresion) {
	expresion = reverso(expresion);
	expresion = postFix1(expresion);
	expresion = reverso(expresion);
	return expresion;
}

bool Transformacion::detectarOperadores(char ch) {

	if (ch == ')'|| ch == '#' || ch == '+' || ch == '-' || ch == '*' || ch == '/' || ch == '%' || ch == '^' || ch == 's' || ch == 't' || ch == 'c' || ch == 'p') {
		return true;
	}
	return false;
}

float Transformacion::calcular(string infijo, string posfijo)
{	
	Pila<float> pilaFloat;
	int i,j,k=0;
	char aux[10]{},aux2[10]{},aux3[10]{};
	string num;
	float val1, val2;
	infijo.append("#");
	for ( i = 0,j =0; i < posfijo.size(); i++,j++)
	{
		//75-35^2+(8*12)
		//75352^-812*+
		
		aux[0] = posfijo[i];
		aux2[0] = infijo[j];
		if (!detectarOperadores(aux[0])) {
			if (aux2[0] == '(') {
				j++;
				aux2[0] == infijo[j];
			}
			if (!detectarOperadores(aux2[0])&& !detectarOperadores(infijo[j + 1]) ) {
				aux3[k] += aux[0];
				k++;
			}
			else if (!detectarOperadores(aux2[0]) && (detectarOperadores(infijo[j + 1]))){
				aux3[k] += aux[0];
				pilaFloat.Push(atof(aux3));
				k = 0;
				for ( int p = 0;  p < 3;  p++)
				{
					aux3[p] = {};
				}
				if (infijo[j + 1] == ')') {
					j = j + 2;
				}
				else {
					j++;
				}
			}
			
		}
		else {
		
			switch (aux[0])
			{
			case '+':
				val1 = pilaFloat.Pop();
				val2 = pilaFloat.Pop();
				pilaFloat.Push(val1 + val2);
				break;
			case '-':
				val1 = pilaFloat.Pop();
				val2 = pilaFloat.Pop();
				pilaFloat.Push(val2 - val1);
				break;
			case '*':
				val1 = pilaFloat.Pop();
				val2 = pilaFloat.Pop();
				pilaFloat.Push(val1 * val2);
				break;
			case '/':
				val1 = pilaFloat.Pop();
				val2 = pilaFloat.Pop();
				pilaFloat.Push(val2 / val1);
				break;
			case '^':
				val1 = pilaFloat.Pop();
				val2 = pilaFloat.Pop();
				pilaFloat.Push(pow(val2, val1));
				break;
			case '%':
				val1 = pilaFloat.Pop();
				val2 = pilaFloat.Pop();
				pilaFloat.Push((int)(val2) % (int)val1);
				break;
			case 'c':
				aux[0] = posfijo.at(i + 3);
				if (infijo[j + 6] == ')') {
					aux[1] = posfijo.at(i + 4);
					j++;
					i++;
				}
				else if (infijo[j + 7] == ')') {
					aux[1] = posfijo.at(i + 4);
					aux[2] = posfijo.at(i + 5);
					j=j+2;
					i=i+2;
				}
				i = i + 3;
				//pilaFloat.Push(cos((MY_PI/180) * atof(aux)));
				pilaFloat.Push(calcularCos((MY_PI/180) * atof(aux),10));
				j = j + 7;
				break;
			case 's':
				if (posfijo.at(i + 1) == 'i') {
					aux[0] = posfijo.at(i + 3);
					if (esOperador(infijo[j])) {
						j++;
					}
					if (infijo[j + 6] == ')') {
						aux[1] = posfijo.at(i + 4);
						j++;
						i++;
					}
					else if (infijo[j + 7] == ')') {
						aux[1] = posfijo.at(i + 4);
						aux[2] = posfijo.at(i + 5);
						j = j + 2;
						i = i + 2;
					}
					i = i + 3;
					//pilaFloat.Push(sin((MY_PI / 180) * atof(aux)));
					pilaFloat.Push(calcularSen((MY_PI/180) * atof(aux),10));
					j = j + 7;
					break;
				}
				else {
						int m = 0,count = j;
						while (infijo[count + 5] != ')') {
						aux[m] = posfijo.at(i + 4+m);
						m++;
						count++;
					}
					pilaFloat.Push(sqrt(atof(aux)));
					i = i + 3 + m;
					j = j + 7 + m;
					break;
				}
			case 't':
				aux[0] = posfijo.at(i + 3);
				if (infijo[j + 6] == ')') {
					aux[1] = posfijo.at(i + 4);
					j++;
					i++;
				}
				else if (infijo[j + 7] == ')') {
					aux[1] = posfijo.at(i + 4);
					aux[2] = posfijo.at(i + 5);
					j = j + 2;
					i = i + 2;
				}
				i = i + 3;
				//pilaFloat.Push(tan((MY_PI / 180) * atof(aux)));
				pilaFloat.Push(calcularTan((MY_PI/180) * atof(aux),10));
				j = j + 7;
				break;
			case 'p':
				pilaFloat.Push(MY_PI);
				i = i + 1;
				j = j + 1;
				break;
			}
			j--;
		}
		for (int p = 0; p < 3; p++)
		{
			aux[p] = {};
		}
	}
	return pilaFloat.Pop();
}

string Transformacion::postFix1(string infix)
{
	
	Pila <char> pilaOperadores;
	pilaOperadores.Push('#');
    string postfix= "";
	char aux;
	for (int i = 0,j=0; i < infix.size(); i++)
	{
		aux = infix[i];
		if (!esOperador(aux)) {
			postfix += aux;
		}
		else {
			if (aux == '(') {
				pilaOperadores.Push(aux);
			}
			else if (aux == ')') {
				while (pilaOperadores.Peek() != '(') {
					postfix += pilaOperadores.Pop();
				}
				pilaOperadores.Pop();
			}
			else {
				if (prioridades(pilaOperadores.Peek())<prioridades(aux)) {
					pilaOperadores.Push(aux);
				}
				else {
					while (prioridades(pilaOperadores.Peek()) >= prioridades(aux)) {
						postfix += pilaOperadores.Pop();
					}
					pilaOperadores.Push(aux);
				}

			}
		}
		
	}
	while (pilaOperadores.Peek() != '#') {
		postfix += pilaOperadores.Pop();
	}
    return postfix;
}

bool Transformacion::validarString(string infix){
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


double Transformacion::calcularCos(double x,int n){
	double resultado = 0.0;
    for (int i = 0; i < n; ++i) {
        int exponente = 2 * i;
        double termino = std::pow(-1, i) * std::pow(x, exponente) / std::tgamma(exponente + 1);
        resultado += termino;
    }
    return resultado;
}

double Transformacion::calcularSen(double x,int n){
	int expo=1;
	double resultado=0,factorial;
	for (int i = 1; i <= n; i++) {
        factorial = 1;
        for (int j = 1; j <= expo; j++) {
            factorial *= j;
        }

        if (i % 2 == 0) {
            resultado = resultado - pow(x, expo) / factorial;
        } else {
            resultado = resultado + pow(x, expo) / factorial;
        }

        expo = expo + 2;
    }
    return resultado;
}

double Transformacion::calcularTan(double x,int n){
    double seno = calcularSen(x,n);
    double coseno = calcularCos(x,n);

    return seno / coseno;
}

template class Pila<int>;