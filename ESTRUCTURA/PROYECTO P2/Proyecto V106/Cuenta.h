#ifndef CUENTA_H_INCLUDED
#define CUENTA_H_INCLUDED

#include"Persona.h"
class Cuenta{
public:
     Cuenta();
     static Cuenta crear_cuenta();
     std::string generar_cuenta_automatica();
     std::string getCuenta(void);
     void setCuenta(std::string );
     void guardarTabla(const std::string& nombreArchivo);
     Cuenta(std::string cuenta);
     void mostrarRegistroCuenta();
      static int contadorId;
private:
 std::string cuenta;




};

#endif // CUENTA_H_INCLUDED
