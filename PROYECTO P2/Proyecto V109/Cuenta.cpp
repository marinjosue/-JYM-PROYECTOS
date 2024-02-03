#include "Cuenta.h"
#include "validaciones.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <iomanip>
#include "Movimientos.h"

Cuenta::Cuenta(){
}
std::string Cuenta::getCuenta(void)const
{
   return cuenta;
}
void Cuenta::setCuenta(std::string newCuenta)
{
   cuenta = newCuenta;
}

Cuenta::Cuenta(std::string cuenta)
    :  cuenta(cuenta) {
         int contadorId=0;
    // Actualizar el contadorId si es necesario
    int idValor = std::stoi(cuenta.substr(1));
    if (idValor > contadorId) {
        contadorId = idValor;
    }
}

Cuenta Cuenta::crear_cuenta() {
    Movimientos monto;
    validaciones valida;
    Persona nuevaPersona;
    std::string cedulaIngresada;

    // Solicitar la c�dula al usuario
    do {
        cedulaIngresada = valida.ingresar_numeros_como_string("\nIngrese el numero de cedula: ");

        if (valida.validarCedula(cedulaIngresada)) {
            std::ifstream archivo("Personas.txt");
            std::string linea;

            if (archivo.is_open()) {
                // Leer cada l�nea del archivo
                while (std::getline(archivo, linea)) {
                    std::istringstream iss(linea);
                    std::string cedulaArchivo, nombreCompleto, id;

                    // Leer los componentes de la l�nea
                    iss >> cedulaArchivo;  // Leer la c�dula
                    std::string nombreApellido;
                    while (iss >> nombreApellido) {
                        // Si el componente actual es num�rico, es el ID, no el nombre
                        if (!isdigit(nombreApellido[0])) {
                            // Concatenar los nombres y apellidos en uno solo
                            nombreCompleto += nombreApellido + " ";
                        } else {
                            id = nombreApellido;
                        }
                    }
                    // Eliminar el espacio extra al final del nombre completo
                    nombreCompleto.pop_back();

                    // Comparar la c�dula ingresada con la c�dula en la l�nea actual
                    if (cedulaArchivo == cedulaIngresada) {
                        Cuenta nuevaCuenta;
                        std::string newCuenta = nuevaCuenta.generar_cuenta_automatica();
                        std::cout << "\nSu cuenta es: " << newCuenta << std::endl;
                        nuevaCuenta.setCuenta(newCuenta);

                        std::cout << "\nDatos encontrados:\n";
                        std::cout << "Cedula: " << cedulaArchivo << "\n";
                        std::cout << "Nombre: " << nombreCompleto << "\n";
                        std::cout << "ID: " << id << "\n";
                        archivo.close();
                        nuevaCuenta.guardarTabla("Usuarios.txt",cedulaArchivo ,nombreCompleto,id, nuevaCuenta);
                        monto.registrarMovimiento(cedulaIngresada);
                        return nuevaCuenta;
                    }
                }
                archivo.close();
                std::cout << "\nLa cedula ingresada no existe en el archivo. Vuelva a intentarlo." << std::endl;
            } else {
                std::cerr << "No se pudo abrir el archivo Personas.txt\n";
            }
        } else {
            std::cout << "\nLa cedula ingresada es invalida. Vuelva a intentarlo." << std::endl;
        }
    } while (true);
}

