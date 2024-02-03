#include "Movimientos.h"
#include "validaciones.h"
#include "Persona.h"
#include "Cuenta.h"
#include "Fecha.h"
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
    Cuenta nuevacuenta;
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
    // Solicitar el monto al usuario
    double montoIngresado = valida.ingresar_reales("\nIngrese el monto a registrar ($): ");
    if (montoIngresado != 5.0) {
        std::cout << "\nSolo se permite registrar un monto de $5.\n" << std::endl;
        return;
    }
    // Obtener datos del usuario
    DatosUsuario datosUsuario = nuevacuenta.mostrarDatosUsuarios("Usuarios.txt", cedulaIngresada);
    if (datosUsuario.cedula.empty()) {
        std::cout << "\nLa cedula ingresada no existe en el archivo. Vuelva a intentarlo." << std::endl;
        return;
    }
    // Obtener la fecha actual
    Fecha fechaActual;
    std::string nombreArchivo = carpetaUsuarios + "/" + cedulaIngresada + ".txt";
    // Abrir el archivo de usuario en modo de añadir (append)
    std::ofstream outFile(nombreArchivo, std::ios::app);
    if (outFile.is_open()) {
        // Escribir los datos en el archivo
        outFile << "Fecha: " << fechaActual.to_string() << "\n";
        outFile << "Monto: $" << montoIngresado << "\n";
        outFile << "Cedula: " << datosUsuario.cedula << "\n";
        outFile << "Nombre: " << datosUsuario.nombreCompleto << "\n";
        outFile << "ID: " << datosUsuario.id << "\n";
        outFile << "No.Cuenta: " << datosUsuario.Ncuenta << "\n";
        outFile << "\n";
        std::cout << "\nDatos guardados en " << nombreArchivo << std::endl;
        outFile.close();
    } else {
        std::cerr << "\nNo se pudo abrir el archivo " << nombreArchivo << std::endl;
    }
}

void Movimientos::mostrarMovimientosPorCedula() {
    // Solicitar el número de cédula al usuario
    std::string cedulaIngresada;
    std::cout << "Ingrese su numero de cedula: ";
    std::cin >> cedulaIngresada;

    // Construir el nombre del archivo correspondiente
    std::string nombreArchivo = "Usuarios/" + cedulaIngresada + ".txt";
    // Intentar abrir el archivo
    std::ifstream inFile(nombreArchivo);
    if (inFile.is_open()) {
        // Leer y mostrar el contenido del archivo línea por línea
        std::string linea;
        std::cout << "\nContenido del archivo " << nombreArchivo << ":\n";
        while (std::getline(inFile, linea)) {
            std::cout << linea << std::endl;
        }
        inFile.close();
    } else {
        std::cerr << "\nNo se pudo abrir el archivo " << nombreArchivo << ". Puede que no exista o haya un error." << std::endl;
    }
}

void Movimientos::tablaMoviemito(){

}

void Movimientos::pagoPrestamoAutomatico(){


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
