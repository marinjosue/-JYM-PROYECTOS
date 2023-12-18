/***********************************************************************
 UFA - ESPE
 * Module:  Fecha.h
 * Author:  Chiliquinga Yeshua, Marin Alquinga,Salcedo Micaela
 * Modified: jueves, 7 de diciembre de 2023 01:11:27 p. m.
 * Purpose: Declaracion de clase Fecha
 ***********************************************************************/

#ifndef IMAGEN_H
#define IMAGEN_H
#include <string>
#include <windows.h>

class Imagen{
	public:
		//Constuctor
		Imagen(std::string);
		//Setters y Getters
		void setArchivo (std::string);
		std::string getArchivo();
		//Funciones
		int imprimirImagenEnConsola();
	private:
		void dibujarImagen(std::string, HDC*);
		std::string archivo;
};
#endif
