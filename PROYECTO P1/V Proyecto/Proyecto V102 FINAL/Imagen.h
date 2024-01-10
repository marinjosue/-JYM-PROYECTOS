/*************************
        UFA - ESPE
 * Module:  Imagen.h
 * Author:  Chiliquinga Yeshua, Marin Alquinga,Salcedo Micaela
 * Modified: domingo, 17 de diciembre de 2023
 * Purpose: Declaracion de Encabezado Imagen
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
