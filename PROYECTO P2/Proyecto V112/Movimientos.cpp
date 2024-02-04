#include "Movimientos.h"
#include "validaciones.h"
#include "Persona.h"
#include "Cuenta.h"
#include "Fecha.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <sys/stat.h> 
#include <cerrno>    
#include <iomanip>
#include "ListaDoble.cpp"

using namespace std;

Movimientos::Movimientos() {
    depositos = new ListaDoble<double>();
    retiros = new ListaDoble<double>();
    monto = new ListaDoble<double>();
    fecha_de_pago = new ListaDoble<Fecha>();
}

std::string Movimientos::getCedula() const {
    return cedula;
}

void Movimientos::setCedula(const std::string& cedula) {
    this->cedula = cedula;
}

std::string Movimientos::getTipoMovimiento() const {
    return tipoMovimiento;
}

void Movimientos::setTipoMovimiento(const std::string& tipoMovimiento) {
    this->tipoMovimiento = tipoMovimiento;
}

ListaDoble<double>* Movimientos::get_depositos(){
return depositos;

}
ListaDoble<double>* Movimientos:: get_retiros(){
return retiros;

}
ListaDoble<Fecha>* Movimientos::get_fecha_de_pago(){
return fecha_de_pago;

}

ListaDoble<double>* Movimientos:: get_monto(){
return monto;

}
void  Movimientos::set_depositos(ListaDoble<double>* nuevo_Deposito){
depositos=nuevo_Deposito;

}
void  Movimientos::set_retiros(ListaDoble<double>* nuevo_Retiro){
retiros=nuevo_Retiro;
}
void  Movimientos::set_monto(ListaDoble<double>* nuevo_Monto){
monto=nuevo_Monto;
}
void  Movimientos::set_fecha_de_pago(ListaDoble<Fecha>* nuevo_fechas_pago){
fecha_de_pago=nuevo_fechas_pago;
}

void Movimientos::realizarMovimiento(const std::string& cedulaIngresada, const std::string& tipoMovimiento) {
    validaciones valida;
    Cuenta nuevaCuenta;

    // Crear la carpeta "Usuarios" si no existe
    std::string carpetaUsuarios = "Movimientos";
    if (!directorioExiste(carpetaUsuarios)) {
        if (crearDirectorio(carpetaUsuarios)) {
            std::cout << "Carpeta de usuarios creada correctamente." << std::endl;
        } else {
            std::cerr << "Error al crear la carpeta de usuarios." << std::endl;
            return;
        }
    }

    // Crear la carpeta "DATOS" si no existe
    std::string carpetaDatos = "DATOS";
    if (!directorioExiste(carpetaDatos)) {
        if (crearDirectorio(carpetaDatos)) {
            std::cout << "Carpeta de datos creada correctamente." << std::endl;
        } else {
            std::cerr << "Error al crear la carpeta de datos." << std::endl;
            return;
        }
    }

    // Obtener datos del usuario
    DatosUsuario datosUsuario = nuevaCuenta.mostrarDatosUsuarios("Usuarios.txt", cedulaIngresada);

    if (datosUsuario.cedula.empty()) {
        std::cout << "\nLa cedula ingresada no existe en el archivo. Vuelva a intentarlo." << std::endl;
        return;
    }

    double deposito = 0.0, retiro = 0.0;  // Inicializar a 0.0
    Fecha fecha;
  

    double saldoActual = obtenerSaldoActual(cedulaIngresada, carpetaDatos);
     if (saldoActual < 0.0) {
    std::cout << " Su saldo inicial es $0.0." << std::endl;
    saldoActual = 0.0;  // Establecer el saldo inicial en 0.0
        }
    if (saldoActual < 0.0) {
        std::cerr << "Error al obtener el saldo actual." << std::endl;
        return;
    }

    if (tipoMovimiento == "Deposito") {
        std::cout << "\nIngrese el monto del deposito: ";
        std::cin >> deposito;

        // Actualizar el saldo con el nuevo depósito
        saldoActual += deposito;

        // Insertar el monto en la cola de depósitos
        depositos->insertar_cola(static_cast<int>(deposito));
        monto->insertar_cola(saldoActual);  // Actualizar monto con el nuevo saldo
    } else if (tipoMovimiento == "Retiro") {
        std::cout << "\nIngrese el monto del retiro: ";
        std::cin >> retiro;

        // Validar que el monto de retiro no sea mayor que el saldo actual
        if (retiro > saldoActual) {
            std::cerr << "Error: El monto de retiro supera el saldo actual." << std::endl;
            return;
        }

        // Actualizar el saldo con el nuevo retiro
        saldoActual -= retiro;

        // Insertar el monto en la cola de retiros
        retiros->insertar_cola(static_cast<int>(retiro));
        monto->insertar_cola(saldoActual);  // Actualizar monto con el nuevo saldo
    } else {
        std::cerr << "Error: Tipo de movimiento no valido. Ingrese 'Deposito' o 'Retiro'." << std::endl;
        return;  // Salir del método si el tipo de movimiento no es válido
    }

    // Actualizar el saldo en el archivo correspondiente
    guardarSaldoActual(cedulaIngresada, carpetaDatos, saldoActual);

    // Ahora, abrir el archivo para escritura
    std::ofstream archivo;
    std::string rutaArchivo = carpetaUsuarios + "/" + cedulaIngresada + ".txt";

    archivo.open(rutaArchivo, std::ios_base::app);

    if (!archivo.is_open()) {
        std::cerr << "Error al abrir el archivo para escritura." << std::endl;
        return;
    }
    // Formato de salida en el archivo
    archivo << std::left << std::setw(20) << fecha.obtenerFechaHoraActual() << '|'
            << std::left << std::setw(10) << deposito << '|'
            << std::left << std::setw(10) << retiro << '|'
            << std::left << std::setw(10) << saldoActual << '|' << std::endl;
    // Cerrar el archivo
    archivo.close();
    std::cout << "Movimiento registrado con exito." << std::endl;
}


