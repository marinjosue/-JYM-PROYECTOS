#include <iostream>
#include <string>
#include <sstream>
#include "Polaca.h"
#include "Validacion.h"
using namespace std;

Polaca::Polaca(void)
{
}



bool Polaca::isOperador(char c) {
   switch (c) {
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

int Polaca::prioridades(char ch)
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
bool Polaca::isFuncion(char c) {
    return c == 'sin' || c == 'cos' || c == 'tan'  || c == 'sqrt' || c == 'q';
}

bool Polaca::isOperadorStr(string c) {
    return c == "+" || c == "-" || c == "*" || c == "/" || c == "^";
}

bool Polaca::isFuncionStr(string c) {
    return c == "sin" || c == "cos" || c == "tan" || c == "sqrt" || c == "q";
}


int Polaca::obtenerPrecedencia(string operador) {
    if (operador == "sin" || operador == "cos" || operador == "tan")
        return 4;
    else if (operador == "^" || operador == "sqrt" || operador == "q")
        return 3;
    else if (operador == "*" || operador == "/")
        return 2;
    else if (operador == "+" || operador == "-")
        return 1;
    else
        return 0;
}

string Polaca::reverso(string expresion1)
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

bool Polaca::validarString(string infix){
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


string Polaca::convertirExpresionInfijaAPrefija(string expresionInfija) {
    expresionInfija = reverso(expresionInfija);
    expresionInfija = postFix1(expresionInfija);
    expresionInfija = reverso(expresionInfija);

    return expresionInfija;
}

string Polaca::postFix1(string infix)
{
	
	Pila <char> pilaOperadores;
	pilaOperadores.push('#');
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
				pilaOperadores.push(aux);
			}
			else if (aux == ')') {
				while (pilaOperadores.peek() != '(') {
					postfix += pilaOperadores.pop();
				}
				pilaOperadores.pop();
			}
			else {
				if (prioridades(pilaOperadores.peek())<prioridades(aux)) {
					pilaOperadores.push(aux);
				}
				else {
					while (prioridades(pilaOperadores.peek()) >= prioridades(aux)) {
						postfix += pilaOperadores.pop();
					}
					pilaOperadores.push(aux);
				}

			}
		}
		
	}
	while (pilaOperadores.peek() != '#') {
		postfix += pilaOperadores.pop();
	}
    return postfix;
}
int Polaca::esOperador(char ch) {
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


Pila<string> Polaca::convertirExpresionInfijaAPosfija(string expresionInfija) {
    Pila<string> pilaPosfija;
    Pila<char> pilaOperadores;
    pilaOperadores.push('#');
    string pilaSalida = "";
    char aux;
    Validacion val;

    if (val.Parentesis_Sintaxis(expresionInfija)) {
        if (val.Operadores_Sintaxis(expresionInfija)) {
            if (val.vaidar_Escritura(expresionInfija)) {
                if (val.validar_Ceros(expresionInfija)) {
                    for (int i = 0; i < expresionInfija.size(); i++) {
                        aux = expresionInfija[i];
                        if (!isOperador(aux)) {
                            pilaSalida += aux;
                        } else {
                            if (aux == '(') {
                                pilaOperadores.push(aux);
                            } else if (aux == ')') {
                                while (pilaOperadores.top() != '(') {
                                    pilaSalida += pilaOperadores.pop(); // Corregido aquí
                                }
                                pilaOperadores.pop(); // Elimina el '(' de la pila
                            } else {
                                if (prioridades(pilaOperadores.top()) < prioridades(aux)) {
                                    pilaOperadores.push(aux);
                                } else {
                                    while (prioridades(pilaOperadores.top()) >= prioridades(aux)) {
                                        pilaSalida += pilaOperadores.pop(); // Corregido aquí
                                    }
                                    pilaOperadores.push(aux);
                                }
                            }
                        }
                    }
                    while (pilaOperadores.top() != '#') {
                        pilaSalida += pilaOperadores.pop(); // Corregido aquí
                    }
                } else {
                    cout << "\n La division no esta definida" << endl;
                }
            } else {
                cout << "\n Ingrese correctamente su expresion" << endl;
            }
        } else {
            cout << "\n ERROR" << endl;
        }
    } else {
        cout << "\n ERROR SINTAXIS DE LOS PARENTESIS" << endl;
    }

    // Convertir la cadena de salida a una pila de strings
    for (char c : pilaSalida) {
        pilaPosfija.push(string(1, c));
    }

    return pilaPosfija;
}

double Polaca::calcular(Pila<string>& expresion) {
    Pila<double> pilaOperandos;
    Operaciones op;

    int tamInicial = expresion.size();

    for (int i = 0; i < tamInicial; i++) {
        string token = expresion.top();
        expresion.pop();

        if (isdigit(token[0]) || (token[0] == '-' && token.length() > 1 && isdigit(token[1]))) {
            // Si el token es un número (incluyendo números negativos), lo convertimos a double y lo agregamos a la pila de operandos
            double numero = stod(token);
            pilaOperandos.push(numero);
        }
        else if (isOperador(token[0])) {
            // Si el token es un operador, realizamos la operación correspondiente
            double operand2 = pilaOperandos.top();
            pilaOperandos.pop();
            double operand1 = pilaOperandos.top();
            pilaOperandos.pop();

            double resultado;

            switch (token[0]) {
            case '+':
                resultado = operand1 + operand2;
                break;
            case '-':
                resultado = operand1 - operand2;
                break;
            case '*':
                resultado = operand1 * operand2;
                break;
            case '/':
                resultado = operand1 / operand2;
                break;
            case '^':
                resultado = op.potencia(operand1, operand2);
                break;
            }

            pilaOperandos.push(resultado);
        }
        else if (isFuncion(token[0])) {
            // Si el token es una función, aplicamos la función al operando de la pila
            double operando = pilaOperandos.top();
            pilaOperandos.pop();

            double resultado;

            switch (token[0]) {
            case 'sin':
                resultado = op.sin(operando);
                break;
            case 'cos':
                resultado = op.cos(operando);
                break;
            case 'tan':
                resultado = op.tan(operando);
                break;
            case 'sqrt':
                resultado = op.raizCuadrada(operando);
                break;
            case 'q':
                resultado = op.raizCubica(operando);
                break;
            }

            pilaOperandos.push(resultado);
        }
    }

    return pilaOperandos.top();
}
