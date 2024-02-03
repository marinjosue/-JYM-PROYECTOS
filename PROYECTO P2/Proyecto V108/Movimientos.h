#ifndef MOVIMIENTOS_H
#define MOVIMIENTOS_H

#include <string>

class Movimientos {
private:
    std::string cedula;
    std::string tipoMovimiento;
    double monto;

public:
    Movimientos();  // Constructor por defecto
    Movimientos(const std::string& cedula, const std::string& tipoMovimiento, double monto);

    // Getters y setters
    std::string getCedula() const;
    void setCedula(const std::string& cedula);
    std::string getTipoMovimiento() const;
    void setTipoMovimiento(const std::string& tipoMovimiento);
    double getMonto() const;
    void setMonto(double monto);

    // Funciones específicas para la clase Movimientos
    void registrarMovimiento(const std::string& cedula);
    void mostrarMovimientos();
    bool directorioExiste(const std::string& nombreDirectorio);
    bool crearDirectorio(const std::string& nombreDirectorio);
    void realizarDeposito(const std::string& cedulaIngresada);

};

#endif
