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
#include <algorithm>
#include "validaciones.h"
#include "ListaDoble.h"
using namespace std;

std::string Persona::generarSiguienteId(const std::string& ultimoIdUtilizado) {
    // Extraer el último número del ID utilizado
    std::string numeroStr = ultimoIdUtilizado.substr(ultimoIdUtilizado.size() - 6);

    // Convertir el número a entero
    int ultimoNumero = std::stoi(numeroStr);

    // Incrementar el último número utilizado
    ++ultimoNumero;

    // Convertir el nuevo número a cadena y formatearlo con ceros a la izquierda
    std::ostringstream oss;
    oss << std::setfill('0') << std::setw(6) << ultimoNumero;

    return oss.str();
}

std::string Persona::obtenerUltimoIdUtilizado(const std::string& nombreArchivo2) {
    std::ifstream archivo(nombreArchivo2);
    std::string linea;
    std::string ultimoId = "000000"; // Establecer un ID inicial mínimo

    if (archivo.is_open()) {
        while (getline(archivo, linea)) {
            // Buscar el último espacio en blanco que precede al ID
            size_t pos = linea.find_last_of(' ');

            if (pos != std::string::npos) {
                // Extraer el ID desde la posición encontrada hasta el final de la línea
                std::string id = linea.substr(pos + 1);

                // Actualizar el último ID si el ID actual es mayor
                if (id > ultimoId) {
                    ultimoId = id;
                }
            }
        }
        archivo.close();
    }

    return ultimoId;
}


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

std::string Persona::getNombre(void)const
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

std::string Persona::getApellido(void)const
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

std::string Persona::getCedula(void)const
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

std::string Persona::getId(void)const
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

    std::ostringstream oss;
    oss << std::setfill('0') << std::setw(6) << ++contadorId;

    return oss.str();
}

/**
 * @brief Ingresa una nueva persona y la guarda en un archivo de texto.
 */

bool Persona::verificarCedula(const std::string& cedula) {
    std::ifstream archivo("Personas.txt");
    std::string cedulaArchivo;

    if (archivo.is_open()) {
        while (archivo >> cedulaArchivo) {
            // Comparar la cédula actual con la cédula ingresada
            if (cedula == cedulaArchivo) {
                archivo.close();
                return true;  // La cédula ya existe en el archivo
            }

            // Leer los otros campos (nombre, apellido, id) y descartarlos
            archivo >> cedulaArchivo;  // nombre
            archivo >> cedulaArchivo;  // apellido
            archivo >> cedulaArchivo;  // id
        }
        archivo.close();
    }
    return false;
}


bool Persona::verificarCedulaEnArchivo(const std::string& cedula) {
    std::ifstream archivo("Personas.txt");
    std::string cedulaArchivo;

    if (archivo.is_open()) {
        while (archivo >> cedulaArchivo) {
            // Comparar la cédula actual con la cédula ingresada
            if (cedula == cedulaArchivo) {
                archivo.close();
                return true;  // La cédula ya existe en el archivo
            }

            // Leer los otros campos (nombre, apellido, id) y descartarlos
            archivo >> cedulaArchivo;  // nombre
            archivo >> cedulaArchivo;  // apellido
            archivo >> cedulaArchivo;  // id
        }
        archivo.close();
    } else {
        std::cerr << "\nEl archivo Personas.txt no existe. Se creara automaticamente.\n";
        ofstream nuevoArchivo("Personas.txt");
        nuevoArchivo.close();
    }

    return false;
}
// Función para ingresar una nueva persona
Persona Persona::ingresarPersona(ListaDoble<Persona*>& listaPersonas) {
    std::string nombreArchivo2 = "Personas.txt";
    std::string ultimoIdUtilizado = obtenerUltimoIdUtilizado(nombreArchivo2);
    std::cout << "Ultimo ID utilizado: " << ultimoIdUtilizado << std::endl;
    validaciones valida;
    std::string newCedula, newNombre, newApellido, newId, datos;
    // Crear un objeto Persona sin inicializar
    Persona nuevaPersona;
    // Input and validation for Cédula
    do {
        newCedula = valida.ingresar_numeros_como_string("\nIngrese el numero de cedula: ");

        if (valida.validarCedula(newCedula)) {
            if (!verificarCedulaEnArchivo(newCedula)) {
                nuevaPersona.setCedula(newCedula);
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

            // Generar el siguiente ID utilizando el último ID utilizado
            Persona persona;
            newId = persona.generarSiguienteId(ultimoIdUtilizado);
            std::cout << "\nSu cuenta es: " << newId << std::endl;

                break;
            } else {
                cout << "\nLa cedula ingresada ya existe en el archivo. Vuelva a intentarlo." << endl;
            }
        } else {
            cout << "\nLa cedula ingresada es invalida. Vuelva a intentarlo." << endl;
        }
    } while (true);

    nuevaPersona.setId(newId);

    return nuevaPersona;
}



