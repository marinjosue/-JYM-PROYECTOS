#ifndef MOVIMIENTOS_H
#define MOVIMIENTOS_H
#include "ListaDoble.h"
#include "Fecha.h"
#include <string>
#include <vector>

class Movimientos {
private:
        std::string cedula;
        std::string tipoMovimiento;
        ListaDoble<double>* depositos;
        ListaDoble<double>* retiros;
        ListaDoble<Fecha>* fecha_de_pago;
        ListaDoble<double>* monto;
        bool eliminarArchivo(const std::string& rutaArchivo);
        bool eliminarDirectorio(const std::string& rutaDirectorio);
        bool eliminarUsuarioDeArchivo(const std::string& cedulaAEliminar);
        bool tieneDeudaPendiente(const std::string& cedula);

public:
    Movimientos();  // Constructor por defecto
    Movimientos(const std::string& cedula, const std::string& tipoMovimiento, double monto);
    // Getters y setters
    ListaDoble<double>* get_depositos();
    ListaDoble<double>* get_retiros();
    ListaDoble<Fecha>* get_fecha_de_pago();
    ListaDoble<double>* get_monto();
    std::string getCedula() const;
    void setCedula(const std::string& cedula);
    std::string getTipoMovimiento() const;
    void setTipoMovimiento(const std::string& tipoMovimiento);
    void set_depositos(ListaDoble<double>* nuevo_Deposito);
    void set_retiros(ListaDoble<double>* nuevo_Retiro);
    void set_monto(ListaDoble<double>* nuevo_Monto);
    void set_fecha_de_pago(ListaDoble<Fecha>* nuevo_fechas_pago);
    double verificarDeuda(const std::string& cedula);
    void guardarMontoDeuda(const std::string& cedula, double montoDeuda);


    // Funciones específicas para la clase Movimientos
    void realizarMovimiento(const std::string& cedulaIngresada, const std::string& tipoMovimiento);
    void mostrarMovimientos();
    bool directorioExiste(const std::string& nombreDirectorio);
    bool crearDirectorio(const std::string& nombreDirectorio);
    void mostrarMovimientosPorCedula();
    void registrarMovimiento(const std::string& );
    void mostrarTabla(const std::string& cedulaIngresada);
    double obtenerSaldoActual(const std::string& cedula, const std::string& carpeta);
    void guardarSaldoActual(const std::string& cedula, const std::string& carpeta, double saldo);
    bool validarNuevoCredito(const std::string& cedula);
    //void guardarMontoDeuda(const std::string& cedula, double montoDeuda);
    void pagoAutomatico(const std::string& cedula, bool pagoTotal);
    void eliminarUsuario(const std::string& cedula);
    void actualizarMovimientos(const std::string& cedula, const std::vector<std::string>& fechas,
                                        const std::vector<double>& cuotasFijas, const std::vector<double>& pagosCapitales,
                                        const std::vector<double>& intereses, const std::vector<double>& saldosCapitales);
  };

#endif
