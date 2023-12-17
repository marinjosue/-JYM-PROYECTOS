#ifndef NODO_H_INCLUDED
#define NODO_H_INCLUDED

#include <string>

using namespace std;

class Nodo {
public:
    string fecha;
    int numeroCuota;
    double cuotaMensual;
    double capital;
    double interes;
    double saldoRestante;
    Nodo* siguiente;
    Nodo* anterior;


    Nodo(const string& fecha, int numeroCuota, double cuotaMensual, double capital, double interes, double saldoRestante);
};

#endif // NODO_H_INCLUDED