void Cuenta::guardarTabla(const std::string& archivo, const std::string& cedula, const std::string& nombreCompleto, const std::string& id, const Cuenta& cuenta) {
    std::ofstream outFile(archivo, std::ios::app);
    if (outFile.is_open()) {
        outFile << cedula << " "
                << nombreCompleto << " "
                << id << " "
                << cuenta.getCuenta() << "\n";

        outFile.close();
        std::cout << "Datos guardados en " << archivo << std::endl;
        // L�nea en blanco opcional
        std::cout << std::endl;
    } else {
        std::cerr << "No se pudo abrir el archivo " << archivo << std::endl;
    }
}
void Cuenta::mostrarDatosUsuarios(const std::string& archivo) {
    validaciones valida;
    std::string lectura = valida.leerArchivoTxtCuenta();
    std::stringstream input_stringstream(lectura);

    int ancho_cedula = 12, ancho_nombre = 35, ancho_id = 10, ancho_cuenta = 10;

    std::cout << '|' << std::setw(ancho_cedula) << std::left << "CEDULA" << '|'
              << std::setw(ancho_nombre) << std::left << "NOMBRE COMPLETO" << '|'
              << std::setw(ancho_id) << std::left << "ID" << '|'
              << std::setw(ancho_cuenta) << std::left << "No.Cuenta" << '|';
    std::cout << "\n========================================================" << std::endl;

    std::string cedula, nombreCompleto, id, cuenta;

    while (input_stringstream >> cedula) {
        // Leer el nombre completo hasta encontrar el siguiente campo num�rico (ID)
        nombreCompleto = "";
        while (input_stringstream >> id && !isdigit(id[0])) {
            nombreCompleto += id + " ";
        }

        // El �ltimo token le�do es el ID
        // Leer el N�Cuenta
        input_stringstream >> cuenta;

        std::cout << '|' << std::setw(ancho_cedula) << std::left << cedula << '|'
                  << std::setw(ancho_nombre) << std::left << nombreCompleto << '|'
                  << std::setw(ancho_id) << std::left << id << '|'
                  << std::setw(ancho_cuenta) << std::left << cuenta << '|';

        std::cout << std::endl;
    }
}

DatosUsuario Cuenta::mostrarDatosUsuarios(const std::string& archivo, const std::string& cedulaIngresada) {
    std::ifstream archivoUsuarios(archivo);
    DatosUsuario datosUsuario;  // Estructura para almacenar los datos

    std::string cedulaArchivo, nombreCompleto, id, Ncuenta;

    // Leer cada l�nea del archivo
    while (archivoUsuarios >> cedulaArchivo) {
        // Leer el nombre completo hasta encontrar el siguiente campo num�rico (ID)
        nombreCompleto = "";
        while (archivoUsuarios >> id && !isdigit(id[0])) {
            nombreCompleto += id + " ";
        }

        // El �ltimo token le�do es el ID
        // Leer el N�Cuenta
        archivoUsuarios >> Ncuenta;

        // Eliminar el espacio extra al final del nombre completo
        nombreCompleto.pop_back();

        // Verificar si la c�dula ingresada coincide con la c�dula del archivo
        if (cedulaArchivo == cedulaIngresada) {
            // Asignar los datos a la estructura
            datosUsuario.cedula = cedulaArchivo;
            datosUsuario.nombreCompleto = nombreCompleto;
            datosUsuario.id = id;
            datosUsuario.Ncuenta = Ncuenta;

            break;  // Salir del bucle al encontrar la c�dula
        }
    }

    archivoUsuarios.close();

    // Devolver la estructura con los datos
    return datosUsuario;
}

bool Cuenta::verificarCedula(const std::string& cedula) {
    std::ifstream archivo("Usuarios.txt");
    std::string cedulaArchivo;

    if (archivo.is_open()) {
        while (archivo >> cedulaArchivo) {
            // Comparar la c�dula actual con la c�dula ingresada
            if (cedula == cedulaArchivo) {
                archivo.close();
                return true;  // La c�dula ya existe en el archivo
            }
            // Leer los otros campos (nombre, apellido, id) y descartarlos
            archivo >> cedulaArchivo;
            archivo >> cedulaArchivo;
            archivo >> cedulaArchivo;
        }
        archivo.close();
    }
    return false;
}
int contadorCuenta = 2024;
int codigoV = 0;

std::string Cuenta::generar_cuenta_automatica() {
    // Numero de cuenta = 009 10 2024 0   y el 10 se va incrementando
    std::ostringstream oss;
    int digitoVerificador = ++codigoV % 10;

    if (digitoVerificador == 10) {
        digitoVerificador = 0;
        ++codigoV;
    }

    oss << "009" <<  digitoVerificador << std::setfill('0') << std::setw(5) << ++contadorCuenta << digitoVerificador;
    return oss.str();
}


