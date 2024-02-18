#include <iostream>
#include <map>
#include <fstream>
#include <string>
#include <sstream>

using namespace std;

// Definición del diccionario
map<string, string> diccionario;

// Función para cargar la base de datos desde un archivo
void cargarBaseDeDatos(const string& nombreArchivo) {
    ifstream archivo(nombreArchivo);

    if (!archivo.is_open()) {
        cerr << "Error: No se pudo abrir el archivo." << endl;
        return;
    }

    string linea;
    while (getline(archivo, linea)) {
        // Utilizamos un stringstream para dividir la línea en palabras
        stringstream ss(linea);
        string palabraIngles, palabraEspanol;
        // Leemos la palabra en inglés
        getline(ss, palabraIngles, ':'); // Suponiendo que las palabras están separadas por ':'
        // Leemos la palabra en español
        getline(ss, palabraEspanol);
        // Agregamos la palabra al diccionario
        diccionario[palabraIngles] = palabraEspanol;
    }

    archivo.close();
}

// Función para traducir una palabra
string traducirPalabra(string palabra) {
    // Buscar la palabra en el diccionario
    auto it = diccionario.find(palabra);
    if (it != diccionario.end()) {
        // Si se encuentra la palabra, devolver su traducción
        return it->second;
    } else {
        // Si la palabra no se encuentra en el diccionario, devolver un mensaje indicando que no se encontró la traducción
        return "Traduccion no encontrada";
    }
}

int main() {
    // Nombre del archivo que contiene el diccionario
    string nombreArchivo = "diccionario.txt";

    // Cargar la base de datos al inicio del programa
    cargarBaseDeDatos(nombreArchivo);

    // Solicitar al usuario que ingrese una palabra en inglés
    string palabraIngles;
    cout << "Ingrese una palabra en ingles: ";
    cin >> palabraIngles;

    // Traducir la palabra ingresada por el usuario
    string palabraEspanol = traducirPalabra(palabraIngles);

    // Mostrar la traducción por consola
    cout << "La traduccion al espaniol es: " << palabraEspanol << endl;

    main();

    return 0;
}
