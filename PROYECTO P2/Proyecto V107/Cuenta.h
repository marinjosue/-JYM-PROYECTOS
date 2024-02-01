#ifndef CUENTA_H_INCLUDED
#define CUENTA_H_INCLUDED

#include"Persona.h"
class Cuenta{
public:
     Cuenta();
     static Cuenta crear_cuenta();
     std::string generar_cuenta_automatica();
     std::string getCuenta(void)const;
     void setCuenta(std::string );
     void guardarTabla(const std::string& archivo, const std::string& cedula, const std::string& nombreCompleto, const std::string& id, const Cuenta& cuenta);
     Cuenta(std::string cuenta);
     void mostrarRegistroCuenta();
     static int contadorId;
     bool  verificarCedula(const std::string& cedula);
      std::string getCedula() const {
        return cedulaAsociada;
    }
private:
 std::string cuenta;
 std::string cedulaAsociada;
};

#endif // CUENTA_H_INCLUDED
