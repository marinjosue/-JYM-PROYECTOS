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

bool Cuenta::compararCuentas(const std::string& cuenta) {
    std::ifstream archivo("Usuarios.txt");
    std::string cuentaArchivo;

    if (archivo.is_open()) {
        while (archivo >> cuentaArchivo) {
            // Comparar la cuenta actual con la cuenta ingresada
            if (cuenta == cuentaArchivo) {
                archivo.close();
                return true;  // La cuenta ya existe en el archivo
            }
            // Leer los otros campos (nombre, apellido, cédula) y descartarlos
            archivo >> cuentaArchivo;
            archivo >> cuentaArchivo;
            archivo >> cuentaArchivo;
        }
        archivo.close();
    }
    return false;
}
Cuenta Cuenta::crear_cuenta() {
    Movimientos monto;
    validaciones valida;
    Cuenta nuevacuenta;
    Persona nuevaPersona;
    std::string cedula, cedulaArchivo, nombreCompleto, id;

    bool procesarCedula = true;  // Flag to control the loop

    do {
        // Step 1: Ingresar el número de cedula
        cedula = valida.ingresar_numeros_como_string("\nIngrese el numero de cedula: ");

        // Step 2: Validar la cédula en Personas.txt y que no exista en Usuarios.txt
        if (valida.validarCedula(cedula) && nuevacuenta.verificarCedula("Personas.txt", cedula) && !nuevacuenta.verificarCedula("Usuarios.txt", cedula)) {
            // Step 3: Leer información de Personas.txt
            std::ifstream archivo("Personas.txt");
            std::string linea;

            bool cedulaEncontrada = false;

            if (archivo.is_open()) {
                // Leer cada línea del archivo
                while (std::getline(archivo, linea)) {
                    std::istringstream iss(linea);
                    iss >> cedulaArchivo;  // Leer la cédula
                    std::string idTemporal;
                    std::string nombreApellido;

                    // Extract ID and concatenate names and surnames
                    while (iss >> idTemporal) {
                        if (isdigit(idTemporal[0])) {
                            id = idTemporal;
                        } else {
                            nombreApellido += idTemporal + " ";
                        }
                    }

                    // Eliminar el espacio extra al final del nombre completo
                    nombreCompleto = nombreApellido.substr(0, nombreApellido.size() - 1);

                    // Comparar la cédula ingresada con la cédula en la línea actual
                    if (cedulaArchivo == cedula && !nuevacuenta.verificarCedula("Usuarios.txt", cedula)) {
                        Cuenta nuevaCuenta;
                        std::string newCuenta = nuevaCuenta.generar_cuenta_automatica();
                        std::cout << "\nSu cuenta es: " << newCuenta << std::endl;
                        nuevaCuenta.setCuenta(newCuenta);

                        std::cout << "\nDatos encontrados:\n";
                        std::cout << "Cedula: " << cedulaArchivo << "\n";
                        std::cout << "Nombre: " << nombreCompleto << "\n";
                        std::cout << "ID: " << id << "\n";
                        archivo.close();
                        nuevaCuenta.guardarTabla("Usuarios.txt", cedulaArchivo, nombreCompleto, id, nuevaCuenta);
                        monto.registrarMovimiento(cedulaArchivo);
                        cedulaEncontrada = true;
                        procesarCedula = false;  // Set the flag to false to exit the loop
                        break;  // Salir del bucle si ya existe en Usuarios.txt
                    }
                }
                archivo.close();
                if (!cedulaEncontrada) {
                    // Si no se encuentra la cedula en Personas.txt
                    std::cerr << "\nError: La cedula ingresada no fue encontrada en Personas.txt.\n";
                    procesarCedula = false;
                }
            } else {
                std::cerr << "\nError: No se pudo abrir el archivo Personas.txt\n";
                procesarCedula = false;
            }
        } else {
            // Si la cedula es invalida o ya existe en Usuarios.txt
            std::cerr << "\nError: La cedula ingresada es invalida o ya existe en Usuarios.txt. Vuelva a intentarlo.\n";
            procesarCedula = false;
        }
    } while (procesarCedula);

    // Return a dummy account if needed (replace this with your actual return logic)
    return Cuenta();
}




bool Cuenta::verificarCedula(const std::string& archivo, const std::string& cedula) {
    std::ifstream archivoCuentas(archivo);
    std::string linea;

    if (archivoCuentas.is_open()) {
        while (std::getline(archivoCuentas, linea)) {
            std::istringstream iss(linea);
            std::string cedulaArchivo;

            // Extraer la cédula de la línea
            iss >> cedulaArchivo;

            // Comparar la cédula ingresada con la cédula en la línea actual
            if (cedulaArchivo == cedula) {
                archivoCuentas.close();
                return true;  // Cédula encontrada, es duplicada
            }
        }

        archivoCuentas.close();
    } else {
        std::cerr << "\nError: No se pudo abrir el archivo " << archivo << "\n";
    }

    return false;  // La cédula no está duplicada
}



bool Cuenta::verificarCedulaA(const std::string& nombreArchivo, const std::string& cedula) {
    std::ifstream archivo(nombreArchivo);
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
        // El ultimo token leido es el ID
        // Leer el NCuenta
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

        // Verificar si la cedula ingresada coincide con la c�dula del archivo
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


