#include "Nodo.h"
using namespace std;

Nodo::Nodo(const string& fecha, int numeroCuota, double cuotaMensual, double capital, double interes, double saldoRestante)
    : fecha(fecha), numeroCuota(numeroCuota), cuotaMensual(cuotaMensual), capital(capital), interes(interes), saldoRestante(saldoRestante), siguiente(nullptr), anterior(nullptr){}