void Movimientos::guardarSaldoActual(const std::string& cedula, const std::string& carpeta, double saldo) {
   std::ofstream archivo;
std::string rutaArchivo = carpeta + "/" + cedula + ".txt";

archivo.open(rutaArchivo, std::ios_base::trunc);  // Cambiado a std::ios_base::trunc

if (!archivo.is_open()) {
    std::cerr << "Error al abrir el archivo para escritura." << std::endl;
    return;
}

// Formato de salida en el archivo
archivo << saldo << std::endl;

// Cerrar el archivo
archivo.close();

}

double Movimientos::obtenerSaldoActual(const std::string& cedula, const std::string& carpeta) {
    std::ifstream archivo;
    std::string rutaArchivo = carpeta + "/" + cedula + ".txt";

    archivo.open(rutaArchivo);

    if (!archivo.is_open()) {
        std::cerr << "\n Es la primera vez que ingresa." << std::endl;
        return -1.0;  // Retorna un valor negativo para indicar error
    }

    // Leer el valor de SALDO desde la línea
    double saldoActual = 0.0;
    std::string linea;  // Agregar esta línea para declarar 'linea'
    if (std::getline(archivo, linea)) {
        std::istringstream iss(linea);
        if (iss >> saldoActual) {
            // Se leyó correctamente
        } else {
            std::cerr << "Error al convertir el saldo a double." << std::endl;
            saldoActual = -1.0;
        }
    } else {
        std::cerr << "Error al leer la línea del saldo actual." << std::endl;
        saldoActual = -1.0;
    }

    archivo.close();
    return saldoActual;
}

void Movimientos::pagoPrestamoAutomatico(){

}

