//*****************//
//***Universidad de Las Fuerzas Armadas ESPE***//
//Estudiante: Karla Ansatuña
//Materia: Estructura de Datos
//NRC:9671
//Descripcion del codigo:
// Funcion que retorna un booleano si es que el numero es palindromo
//Es decir que se lee igual al reves y al derecho
//*****************//
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