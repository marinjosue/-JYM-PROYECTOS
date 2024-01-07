/***********************************************************************
 * Module:  Persona.cpp
 * Author:  Usuario
 * Modified: domingo, 7 de enero de 2024 0:07:18
 * Purpose: Implementation of the class Persona
 ***********************************************************************/

#include "Persona.h"

////////////////////////////////////////////////////////////////////////
// Name:       Persona::Persona()
// Purpose:    Implementation of Persona::Persona()
// Return:     
////////////////////////////////////////////////////////////////////////

Persona::Persona()
{
}

////////////////////////////////////////////////////////////////////////
// Name:       Persona::~Persona()
// Purpose:    Implementation of Persona::~Persona()
// Return:     
////////////////////////////////////////////////////////////////////////

Persona::~Persona()
{
   // TODO : implement
}

////////////////////////////////////////////////////////////////////////
// Name:       Persona::getNombre()
// Purpose:    Implementation of Persona::getNombre()
// Return:     std::string
////////////////////////////////////////////////////////////////////////

std::string Persona::getNombre(void)
{
   return Nombre;
}

////////////////////////////////////////////////////////////////////////
// Name:       Persona::setNombre(std::string newNombre)
// Purpose:    Implementation of Persona::setNombre()
// Parameters:
// - newNombre
// Return:     void
////////////////////////////////////////////////////////////////////////

void Persona::setNombre(std::string newNombre)
{
   Nombre = newNombre;
}

////////////////////////////////////////////////////////////////////////
// Name:       Persona::getApellido()
// Purpose:    Implementation of Persona::getApellido()
// Return:     std::string
////////////////////////////////////////////////////////////////////////

std::string Persona::getApellido(void)
{
   return Apellido;
}

////////////////////////////////////////////////////////////////////////
// Name:       Persona::setApellido(std::string newApellido)
// Purpose:    Implementation of Persona::setApellido()
// Parameters:
// - newApellido
// Return:     void
////////////////////////////////////////////////////////////////////////

void Persona::setApellido(std::string newApellido)
{
   Apellido = newApellido;
}

////////////////////////////////////////////////////////////////////////
// Name:       Persona::getCedula()
// Purpose:    Implementation of Persona::getCedula()
// Return:     std::string
////////////////////////////////////////////////////////////////////////

std::string Persona::getCedula(void)
{
   return Cedula;
}

////////////////////////////////////////////////////////////////////////
// Name:       Persona::setCedula(std::string newCedula)
// Purpose:    Implementation of Persona::setCedula()
// Parameters:
// - newCedula
// Return:     void
////////////////////////////////////////////////////////////////////////

void Persona::setCedula(std::string newCedula)
{
   Cedula = newCedula;
}

////////////////////////////////////////////////////////////////////////
// Name:       Persona::getId()
// Purpose:    Implementation of Persona::getId()
// Return:     std::string
////////////////////////////////////////////////////////////////////////

std::string Persona::getId(void)
{
   return Id;
}

////////////////////////////////////////////////////////////////////////
// Name:       Persona::setId(std::string newId)
// Purpose:    Implementation of Persona::setId()
// Parameters:
// - newId
// Return:     void
////////////////////////////////////////////////////////////////////////

void Persona::setId(std::string newId)
{
   Id = newId;
}

////////////////////////////////////////////////////////////////////////
// Name:       Persona::Persona(const Persona& oldPersona)
// Purpose:    Implementation of Persona::Persona()
// Parameters:
// - oldPersona
// Return:     
////////////////////////////////////////////////////////////////////////

Persona::Persona(const Persona& oldPersona)
{
   Nombre = oldPersona.Nombre;
   Apellido = oldPersona.Apellido;
   Cedula = oldPersona.Cedula;
   Id = oldPersona.Id;
}