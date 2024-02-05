/***********************************************************************
 UFA - ESPE
 * Module:  Extra.cpp
 * Author:  Chiliquinga Yeshua, Marin Alquinga,Salcedo Micaela
 * Modified: domingo, 4 de enero de 2024
 * Purpose: Implementation of the class Extra
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
//void listarRespaldos(const std::string& nombreArchivo);
void restaurarRespaldo(const std::string& nombreArchivo, const std::string& archivoRespaldo);
//void listarRespaldos(const std::string& nombreArchivo);
std::vector<std::string> listarRespaldos(const std::string& nombreArchivo);
void imprimirRespaldos(const std::vector<std::string>& respaldos);
std::vector<std::string> listarArchivosTXT(const std::string& carpeta);
void imprimirArchivosTXT(const std::vector<std::string>& archivos);
void createBackupRegistro(const std::string& );


#endif // EXTRAS_H
