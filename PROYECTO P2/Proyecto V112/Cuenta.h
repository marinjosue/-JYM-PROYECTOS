#ifndef CUENTA_H_INCLUDED
#define CUENTA_H_INCLUDED

#include"Persona.h"
#include <string>
struct DatosUsuario {
    std::string cedula;
    std::string nombreCompleto;
    std::string id;
    std::string Ncuenta;
    std::string Prestamo;
};
class Cuenta{
public:
     Cuenta();
     static Cuenta crear_cuenta();
     std::string generar_cuenta_automatica();
     std::string getCuenta(void)const;
     void setCuenta(std::string );
     void guardarTabla(const std::string& archivo, const std::string& cedula, const std::string& nombreCompleto, const std::string& id, const Cuenta& cuenta);
     Cuenta(std::string cuenta);
     void mostrarDatosUsuarios(const std::string &archivo);
      bool verificarCedula(const std::string& nombreArchivo,const std::string& cedula);
     DatosUsuario mostrarDatosUsuarios(const std::string& archivo, const std::string& cedulaIngresada);
     static int contadorId;
     bool verificarCedulaA(const std::string& nombreArchivo,const std::string& cedula);
      std::string getCedula() const {
        return cedulaAsociada;
    }
    bool verificar_cuenta_existente(const std::string& cuenta, const std::string& archivo);
    std::string generar_cuenta_unico();
private:
 std::string cuenta;
 std::string cedulaAsociada;
};

#endif // CUENTA_H_INCLUDED
