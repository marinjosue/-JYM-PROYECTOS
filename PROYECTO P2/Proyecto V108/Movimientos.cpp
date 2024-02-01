#include "Movimientos.h"
#include "validaciones.h"
#include "Persona.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <sys/stat.h> // Para crear directorios
#include <cerrno>     // Para manejar errores de sistema

using namespace std;

Movimientos::Movimientos() {}

Movimientos::Movimientos(const std::string& cedula, const std::string& tipoMovimiento, double monto)
    : cedula(cedula), tipoMovimiento(tipoMovimiento), monto(monto) {}

std::string Movimientos::getCedula() const {
    return cedula;
}

void Movimientos::setCedula(const std::string& cedula) {
    this->cedula = cedula;
}

std::string Movimientos::getTipoMovimiento() const {
    return tipoMovimiento;
}

void Movimientos::setTipoMovimiento(const std::string& tipoMovimiento) {
    this->tipoMovimiento = tipoMovimiento;
}

double Movimientos::getMonto() const {
    return monto;
}

void Movimientos::setMonto(double monto) {
    this->monto = monto;
}

void Movimientos::registrarMovimiento(const std::string& cedulaIngresada) {
    validaciones valida;
    Persona nuevaPersona;

    // Crear la carpeta "Usuarios" si no existe
    std::string carpetaUsuarios = "Usuarios";
    if (!directorioExiste(carpetaUsuarios)) {
        if (crearDirectorio(carpetaUsuarios)) {
            std::cout << "Carpeta de usuarios creada correctamente." << std::endl;
        } else {
            std::cerr << "Error al crear la carpeta de usuarios." << std::endl;
            return;
        }
    }

    // Solicitar la cédula al usuario
    do {
        double montoIngresado = valida.ingresar_enteros("\nIngrese el monto a registrar ($): ");
        if (montoIngresado != 5.0) {
            std::cout << "Solo se permite registrar un monto de $5." << std::endl;
            return;
        }

        std::ifstream archivo("Personas.txt");
        std::string linea;

        if (archivo.is_open()) {
            // Leer cada línea del archivo
            while (std::getline(archivo, linea)) {
                std::istringstream iss(linea);
                std::string cedulaArchivo, nombreCompleto, id;

                // Leer los componentes de la línea
                iss >> cedulaArchivo;  // Leer la cédula
                std::string nombreApellido;
                while (iss >> nombreApellido) {
                    // Si el componente actual es numérico, es el ID, no el nombre
                    if (!isdigit(nombreApellido[0])) {
                        // Concatenar los nombres y apellidos en uno solo
                        nombreCompleto += nombreApellido + " ";
                    } else {
                        id = nombreApellido;
                    }
                }
                // Eliminar el espacio extra al final del nombre completo
                nombreCompleto.pop_back();

                // Comparar la cédula ingresada con la cédula en la línea actual
                if (cedulaArchivo == cedulaIngresada) {
                    std::string nombreArchivo = carpetaUsuarios + "/" + cedulaIngresada + ".txt";
                    std::ofstream outFile(nombreArchivo, std::ios::app);
                    if (outFile.is_open()) {
                        outFile << "Cedula: " << cedulaArchivo << "\n";
                        outFile << "Nombre: " << nombreCompleto << "\n";
                        outFile << "ID: " << id << "\n";
                        outFile.close();
                        std::cout << "Datos guardados en " << nombreArchivo << std::endl;
                    } else {
                        std::cerr << "No se pudo abrir el archivo " << nombreArchivo << std::endl;
                    }
                    archivo.close();
                    return;
                }
            }
            archivo.close();
            std::cout << "\nLa cedula ingresada no existe en el archivo. Vuelva a intentarlo." << std::endl;
        } else {
            std::cerr << "No se pudo abrir el archivo Personas.txt\n";
        }
    } while (true);
}

bool Movimientos::directorioExiste(const std::string& nombreDirectorio) {
    struct stat info;
    if (stat(nombreDirectorio.c_str(), &info) != 0) {
        return false;
    }
    return (info.st_mode & S_IFDIR) != 0;
}

bool Movimientos::crearDirectorio(const std::string& nombreDirectorio) {
    int resultado = mkdir(nombreDirectorio.c_str());
    if (resultado == -1) {
        std::cerr << "Error al crear el directorio: " << strerror(errno) << std::endl;
        return false;
    }
    return true;
}
void Movimientos::mostrarMovimientos() {
    // Implementa la lógica para mostrar los movimientos realizados
}
