/***********************************************************************
 UFA - ESPE
 * Module:  CalculosCredito.cpp
 * Author:  Chiliquinga Yeshua, Marin Alquinga,Salcedo Micaela
 * Modified: domingo, 17 de diciembre de 2023
 * Purpose: Implementation of the class Nodo
 ***********************************************************************/

#ifndef EXTRAS_H
#define EXTRAS_H
#include <string>
#include <vector>
#include <filesystem>
#include <fstream>

void createFile();
void createBackup();
void createBackupRegistro();
std::string leerArchivoComoString(const std::string& nombreArchivo);
void imprimirContenidoArchivo(const std::string& nombreArchivo);
void restaurarDesdeBackup(const std::string& archivoOriginal, const std::string& archivoBackup);
void imprimirContenidoArchivo(const std::string& nombreArchivo);



#endif // EXTRAS_H
