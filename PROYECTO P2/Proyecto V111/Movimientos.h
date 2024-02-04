#ifndef MOVIMIENTOS_H
#define MOVIMIENTOS_H
#include "ListaDoble.h"
#include "Fecha.h"
#include <string>

class Movimientos {
private:
        std::string cedula;
        std::string tipoMovimiento;
        ListaDoble<int>* depositos;
        ListaDoble<int>* retiros;
        ListaDoble<Fecha>* fecha_de_pago;
        ListaDoble<double>* monto;

public:
    Movimientos();  // Constructor por defecto
    Movimientos(const std::string& cedula, const std::string& tipoMovimiento, double monto);
    // Getters y setters
    ListaDoble<int>* get_depositos();
    ListaDoble<int>* get_retiros();
    ListaDoble<Fecha>* get_fecha_de_pago();
    ListaDoble<double>* get_monto();

    std::string getCedula() const;
    void setCedula(const std::string& cedula);
    std::string getTipoMovimiento() const;
    void setTipoMovimiento(const std::string& tipoMovimiento);

    void set_depositos(ListaDoble<int>* nuevo_Deposito);
    void set_retiros(ListaDoble<int>* nuevo_Retiro);
    void set_monto(ListaDoble<double>* nuevo_Monto);
    void set_fecha_de_pago(ListaDoble<Fecha>* nuevo_fechas_pago);


    // Funciones específicas para la clase Movimientos
    void realizarMovimiento(const std::string& cedulaIngresada, const std::string& tipoMovimiento);
    void mostrarMovimientos();
    bool directorioExiste(const std::string& nombreDirectorio);
    bool crearDirectorio(const std::string& nombreDirectorio);
    void mostrarMovimientosPorCedula();
    void guardarTabla(std::ofstream& outFile, const std::string& cedulaIngresada, int monto);
    void pagoPrestamoAutomatico();
    void registrarMovimiento(const std::string& );
    void mostrarTabla(const std::string& cedulaIngresada);
    double obtenerSaldoActual(const std::string& rutaArchivo);

};

#endif
