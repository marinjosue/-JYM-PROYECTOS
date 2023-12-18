/***********************************************************************
 UFA - ESPE
 * Module:  CalculosCredito.cpp
 * Author:  Chiliquinga Yeshua, Marin Alquinga,Salcedo Micaela
 * Modified: domingo, 17 de diciembre de 2023
 * Purpose: Implementation of the class Nodo
 ***********************************************************************/

#include "Extra.h"
#include <iostream>
#include <fstream>
#include <ctime>
#include <sys/stat.h>
#include <dirent.h>
#include <cstring>
#include <sstream>
#include <string>
#include <chrono>
#include "validaciones.h"

void createBackupFolder(const std::string& folderName) {
    if (mkdir(folderName.c_str()) == 0) {
        std::cout << "Carpeta '" << folderName << "' creada exitosamente.\n";
    } else {
        std::cout << "La carpeta'" << folderName << "' ya existe\n";
    }
}

void createBackup() {
    // Obtener la fecha actual del sistema
    std::time_t tiempoActual = std::time(nullptr);
    std::tm* fechaActual = std::localtime(&tiempoActual);

    // Crear una cadena con el formato de la fecha para usar como nombre del archivo de respaldo
    char nombreBackup[100];
    std::strftime(nombreBackup, sizeof(nombreBackup), "%Y-%m-%d_%H-%M-%S", fechaActual);

    // Crear la carpeta de respaldo
    createBackupFolder("backup");

    // Copiar el archivo a la carpeta de respaldo con el nombre de la fecha del sistema
    std::ifstream srcFile("personas.txt", std::ios::binary);
    std::ofstream dstFile("backup/" + std::string(nombreBackup) + ".txt", std::ios::binary);
    dstFile << srcFile.rdbuf();

    std::cout << "Se realizo una copia de seguridad en la carpeta 'backup'.\n";
}


void createBackupRegistro() {
    // Obtener la fecha actual del sistema
    std::time_t tiempoActual = std::time(nullptr);
    std::tm* fechaActual = std::localtime(&tiempoActual);

       // Obtener el tiempo actual
    auto now = std::chrono::system_clock::now();
    std::time_t now_time = std::chrono::system_clock::to_time_t(now);

    // Aumentar un segundo
    now_time++;

    // Convertir el tiempo incrementado a struct tm
    struct std::tm *incremented_time = std::localtime(&now_time);

    // Crear una cadena con el formato de fecha deseado
    char nombreBackup[100];
    std::strftime(nombreBackup, sizeof(nombreBackup), "%Y-%m-%d_%H-%M-%S", incremented_time);


    // Crear la carpeta de respaldo
    createBackupFolder("backup");

    // Copiar el archivo a la carpeta de respaldo con el nombre de la fecha del sistema
    std::ifstream srcFile("registro.txt", std::ios::binary);
    std::ofstream dstFile("backup/" + std::string(nombreBackup) + ".txt", std::ios::binary);
    dstFile << srcFile.rdbuf();

    std::cout << "Se realizo una copia de seguridad en la carpeta 'backup'.\n";
}




