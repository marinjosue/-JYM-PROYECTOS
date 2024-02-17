/***********************************************************************
 * Module:  Validaciones.h
 * Author:  Josue Marin
 * Modified: viernes, 1 de diciembre de 2023 12:05:38 a. m.
 * Purpose: Declaration of the class validaciones
 ***********************************************************************/

#ifndef VALIDACIONES_H_INCLUDED
#define VALIDACIONES_H_INCLUDED
using namespace std;
#include <iostream>
#include <stdlib.h>
#include <conio.h>
#include <stdio.h>
#include <string.h>
#include <cstring>
#include <ios>
#include <sstream>
#include <cstdlib>
#include <vector>
#include <fstream>
std::string mayusculas_primeras(const std::string& cadena);
std::string ingresar_cadena_con_espacio(const char* msj);
int ingresar_enteros(const char* msj);
int ingresar_enterosC(const char* msj);
int borrar(char* datos, int& i);
float ingresar_reales(const char* msj);
std::string ingresar_alfabetico(const char* msj);
std::string ingresar_cedula(const char* msj);
 bool validarCedula(std::string cedula);
  std::string ingresar_numeros_como_string(const char* msj);


 std::string ingresar_numeros_como_string(const char* msj) {
   string datos = "";
  char c;

  printf("%s", msj);
  printf("\n");

  while ((c = getch()) != 13 && datos.length() < 10) {
    if ((c >= '0' && c <= '9') || c == 8) {
      if (c == 8) {
        // Borrar último caracter si la entrada es retroceso
        if (!datos.empty()) {
          datos.pop_back();
          cout << "\b \b";  // Mover el cursor y borrar visualmente
        }
      } else {
        cout << c;  // Mostrar el caracter ingresado
        datos += c;  // Añadir al string
      }
    }
  }

  return datos;
}
int ingresar_enteros(const char* msj) {
    char* datos = new char[10];
    char c;
    int i = 0;

    printf("%s", msj);
    printf("\n");

    while ((c = getch()) != 13 && i < 10) {
        if ((c >= '0' && c <= '9')|| c == 8) {
            if(c == 8){
                i = borrar(datos,i);
            }else{
                printf("%c", c);
                datos[i++] = c;
            }

        }
    }
    datos[i] = '\0';
    return atoi(datos);
}
int ingresar_enterosC(const char* msj) {
    char* datos = new char[10];
    char c;
    int i = 0;

    printf("%s", msj);
    printf("\n");

    while ((c = getch()) != 13 && i < 10) {
        if ((c >= '0' && c <= '9')|| c == 8) {
            if(c == 8){
                i = borrar(datos,i);
            }else{
                printf("%c", c);
                datos[i++] = c;
            }

        }
    }
    datos[i] = '\0';
    return atoi(datos);
}

float ingresar_reales(const char* msj) {
    char* datos = new char[12];
    char c;
    int i = 0;
    bool hay_punto = false;
    int posicion_punto;

    printf("%s", msj);
    printf("\n");

    while ((c = getch()) != 13 && i < 11) {
        if ((c >= '0' && c <= '9') || (c == '.' && !hay_punto)|| c == 8 || c == '-') {
            if(!((c == '.')&& i == 0)){
                if(!((c == '-') && i != 0)){
                    if (c == 8) {
                        i = borrar(datos, i);
                        if((i+1) == posicion_punto){
                            hay_punto = false;
                        }
                    }
                    else {
                        printf("%c", c);
                        datos[i++] = c;

                        if (c == '.') {
                            posicion_punto = i;
                            hay_punto = true;
                        }
                    }
                }
            }
        }
    }
    datos[i] = '\0';
    return atof(datos);
}

std::string ingresar_alfabetico(const char* msj) {
    char datos[21];
    char c;
    int i = 0;

    printf("%s", msj);
    printf("\n");

    while ((c = getch()) != 13 && i < 20) {
        if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z')|| c == 32||c == 8) {
            if (c == 8) {
                i = borrar(datos, i);
            } else {
                printf("%c", c);
                datos[i++] = c;
            }
        }
    }
    datos[i] = '\0';
    return std::string(datos);
}