void Movimientos::mostrarMovimientosPorCedula() {
    // Solicitar el número de cédula al usuario
    std::string cedulaIngresada;
    std::cout << "Ingrese su numero de cedula: ";
    std::cin >> cedulaIngresada;
    // Construir el nombre del archivo correspondiente
    std::string nombreArchivo = "Movimientos/" + cedulaIngresada + ".txt";
    // Intentar abrir el archivo
    std::ifstream inFile(nombreArchivo);
    if (inFile.is_open()) {
        // Leer y mostrar el contenido del archivo línea por línea
        std::string linea;
        std::cout << "\nContenido del archivo " << nombreArchivo << ":\n";
        while (std::getline(inFile, linea)) {
            std::cout << linea << std::endl;
        }
        inFile.close();
    } else {
        std::cerr << "\nNo se pudo abrir el archivo " << nombreArchivo << ". Puede que no exista o haya un error." << std::endl;
    }
}

bool Movimientos::directorioExiste(const std::string& nombreDirectorio) {
    struct stat info;
    if (stat(nombreDirectorio.c_str(), &info) != 0) {
        return false;
    }
    return (info.st_mode & S_IFDIR) != 0;
}

bool Movimientos::crearDirectorio(const std::string& nombreDirectorio) {
    int resultado = mkdir(nombreDirectorio.c_str());
    if (resultado == -1) {
        std::cerr << "Error al crear el directorio: " << strerror(errno) << std::endl;
        return false;
    }
    return true;
}
void Movimientos::mostrarMovimientos() {
    // Implementa la lógica para mostrar los movimientos realizados
}

void Movimientos::registrarMovimiento(const std::string& cedulaIngresada) {
    validaciones valida;
    Cuenta nuevacuenta;

    // Crear la carpeta "Usuarios" si no existe
    std::string carpetaUsuarios = "Movimientos";
    if (!directorioExiste(carpetaUsuarios)) {
        if (crearDirectorio(carpetaUsuarios)) {
            std::cout << "Carpeta de usuarios creada correctamente." << std::endl;
        } else {
            std::cerr << "Error al crear la carpeta de usuarios." << std::endl;
            return;
        }
    }
    // Obtener datos del usuario
    DatosUsuario datosUsuario = nuevacuenta.mostrarDatosUsuarios("Usuarios.txt", cedulaIngresada);

    if (datosUsuario.cedula.empty()) {
        std::cout << "\nLa cedula ingresada no existe en el archivo. Vuelva a intentarlo." << std::endl;
        return;
    }

    // Obtener la fecha actual
    Fecha fechaActual;

    std::string nombreArchivo = carpetaUsuarios + "/" + cedulaIngresada + ".txt";

    // Abrir el archivo de usuario en modo de añadir (append)
    std::ofstream outFile(nombreArchivo, std::ios::app);
    double prestamo=0.0;
    if (outFile.is_open()) {
        // Escribir los datos en el archivo
        outFile << "Fecha de Creacion: " << fechaActual.to_string() << "\n";
        outFile << "Cedula/CI: " << datosUsuario.cedula << "\n";
        outFile << "Cliente: " << datosUsuario.nombreCompleto << "\n";
        outFile << "ID de Cliente: " << datosUsuario.id << "\n";
        outFile << "No.Cuenta Cliente: " << datosUsuario.Ncuenta << "\n";
        outFile << "Prestamo: " << prestamo  << "\n";

        // Añadir encabezado
        int ancho_fecha = 20, ancho_deposito = 10, ancho_retiro = 10, ancho_saldo = 10;
        outFile << '|' << std::setw(ancho_fecha) << std::left << "FECHA Y HORA" << '|'
                << std::setw(ancho_deposito) << std::left << "DEPOSITOS" << '|'
                << std::setw(ancho_retiro) << std::left << "RETIROS" << '|'
                << std::setw(ancho_saldo) << std::left << " SALDO" << '|';

        // Agregar una línea separadora
        outFile << "\n========================================================\n";

        std::cout << "\nDatos guardados en " << nombreArchivo << std::endl;

        outFile.close();
    } else {
        std::cerr << "\nNo se pudo abrir el archivo " << nombreArchivo << std::endl;
    }
}
