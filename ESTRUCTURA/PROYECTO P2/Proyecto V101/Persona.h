/***********************************************************************
 * Module:  Persona.h
 * Author:  Usuario
 * Modified: domingo, 7 de enero de 2024 0:07:18
 * Purpose: Declaration of the class Persona
 ***********************************************************************/

#if !defined(__Persona_Persona_h)
#define __Persona_Persona_h

#include <string>


template <typename T>
class ListaDoble;

class Persona
{
public:
   Persona();
    // Constructores modificados
    Persona(std::string Nombre, std::string Apellido, std::string Cedula);
    Persona(std::string Nombre, std::string Apellido, std::string Cedula, std::string Id);
   // Método estático para obtener el siguiente ID
   static std::string generarSiguienteId();
   ~Persona();
   std::string getNombre(void);
   void setNombre(std::string newNombre);
   std::string getApellido(void);
   void setApellido(std::string newApellido);
   std::string getCedula(void);
   void setCedula(std::string newCedula);
   std::string getId(void);
   void setId(std::string newId);
   static Persona ingresarPersona(ListaDoble<Persona*>& listaPersonas);
   static int contadorId;
   std::string id;
   void guardarEnArchivo(const std::string& nombreArchivo);
   void mostrarRegistroPersona();

protected:
private:
   std::string Nombre;
   std::string Apellido;
   std::string Cedula;
   std::string Id;

};

#endif