std::string ingresar_cedula(const char* msj) {
    const int maxDigitos = 10;
    char* dato = new char[maxDigitos + 1]; // +1 para el carácter nulo '\0'
    int i = 0;
    char c;

    std::cout << msj << std::endl;

    while ((c = _getch()) != 13 && i < maxDigitos) {
        if (c >= '0' && c <= '9') {
            dato[i++] = c;
            std::cout << c;
        } else if (c == 8 && i != 0) {
            dato[--i] = 0;

            std::cout << "\b \b"; // Retrocede el cursor y borra el último carácter
        }
    }

    dato[i] = '\0';

    // Validar cédula (por ejemplo, asumiendo una cédula de 10 dígitos numéricos)
    if (strlen(dato) != 10) {
        std::cout << "\nError: La cedula debe tener 10 caracteres." << std::endl;
        delete[] dato; // Liberar memoria antes de salir
        return ingresar_cedula(msj); // Vuelve a llamar a la función para ingresar nuevamente
    }

    std::cout << std::endl;

    std::string resultado(dato);
    delete[] dato; // Liberar memoria antes de salir
    return resultado;
}


int borrar(char* datos, int& i) {
    if (i > 0) {
        printf("\b \b");
        i--;
        datos[i] = '\0';
        return i;
    }
    return 0;
}

 std::string leerArchivoTxt()
    {
        std:: string texto;
         std::string lectura;
      std::ifstream archivo;
       archivo.open("personas.txt", std::ios::in);

        if (archivo.fail())
        {
             std:: cout << "No se pudo abrir el archivo";
            exit(1);
        }
        while (!archivo.eof())
        {
            getline(archivo, texto, ' ');
            lectura += texto + " ";
        }
        archivo.close();
        return lectura;
    }

bool validarCedula(std::string cedula) {
    // Verificar que tenga 10 dígitos
    if (cedula.length() != 10) {
        return false;
    }
    // Verificar que los primeros dos dígitos sean válidos
    if (cedula[0] < '0' || cedula[0] > '9' || cedula[1] < '0' || cedula[1] > '9') {
        return false;
    }
    // Verificar que los dígitos intermedios sean válidos
    for (int i = 2; i < 8; i++) {
        if (cedula[i] < '0' || cedula[i] > '9') {
            return false;
        }
    }
    // Verificar que el último dígito sea válido
    if (cedula[9] < '0' || cedula[9] > '9') {
        return false;
    }
    // Verificar el dígito verificador
    int suma = 0;
    for (int i = 0; i < 9; i++) {
        int digito = cedula[i] - '0';
        if (i % 2 == 0) {
            digito *= 2;
            if (digito > 9) {
                digito -= 9;
            }
        }
        suma += digito;
    }
    int digitoVerificador = 10 - (suma % 10);
    if (digitoVerificador != (cedula[9] - '0')) {
        return false;
    }
    return true;
}

std::string ingresar_alfabetico_con_un_espacio(const char* msj) {
  char datos[21];
  char c;
  int i = 0;
  bool espacio_ingresado = false;

  printf("%s", msj);
  printf("\n");

  while ((c = getch()) != 13 && i < 20) {
    if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || c == 32 || c == 8) {
      if (c == 8) {
        i = borrar(datos, i);
        espacio_ingresado = false; // Reiniciar la bandera si se borra un carácter
      } else if (c == 32 && !espacio_ingresado) {
        printf("%c", c);
        datos[i++] = c;
        espacio_ingresado = true;
      } else if (c != 32) {
        printf("%c", c);
        datos[i++] = c;
      }
    }
  }
  datos[i] = '\0';
  return std::string(datos);
}
std::string mayusculas_primeras(const std::string& cadena) {
  std::string resultado;

  for (int i = 0; i < cadena.size(); i++) {
    if (i == 0 || cadena[i - 1] == ' ') {
      resultado += toupper(cadena[i]);
    } else {
      resultado += tolower(cadena[i]);
    }
  }

  return resultado;
}
#endif // VALIDACIONES_H_INCLUDED
