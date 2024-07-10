#include "Cuenta.h"
#include "validaciones.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <iomanip>

Cuenta::Cuenta(){
}

std::string Cuenta::getCuenta(void)
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
    validaciones valida;
    Persona nuevaPersona;
    std::string cedulaIngresada;

    // Solicitar la cédula al usuario
    do {
        cedulaIngresada = valida.ingresar_numeros_como_string("\nIngrese el numero de cedula: ");

        if (valida.validarCedula(cedulaIngresada)) {
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
                        // Mostrar los datos y terminar la búsqueda
                        Cuenta nuevaCuenta(cedulaArchivo);
                        nuevaCuenta.setCuenta(id);
                        std::cout << "\nDatos encontrados:\n";
                        std::cout << "Cedula: " << cedulaArchivo << "\n";
                        std::cout << "Nombre: " << nombreCompleto << "\n";
                        std::cout << "ID: " << id << "\n";
                        archivo.close();
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






void Cuenta::guardarTabla(const std::string& nombreArchivo) {
    std::ofstream archivo(nombreArchivo, std::ios::app); // Abre el archivo en modo append

    if (archivo.is_open()) {

        archivo << getCuenta() << "\n";

        archivo.close();
        std::cout << "Cuenta registrada exitosamente en el archivo " << nombreArchivo << "\n";
    } else {
        std::cerr << "No se pudo abrir el archivo " << nombreArchivo << " para escribir\n";
    }
}

void Cuenta::mostrarRegistroCuenta(){
    validaciones valida;
    string line;
    string lectura;

    lectura = valida.leerArchivoTxtCuenta();
    stringstream input_stringstream(lectura);
    cout << "N�Cuenta" << endl;
    cout << "===========================================================================" << endl;
    while (getline(input_stringstream, line, '\n'))
    {
        cout << line << endl;
    }
    cout << "===========================================================================" << endl;
}
int Cuenta::contadorId = 0;
std::string  Cuenta::generar_cuenta_automatica(){

    std::ostringstream oss;
    oss << std::setfill('0') << std::setw(6) << ++contadorId;

    return oss.str();
}

