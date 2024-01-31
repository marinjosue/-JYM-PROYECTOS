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

    string newCuenta;
     Cuenta cuent;
     newCuenta = cuent.generar_cuenta_automatica();
    std::cout << "\nSu cuenta es: " << newCuenta << std::endl;

    cuent.setCuenta(newCuenta);


    return cuent;
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
    cout << "N°Cuenta" << endl;
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

