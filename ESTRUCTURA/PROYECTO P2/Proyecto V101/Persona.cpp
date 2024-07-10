/***********************************************************************
 * Module:  Persona.cpp
 * Author:  Usuario
 * Modified: domingo, 7 de enero de 2024 0:07:18
 * Purpose: Implementation of the class Persona
 ***********************************************************************/

#include "Persona.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <iomanip>
#include "validaciones.h"
#include "ListaDoble.h"

using namespace std;
int Persona::contadorId = 0;


////////////////////////////////////////////////////////////////////////
// Name:       Persona::Persona()
// Purpose:    Implementation of Persona::Persona()
// Return:
////////////////////////////////////////////////////////////////////////

Persona::Persona()
{
}

////////////////////////////////////////////////////////////////////////
// Name:       Persona::~Persona()
// Purpose:    Implementation of Persona::~Persona()
// Return:
////////////////////////////////////////////////////////////////////////

Persona::~Persona()
{
   // TODO : implement
}

////////////////////////////////////////////////////////////////////////
// Name:       Persona::getNombre()
// Purpose:    Implementation of Persona::getNombre()
// Return:     std::string
////////////////////////////////////////////////////////////////////////

std::string Persona::getNombre(void)
{
   return Nombre;
}

////////////////////////////////////////////////////////////////////////
// Name:       Persona::setNombre(std::string newNombre)
// Purpose:    Implementation of Persona::setNombre()
// Parameters:
// - newNombre
// Return:     void
////////////////////////////////////////////////////////////////////////

void Persona::setNombre(std::string newNombre)
{
   Nombre = newNombre;
}

////////////////////////////////////////////////////////////////////////
// Name:       Persona::getApellido()
// Purpose:    Implementation of Persona::getApellido()
// Return:     std::string
////////////////////////////////////////////////////////////////////////

std::string Persona::getApellido(void)
{
   return Apellido;
}

////////////////////////////////////////////////////////////////////////
// Name:       Persona::setApellido(std::string newApellido)
// Purpose:    Implementation of Persona::setApellido()
// Parameters:
// - newApellido
// Return:     void
////////////////////////////////////////////////////////////////////////

void Persona::setApellido(std::string newApellido)
{
   Apellido = newApellido;
}

////////////////////////////////////////////////////////////////////////
// Name:       Persona::getCedula()
// Purpose:    Implementation of Persona::getCedula()
// Return:     std::string
////////////////////////////////////////////////////////////////////////

std::string Persona::getCedula(void)
{
   return Cedula;
}

////////////////////////////////////////////////////////////////////////
// Name:       Persona::setCedula(std::string newCedula)
// Purpose:    Implementation of Persona::setCedula()
// Parameters:
// - newCedula
// Return:     void
////////////////////////////////////////////////////////////////////////

void Persona::setCedula(std::string newCedula)
{
   Cedula = newCedula;
}

////////////////////////////////////////////////////////////////////////
// Name:       Persona::getId()
// Purpose:    Implementation of Persona::getId()
// Return:     std::string
////////////////////////////////////////////////////////////////////////

std::string Persona::getId(void)
{
   return Id;
}

////////////////////////////////////////////////////////////////////////
// Name:       Persona::setId(std::string newId)
// Purpose:    Implementation of Persona::setId()
// Parameters:
// - newId
// Return:     void
////////////////////////////////////////////////////////////////////////

void Persona::setId(std::string newId)
{
   Id = newId;
}

////////////////////////////////////////////////////////////////////////
// Name:       Persona::Persona(const Persona& oldPersona)
// Purpose:    Implementation of Persona::Persona()
// Parameters:
// - oldPersona
// Return:
////////////////////////////////////////////////////////////////////////

// Implementación de los constructores modificados
Persona::Persona(std::string Nombre, std::string Apellido, std::string Cedula)
    : Nombre(Nombre), Apellido(Apellido), Cedula(Cedula) {
    this->id = generarSiguienteId();
}

Persona::Persona(std::string Nombre, std::string Apellido, std::string Cedula, std::string Id)
    : Nombre(Nombre), Apellido(Apellido), Cedula(Cedula), Id(Id) {
    // Actualizar el contadorId si es necesario
    int idValor = std::stoi(Id.substr(1));
    if (idValor > contadorId) {
        contadorId = idValor;
    }
}

