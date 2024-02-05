// En ArbolBinario.cpp

#include "ArbolBinario.h"
#include <algorithm> // Para std::sort
#include "Cuenta.h"
#include "Fecha.h"
#include <vector>

// Función para extraer y ordenar los números de cédula del archivo
std::vector<std::string> obtenerNumerosCedula(const std::string& archivo) {
    std::ifstream archivo_usuarios(archivo);
    std::vector<std::string> numeros_cedula;

    if (archivo_usuarios.is_open()) {
        std::string linea;
        while (std::getline(archivo_usuarios, linea)) {
            std::istringstream iss(linea);
            std::string cedula;
            // Leemos la primera cadena que se asume es la cédula
            if (iss >> cedula) {
                // Agregamos la cédula al vector
                numeros_cedula.push_back(cedula);
            }
        }
        archivo_usuarios.close();
    }
    // Ordenamos los números de cédula
    std::sort(numeros_cedula.begin(), numeros_cedula.end());
    return numeros_cedula;
}


// Implementación de la clase NodoArbol
NodoArbol::NodoArbol(std::string cedula) : cedula(cedula), izquierdo(nullptr), derecho(nullptr) {}

NodoArbol::~NodoArbol() {
    delete izquierdo;
    delete derecho;
}

// Implementación de la clase ArbolBinario
ArbolBinario::ArbolBinario() : raiz(nullptr) {}

ArbolBinario::~ArbolBinario() {
    delete raiz;
}

void ArbolBinario::insertar(std::string cedula) {
    raiz = insertarRecursivo(raiz, cedula);
}

NodoArbol* ArbolBinario::insertarRecursivo(NodoArbol* nodo, std::string cedula) {
    if (nodo == nullptr) {
        return new NodoArbol(cedula);
    }

    if (cedula < nodo->cedula) {
        nodo->izquierdo = insertarRecursivo(nodo->izquierdo, cedula);
    } else if (cedula > nodo->cedula) {
        nodo->derecho = insertarRecursivo(nodo->derecho, cedula);
    }

    return nodo;
}

void ArbolBinario::imprimirEnOrden() {
    inordenRecursivo(raiz);
}

void ArbolBinario::inordenRecursivo(NodoArbol* nodo) {
    if (nodo != nullptr) {
        inordenRecursivo(nodo->izquierdo);
        std::cout << nodo->cedula << std::endl;
        inordenRecursivo(nodo->derecho);
    }
}

void ArbolBinario::buscarCedula(const std::string& cedulaBuscada, const std::string& nombreArchivo) {
        if (buscarCedulaRecursivo(raiz, cedulaBuscada)) {
            if (buscarCedulaRecursivo(raiz, cedulaBuscada)) {
            std::cout << "\nCuenta encontrada: " << cedulaBuscada << std::endl;
        } else {
            std::cout << "\nLa cuenta " << cedulaBuscada << " no se encontro." << std::endl;
        }
        // Aquí deberías implementar la lógica para imprimir el recorrido inorden con flechas
        std::cout << std::endl;

        // Crear un objeto Cuenta para acceder a la función mostrarDatosUsuarios
        Cuenta nuevaCuenta;
        // Obtener los datos del usuario
        DatosUsuario datosUsuario = nuevaCuenta.mostrarDatosUsuarios("Usuarios.txt", cedulaBuscada);

        // Abrir el archivo para escribir
        Fecha fecha;
        // Obtener la fecha y hora actual utilizando la nueva función
        std::string fechaHoraGeneracion = fecha.obtenerFechaHoraActual();
            // Imprimir los datos del usuario
            std::cout << "Fecha de Busqueda: " << fechaHoraGeneracion  << "\n";
            std::cout << "Cedula/CI: " << cedulaBuscada << "\n";
            std::cout << "Cliente: " << datosUsuario.nombreCompleto << "\n";
            std::cout << "ID de Cliente: " << datosUsuario.id << "\n";
            std::cout << "No.Cuenta Cliente: " << datosUsuario.Ncuenta << "\n";
            std::cout << std::endl;
            std::cout << "Recorrido inorden con flechas: ";
            //inordenRecursivoConFlechas(raiz);
            std::cout << std::endl;
        } else {
            std::cout << "La cuenta " << cedulaBuscada << " no se encontro." << std::endl;
        }
}


bool ArbolBinario::buscarCedulaRecursivo(NodoArbol* nodo, const std::string& cedulaBuscada) {
    if (nodo == nullptr) {
        return false;
    }

    if (nodo->cedula == cedulaBuscada) {
        return true;
    }

    if (cedulaBuscada < nodo->cedula) {
        return buscarCedulaRecursivo(nodo->izquierdo, cedulaBuscada);
    } else {
        return buscarCedulaRecursivo(nodo->derecho, cedulaBuscada);
    }
}

void ArbolBinario::leerCedulas(const std::string& archivo) {
    std::ifstream file(archivo);
    std::string cedula;

    if (file.is_open()) {
        while (file >> cedula) {
            insertar(cedula);
        }
        file.close();
    } else {
        std::cerr << "\nNo se pudo abrir el archivo: " << archivo << std::endl;
    }
}

void ArbolBinario::inordenRecursivoConFlechas(NodoArbol* nodo) {
    if (nodo != nullptr) {
        inordenRecursivoConFlechas(nodo->izquierdo);
        std::cout << nodo->cedula << " -> ";
        inordenRecursivoConFlechas(nodo->derecho);
    }
}


