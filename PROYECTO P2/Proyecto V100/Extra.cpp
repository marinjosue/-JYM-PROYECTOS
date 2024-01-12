/***********************************************************************
 UFA - ESPE
 * Module:  Extra.cpp
 * Author:  Chiliquinga Yeshua, Marin Alquinga,Salcedo Micaela
 * Modified: domingo, 17 de diciembre de 2023
 * Purpose: Implementation of the class Extra
 ***********************************************************************/

#include "Extra.h"
#include <iostream>
#include <cstdlib>
#include <fstream>
#include <ctime>
#include <sys/stat.h>
#include <dirent.h>
#include <cstring>
#include <sstream>
#include <string>
#include <regex>
#include <chrono>
#include <vector>
#include <string>
#include <regex>
#include <dirent.h>

void createBackupFolder(const std::string& folderName) {
    if (mkdir(folderName.c_str()) == 0) {
        std::cout << "Carpeta '" << folderName << "' creada exitosamente.\n";
    } else {
        std::cout << "La carpeta'" << folderName << "' ya existe\n";
    }
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
    std::ifstream srcFile("tabla_amortizacion.txt", std::ios::binary);
    std::ofstream dstFile("backup/" + std::string(nombreBackup) + ".txt", std::ios::binary);
    dstFile << srcFile.rdbuf();

    std::cout << "Se realizo una copia de seguridad en la carpeta 'backup'.\n";
}
void imprimirContenidoArchivo(const std::string& nombreArchivo) {
    std::ifstream archivo(nombreArchivo);

    if (!archivo.is_open()) {
        std::cerr << "Error al abrir el archivo: " << nombreArchivo << std::endl;
        return;
    }

    std::string linea;
    while (std::getline(archivo, linea)) {
        std::cout << linea << std::endl;
    }

    archivo.close();
}

void restaurarDesdeBackup(const std::string& archivoOriginal, const std::string& archivoBackup) {
    std::ifstream archivoBackupStream(archivoBackup);

    if (!archivoBackupStream.is_open()) {
        std::cerr << "Error al abrir el archivo de backup: " << archivoBackup << std::endl;
        return;
    }

    std::ofstream archivoOriginalStream(archivoOriginal);

    if (!archivoOriginalStream.is_open()) {
        std::cerr << "Error al abrir el archivo original: " << archivoOriginal << std::endl;
        return;
    }

    // Copiar el contenido del archivo de respaldo al archivo original
    archivoOriginalStream << archivoBackupStream.rdbuf();

    std::cout << "Restauración completada con éxito." << std::endl;

    // Cerrar los archivos
    archivoOriginalStream.close();
    archivoBackupStream.close();
}


std::vector<std::string> listarRespaldos(const std::string& nombreArchivo) {
    std::vector<std::string> respaldos;
    std::string carpetaRespaldos = "backup";
    std::regex formato("\\d{4}-\\d{2}-\\d{2}-\\d{2}-\\d{2}-\\d{2}-" + nombreArchivo);

    DIR* dir;
    struct dirent* ent;

    if ((dir = opendir(carpetaRespaldos.c_str())) != nullptr) {
        while ((ent = readdir(dir)) != nullptr) {
            std::string filename = ent->d_name;
            if (std::regex_search(filename, formato)) {
                respaldos.push_back(filename);
            }
        }
        closedir(dir);
    } else {
        std::cerr << "No se pudo abrir la carpeta '" << carpetaRespaldos << "'" << std::endl;
    }

    return respaldos;
}


void restaurarRespaldo(const std::string& nombreArchivo, const std::string& archivoRespaldo) {
    std::string carpetaRespaldos = "backup/";
    std::string rutaArchivoOriginal = nombreArchivo;

    std::string rutaRespaldo = carpetaRespaldos + archivoRespaldo + ".txt";

    std::ifstream respaldo(rutaRespaldo);
    std::ofstream archivoOriginal(rutaArchivoOriginal);

    if (!respaldo.is_open()) {
        std::cerr << "Error: No se pudo abrir el archivo de respaldo '" << rutaRespaldo << "'" << std::endl;
        return;
    }

    if (!archivoOriginal.is_open()) {
        std::cerr << "Error: No se pudo abrir el archivo original '" << rutaArchivoOriginal << "'" << std::endl;
        respaldo.close();
        return;
    }

    archivoOriginal << respaldo.rdbuf(); // Copiar contenido del respaldo al archivo original
    respaldo.close();
    archivoOriginal.close();

    std::cout << "El respaldo '" << archivoRespaldo << "' ha sido restaurado correctamente en '" << nombreArchivo << "'." << std::endl;
}
void imprimirRespaldos(const std::vector<std::string>& respaldos) {
    if (respaldos.empty()) {
        std::cout << "No hay respaldos disponibles." << std::endl;
    } else {
        std::cout << "Respaldos disponibles:" << std::endl;

        for (const std::string& respaldo : respaldos) {
            std::cout << respaldo << std::endl;
        }
    }
}

std::vector<std::string> listarArchivosTXT(const std::string& carpeta) {
    std::vector<std::string> archivosTXT;
    std::regex formato("\\d{4}-\\d{2}-\\d{2}_\\d{2}-\\d{2}-\\d{2}\\.txt");

    DIR* dir;
    struct dirent* ent;

    if ((dir = opendir(carpeta.c_str())) != nullptr) {
        while ((ent = readdir(dir)) != nullptr) {
            std::string filename = ent->d_name;
            if (std::regex_match(filename, formato)) {
                archivosTXT.push_back(filename);
            }
        }
        closedir(dir);
    } else {
        std::cerr << "No se pudo abrir la carpeta '" << carpeta << "'" << std::endl;
    }

    return archivosTXT;
}

void imprimirArchivosTXT(const std::vector<std::string>& archivos) {
    if (archivos.empty()) {
        std::cout << "No hay archivos TXT disponibles en la carpeta 'backup'." << std::endl;
    } else {
        std::cout << "Archivos TXT disponibles en la carpeta 'backup':" << std::endl;

        for (const std::string& archivo : archivos) {
            std::cout << archivo << std::endl;
        }
    }
}
