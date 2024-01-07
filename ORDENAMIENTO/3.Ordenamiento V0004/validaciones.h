/***********************************************************************
 * Module:  Validaciones.h
 * Author:  Chiliquinga Yeshua, Josue Marin, Salcedo Micaela
 * Modified: viernes, 1 de diciembre de 2023 12:05:38 a. m.
 * Purpose: Declaration of the class validaciones
 ***********************************************************************/

#ifndef VALIDACIONES_H_INCLUDED
#define VALIDACIONES_H_INCLUDED

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
int ingresar_enteros(const char* msj);
int borrar(char* datos, int& i);
float ingresar_reales(const char* msj);
std::string ingresar_alfabetico(const char* msj);
std::string ingresar_cedula(const char* msj);

int ingresar_enteros(const char* msj) {
    char* datos = new char[10];
    char c;
    int i = 0;

    printf("%s", msj);
    printf("\n");

    while ((c = getch()) != 13 && i < 9) {
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
    char* dato = new char[maxDigitos + 1]; // +1 para el car�cter nulo '\0'
    int i = 0;
    char c;

    std::cout << msj << std::endl;

    while ((c = _getch()) != 13 && i < maxDigitos) {
        if (c >= '0' && c <= '9') {
            dato[i++] = c;
            std::cout << c;
        } else if (c == 8 && i != 0) {
            dato[--i] = 0;

            std::cout << "\b \b"; // Retrocede el cursor y borra el �ltimo car�cter
        }
    }

    dato[i] = '\0';

    // Validar c�dula (por ejemplo, asumiendo una c�dula de 10 d�gitos num�ricos)
    if (strlen(dato) != 10) {
        std::cout << "\nError: La cedula debe tener 10 caracteres." << std::endl;
        delete[] dato; // Liberar memoria antes de salir
        return ingresar_cedula(msj); // Vuelve a llamar a la funci�n para ingresar nuevamente
    }

    std::cout << std::endl;

    std::string resultado(dato);
    delete[] dato; // Liberar memoria antes de salir
    return resultado;
}

std::string ingresar_id(const char* msj, int& contador) {
    std::string prefijo = "L00";
    std::string contadorStr = std::to_string(contador);
    
    while (contadorStr.length() < 4) {
        contadorStr = "0" + contadorStr;
    }

    std::string id = prefijo + contadorStr;

    std::cout << msj << id << std::endl;

    return id;
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

#endif // VALIDACIONES_H_INCLUDED
