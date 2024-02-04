#include <unordered_map>
#include <string>

class ArbolRadix {
private:
    class NodoRadix {
    public:
        bool esFinal;
        std::unordered_map<char, NodoRadix*> hijos;

        NodoRadix() : esFinal(false) {}
    };

    NodoRadix* raiz;

public:
    ArbolRadix() {
        raiz = new NodoRadix();
    }

    // Método para insertar una cédula en el árbol Radix (no se utilizará en este caso)
    void insertarCedula(const std::string& cedula) {
        // Implementación de inserción si fuera necesaria
    }

    // Método para buscar una cédula en el árbol Radix
    bool buscarCedula(const std::string& cedula) {
        NodoRadix* actual = raiz;
        for (char c : cedula) {
            if (actual->hijos.find(c) == actual->hijos.end()) {
                return false; // No se encontró la cédula
            }
            actual = actual->hijos[c];
        }
        return actual != nullptr && actual->esFinal;
    }
};