void Persona::mostrarRegistroPersona() {
    validaciones valida;
    std::string lectura = valida.leerArchivoTxt();
    std::stringstream input_stringstream(lectura);

    int ancho_cedula = 12, ancho_nombre = 35, ancho_id = 10;

    std::cout  << '|' << std::setw(ancho_cedula) << std::left << "CEDULA" << '|'
              << std::setw(ancho_nombre) << std::left << "NOMBRE COMPLETO" << '|'
              << std::setw(ancho_id) << std::right << "ID" << '|';
    std::cout << "\n===============================================================" << std::endl;
    std::string cedula, nombreCompleto, id, cuenta;

    while (input_stringstream >> cedula) {
        // Leer el nombre completo hasta encontrar el siguiente campo numérico (ID)
        nombreCompleto = "";
        while (input_stringstream >> id && !isdigit(id[0])) {
            nombreCompleto += id + " ";
        }

        std::cout << '|' << std::setw(ancho_cedula) << std::left << cedula << '|'
                  << std::setw(ancho_nombre) << std::left << nombreCompleto << '|'
                  << std::setw(ancho_id) << std::right << id << '|';
        std::cout<< std::endl;
    }
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
std::istream& operator>>(std::istream& is, Persona& persona) {
    std::string cedula, nombreCompleto, id;

    if (is >> cedula) {
        // Leer el nombre completo hasta encontrar el siguiente campo numérico (ID)
        nombreCompleto = "";
        while (is >> id && !isdigit(id[0])) {
            nombreCompleto += (nombreCompleto.empty() ? "" : " ") + id;
        }

        persona.setCedula(cedula);

        // Divide el nombre completo en nombre y apellido
        size_t pos = nombreCompleto.find_last_of(' ');
        if (pos != std::string::npos) {
            persona.setNombre(nombreCompleto.substr(0, pos));
            persona.setApellido(nombreCompleto.substr(pos + 1));
        } else {
            persona.setNombre(nombreCompleto);
            persona.setApellido("");  // Si no hay espacio, el apellido es una cadena vacía
        }

        persona.setId(id);
    }

    return is;
}


void Persona::ordenarEnArchivo(const std::string& nombreArchivo, bool (*criterio)(Persona, Persona)) {
    // Leer todas las personas desde el archivo
    std::vector<Persona> personas;
    std::ifstream archivoEntrada(nombreArchivo);

    if (!archivoEntrada.is_open()) {
        std::cerr << "No se pudo abrir el archivo: " << nombreArchivo << std::endl;
        return;
    }

    Persona persona;
    while (archivoEntrada >> persona) {
        personas.push_back(persona);
    }

    archivoEntrada.close();
    // Ordenar las personas en memoria
    for (size_t i = 0; i < personas.size() - 1; ++i) {
        size_t minimoIndice = i;

        for (size_t j = i + 1; j < personas.size(); ++j) {
            if (criterio(personas[j], personas[minimoIndice])) {
                minimoIndice = j;
            }
        }

        // Intercambiar personas
        Persona tempPersona = personas[i];
        personas[i] = personas[minimoIndice];
        personas[minimoIndice] = tempPersona;
    }
    // Abrir el archivo en modo truncar para escribir la lista ordenada
    std::ofstream archivoSalida(nombreArchivo, std::ios::trunc);

    if (!archivoSalida.is_open()) {
        std::cerr << "No se pudo abrir el archivo para escribir: " << nombreArchivo << std::endl;
        return;
    }

    // Escribir la lista ordenada en el archivo
    for (const auto& p : personas) {
        archivoSalida << p.getCedula() << ' ' << p.getNombre() << ' ' << p.getApellido() << ' ' << p.getId() << '\n';
    }

    archivoSalida.close();

    std::cout << "Personas ordenadas y guardadas en el archivo " << nombreArchivo << "\n";
}


Persona Persona::cargarDesdeArchivo(const std::string& nombreArchivo, const std::string& cedulaBuscar) const {
    std::ifstream archivo(nombreArchivo);

    std::string cedula, nombre, apellido,id;
    Persona personaEncontrada;

    if (archivo.is_open()) {
        while (archivo >> cedula >> nombre >> apellido >> id) {
            if (cedula == cedulaBuscar) {
                // Encontramos la persona con la cédula deseada
                personaEncontrada.setCedula(cedula);
                personaEncontrada.setNombre(nombre);
                personaEncontrada.setApellido(apellido);
                personaEncontrada.setId(id);

                std::cout << "Persona encontrada en el archivo.\n";
                archivo.close();
                return personaEncontrada;
            }
        }
        std::cerr << "No se encontro la persona con la cedula " << cedulaBuscar << " en el archivo.\n";
        archivo.close();
    } else {
        std::cerr << "No se pudo abrir el archivo " << nombreArchivo << " para leer.\n";
    }
    return personaEncontrada;
}