std::string Persona::generarSiguienteId() {
    // Formatear el ID según la lógica deseada (por ejemplo, L000000)
    std::ostringstream oss;
    oss << "L" << std::setfill('0') << std::setw(6) << ++contadorId;
    return oss.str();
}

/**
 * @brief Ingresa una nueva persona y la guarda en un archivo de texto.
 */

#include <fstream>

// ... (other includes and code)

Persona Persona::ingresarPersona(ListaDoble<Persona*>& listaPersonas) {
     validaciones valida;
    std::string newCedula, newNombre, newApellido, newId,datos;

    // Crear un objeto Persona sin inicializar
    Persona nuevaPersona;

    // Input and validation for C�dula
    do {
        newCedula = valida.ingresar_numeros_como_string("\nIngrese el numero de cedula: ");

        if (valida.validarCedula(newCedula)) {
            if (listaPersonas.buscarCedulaExistente(newCedula)) {
                nuevaPersona.setCedula(newCedula);
                break; // C�dula is valid and not duplicate
            } else {
                cout << "\nLa cedula ingresada ya existe. Vuelva a intentarlo." << endl;
            }
        } else {
            cout << "\nLa cedula ingresada es invalida. Vuelva a intentarlo." << endl;
        }
    } while (true);

    // Input and validation for Nombre
    do {
        newNombre = valida.mayusculas_primeras(valida.ingresar_alfabetico_con_un_espacio("\nIngrese el nombre: "));
        if (newNombre.empty()) {
            cout << "\nEl nombre no puede estar vacio. Vuelva a intentarlo." << endl;
        } else {
            nuevaPersona.setNombre(newNombre);
            break; // Nombre is not empty
        }
    } while (true);

    // Input and validation for Apellido
    do {
        newApellido = valida.mayusculas_primeras(valida.ingresar_alfabetico_con_un_espacio("\nIngrese el apellido: "));
        if (newApellido.empty()) {
            cout << "\nEl apellido no puede estar vacio. Vuelva a intentarlo." << endl;
        } else {
            nuevaPersona.setApellido(newApellido);
            break; // Apellido is not empty
        }
    } while (true);

    // Automatically generate the ID using the member function of ListaDoble
    newId = Persona::generarSiguienteId();
    std::cout << "\nSu id unico es: " << newId << std::endl;

    nuevaPersona.setId(newId);


    datos= newCedula + " "+ newNombre+" " + newApellido+" " + newId+" " + "\n";

    std::ofstream archivo("personas.txt", std::ios::app);
    if (archivo.is_open()) {
        archivo << newCedula << " ";
        archivo << newNombre << " ";
        archivo << newApellido << " ";
        archivo << newId << "\n";
        archivo.close();
        std::cout << "Persona registrada exitosamente en el archivo personas.txt\n";
    } else {
        std::cerr << "No se pudo abrir el archivo personas.txt para escribir\n";
    }

    return nuevaPersona;
}

void Persona::guardarEnArchivo(const std::string& nombreArchivo) {
    std::ofstream archivo(nombreArchivo, std::ios::app); // Abre el archivo en modo append

    if (archivo.is_open()) {
        archivo << getCedula() << " ";
        archivo << getNombre() << " ";
        archivo << getApellido() << " ";
        archivo << getId() << "\n";

        archivo.close();
        std::cout << "Persona registrada exitosamente en el archivo " << nombreArchivo << "\n";
    } else {
        std::cerr << "No se pudo abrir el archivo " << nombreArchivo << " para escribir\n";
    }
}

void Persona::mostrarRegistroPersona(){
     validaciones valida;
    string line;
    string lectura;

    lectura = valida.leerArchivoTxt();
    stringstream input_stringstream(lectura);
    cout << "Cedula    Nombre    Apellido   Fecha" << endl;
    cout << "===========================================================================" << endl;
    while (getline(input_stringstream, line, '\n'))
    {
        cout << line << endl;
    }
    cout << "===========================================================================" << endl;
}


// datos= cedula + " "+ nombre+" " + apellido+" " + "\n";

/*
 std::ofstream archivo("personas.txt", std::ios::app);
    if (archivo.is_open()) {
        archivo << cedula << " ";
        archivo << nombre << " ";
        archivo << apellido << " ";
        archivo << id << "\n";
        archivo.close();
        std::cout << "Persona registrada exitosamente en el archivo personas.txt\n";
    } else {
        std::cerr << "No se pudo abrir el archivo personas.txt para escribir\n";
    }*/
