/*************************
 UFA - ESPE
 * Module:  createFile.h
 * Author:  Chiliquinga Yeshua, Marin Alquinga,Salcedo Micaela
 * Modified: domingo, 17 de diciembre de 2023
 * Purpose: Implementacion del encabezado createFile
 *************************/


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

#endif // EXTRAS_H
