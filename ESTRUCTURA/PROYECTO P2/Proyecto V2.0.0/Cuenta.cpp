/***********************************************************************
 UFA - ESPE
 * Module:  Cuenta.cpp
 * Author:  Chiliquinga Yeshua, Marin Alquinga,Salcedo Micaela
 * Modified: domingo, 4 de enero de 2024
 * Purpose: Implementation of the class Cuenta
 ***********************************************************************/
#include "Cuenta.h"
#include "validaciones.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <iomanip>
#include <limits>
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

// Lee el archivo de usuarios y devuelve el último número de cuenta generado como una cadena
std::string obtener_ultimo_numero_cuenta(const std::string& archivo) {
    std::ifstream archivo_usuarios(archivo);
    std::string linea;
    std::string ultimo_numero = "0"; // Inicializar como cadena

    if (archivo_usuarios.is_open()) {
        while (std::getline(archivo_usuarios, linea)) {
            std::istringstream iss(linea);
            std::string cuenta;
            while (iss >> cuenta) {
                // Extraer el número de cuenta de la línea
                // Suponiendo que el formato del archivo es: cedula nombre id cuenta
                if (isdigit(cuenta[0])) {
                    if (cuenta > ultimo_numero) {
                        ultimo_numero = cuenta;
                    }
                }
            }
        }
        archivo_usuarios.close();
    }

    return ultimo_numero;
}
Cuenta Cuenta::crear_cuenta() {
    Movimientos monto;
    validaciones valida;
    Cuenta nuevacuenta;
    Persona nuevaPersona;
    std::string cedula, cedulaArchivo, nombreCompleto, id;

    // Obtener el último número de cuenta generado
    std::string ultimo_numero = obtener_ultimo_numero_cuenta("Usuarios.txt");

    // Continuar generando cuentas desde el último número generado + 1
    int siguiente_numero = std::stoi(ultimo_numero) + 1;

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
                        // Generar un número de cuenta único
                        std::string newCuenta = "009" + std::to_string(siguiente_numero);
                        nuevacuenta.setCuenta(newCuenta);

                        std::cout << "\nDatos encontrados:\n";
                        std::cout << "Cedula: " << cedulaArchivo << "\n";
                        std::cout << "Nombre: " << nombreCompleto << "\n";
                        std::cout << "ID: " << id << "\n";
                        archivo.close();
                        nuevacuenta.guardarTabla("Usuarios.txt", cedulaArchivo, nombreCompleto, id, nuevacuenta);
                        monto.registrarMovimiento(cedulaArchivo,0.0);
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
    }
    return false;  // La cédula no está duplicada
}

bool Cuenta::verificarCedulaA(const std::string& nombreArchivo, const std::string& cedula) {
    std::ifstream archivo(nombreArchivo);
    std::string cedulaArchivo;

    if (archivo.is_open()) {
        while (archivo >> cedulaArchivo) {
            // Comparar la cédula actual con la cédula ingresada
            if (cedula == cedulaArchivo) {
                archivo.close();
                return true;  // La cédula ya existe en el archivo
            }
            // Ir al final de la línea para continuar con la siguiente iteración
            archivo.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
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
        std::cout << "\nDatos guardados en " << archivo << std::endl;
        // L�nea en blanco opcional
        std::cout << std::endl;
    } else {
        std::cerr << "\nNo se pudo abrir el archivo " << archivo << std::endl;
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
            //datosUsuario.Prestamo = Prestamo;

            break;  // Salir del bucle al encontrar la c�dula
        }
    }

    archivoUsuarios.close();

    // Devolver la estructura con los datos
    return datosUsuario;
}
// Implementación de la función para generar un número de cuenta único
std::string Cuenta::generar_cuenta_unico() {
    std::string nueva_cuenta;
    bool cuenta_unica = false;

    do {
        nueva_cuenta = generar_cuenta_automatica(); // Supongamos que esto genera el número de cuenta
        // Verifica si la cuenta generada ya existe en Usuarios.txt
        if (!verificar_cuenta_existente(nueva_cuenta, "Usuarios.txt")) {
            cuenta_unica = true;
        }
    } while (!cuenta_unica);

    return nueva_cuenta;
}

// Implementación de la función para verificar si una cuenta ya existe en el archivo dado
bool Cuenta::verificar_cuenta_existente(const std::string& archivo, const std::string& cedula) {
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

int contadorCuenta = 2024;
int codigoV = 0;

std::string Cuenta::generar_cuenta_automatica() {
    std::ostringstream oss;
    
    // Se calcula el dígito verificador con el algoritmo de Luhn
    int digitoVerificador = ++codigoV % 10;

    if (digitoVerificador == 10) {
        digitoVerificador = 0;
        ++codigoV;
    }

    // Incrementar el contador de cuenta
    ++contadorCuenta;

    // Formatear el número de cuenta con ceros a la izquierda
    oss << "009" << std::setfill('0') << std::setw(5) << contadorCuenta << digitoVerificador;

    std::string nuevaCuenta = oss.str();

    // Verificar si la cuenta generada ya existe en el archivo Usuarios.txt
    while (verificar_cuenta_existente("Usuarios.txt", nuevaCuenta)) {
        // Si la cuenta ya existe, generamos una nueva cuenta
        ++contadorCuenta;
        digitoVerificador = ++codigoV % 10;
        if (digitoVerificador == 10) {
            digitoVerificador = 0;
            ++codigoV;
        }
        oss.str(""); // Limpiamos el stringstream
        oss << "009" << std::setfill('0') << std::setw(5) << contadorCuenta << digitoVerificador;
        nuevaCuenta = oss.str();
    }

    return nuevaCuenta;
}
