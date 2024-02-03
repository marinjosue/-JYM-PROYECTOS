#include "Movimientos.h"
#include "validaciones.h"
#include "Persona.h"
#include "Cuenta.h"
#include "Fecha.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <sys/stat.h> // Para crear directorios
#include <cerrno>     // Para manejar errores de sistema
#include <iomanip>
#include "ListaDoble.cpp"

using namespace std;

Movimientos::Movimientos() {
    depositos = new ListaDoble<int>();
    retiros = new ListaDoble<int>();
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

ListaDoble<int>* Movimientos::get_depositos(){
return depositos;

}
ListaDoble<int>* Movimientos:: get_retiros(){
return retiros;

}
ListaDoble<Fecha>* Movimientos::get_fecha_de_pago(){
return fecha_de_pago;

}

ListaDoble<double>* Movimientos:: get_monto(){
return monto;

}
void  Movimientos::set_depositos(ListaDoble<int>* nuevo_Deposito){
depositos=nuevo_Deposito;

}
void  Movimientos::set_retiros(ListaDoble<int>* nuevo_Retiro){
retiros=nuevo_Retiro;
}
void  Movimientos::set_monto(ListaDoble<double>* nuevo_Monto){
monto=nuevo_Monto;
}
void  Movimientos::set_fecha_de_pago(ListaDoble<Fecha>* nuevo_fechas_pago){
fecha_de_pago=nuevo_fechas_pago;
}

double Movimientos::obtenerSaldoActual(const std::string& rutaArchivo) {
    double saldoActual = 0.0;

    std::ifstream archivoEntrada;
    archivoEntrada.open(rutaArchivo);

    if (archivoEntrada.is_open()) {
        std::string linea;

        // Ignorar las líneas hasta llegar a la línea de saldo
        while (getline(archivoEntrada, linea) && linea != "=======================================================");

        // Leer la línea de saldo y obtener el valor de saldo
        if (getline(archivoEntrada, linea)) {
            std::istringstream ss(linea);

            std::string fechaHora;
            int deposito, retiro, saldo;

            // Leer las partes de la línea
            ss >> fechaHora >> deposito >> retiro >> saldo;

            // Actualizar el saldo actual con el valor leído
            saldoActual = saldo;
        } else {
            std::cerr << "Error: No se encontró la línea de saldo en el archivo." << std::endl;
        }

        archivoEntrada.close();
    } else {
        std::cerr << "Error al abrir el archivo: " << rutaArchivo << std::endl;
    }

    return saldoActual;
}




void Movimientos::realizarMovimiento(const std::string& cedulaIngresada, const std::string& tipoMovimiento) {
    validaciones valida;
    Cuenta nuevaCuenta;

    // Crear la carpeta "Usuarios" si no existe
    std::string carpetaUsuarios = "Usuarios";
    if (!directorioExiste(carpetaUsuarios)) {
        if (crearDirectorio(carpetaUsuarios)) {
            std::cout << "Carpeta de usuarios creada correctamente." << std::endl;
        } else {
            std::cerr << "Error al crear la carpeta de usuarios." << std::endl;
            return;
        }
    }

    // Obtener datos del usuario
    DatosUsuario datosUsuario = nuevaCuenta.mostrarDatosUsuarios("Usuarios.txt", cedulaIngresada);

    if (datosUsuario.cedula.empty()) {
        std::cout << "\nLa cedula ingresada no existe en el archivo. Vuelva a intentarlo." << std::endl;
        return;
    }

    int deposito,retiro=0;
    Fecha fecha;


    // Puedes incluir la lógica para ingresar la fecha según tus necesidades.
    if (tipoMovimiento == "Deposito") {
        std::cout << "\nIngrese el monto del deposito: ";
        std::cin >> deposito;
        // Inserta el monto en la cola de depósitos
        depositos->insertar_cola(deposito);
    } else if (tipoMovimiento == "Retiro") {
        std::cout << "\nIngrese el monto del retiro: ";
        std::cin >> retiro;
        // Inserta el monto en la cola de retiros
        retiros->insertar_cola(retiro);
    } else {
        std::cout << "Tipo de movimiento no valido. Ingrese 'Deposito' o 'Retiro'." << std::endl;
        return;  // Sal del método si el tipo de movimiento no es válido
    }

    // Ahora, abre el archivo para escritura
    std::ofstream archivo;
    std::string rutaArchivo = carpetaUsuarios + "/" + cedulaIngresada + ".txt";

    archivo.open(rutaArchivo, std::ios_base::app); // std::ios_base::app para abrir el archivo en modo de añadir

    if (!archivo.is_open()) {
        std::cerr << "Error al abrir el archivo para escritura." << std::endl;
        return;
    }

    // Formato de salida en el archivo
    archivo << std::left << std::setw(20) << fecha.obtenerFechaHoraActual() << '|'
            << std::left << std::setw(10) << deposito << '|'
            << std::left << std::setw(10) << retiro << '|'
            << std::left << std::setw(10) << 0 << '|' << std::endl;


    // Cierra el archivo
    archivo.close();

    std::cout << "Movimiento registrado con exito." << std::endl;
}

void Movimientos::guardarTabla(std::ofstream& outFile, const std::string& cedulaIngresada, int monto) {
    Fecha fecha;

    // Obtener la ruta del archivo
    std::string nombreArchivo = "Usuarios/" + cedulaIngresada + ".txt";
    int ancho_cedula = 35, ancho_nombre = 10, ancho_id = 10, ancho_cuenta = 10;
    if (outFile.is_open()) {
        // Escribir los datos en formato de tabla
        outFile << std::setw(15) << fecha.obtenerAnioActual() << std::setw(15) << "$" << monto << std::setw(15) << "$0" << std::setw(15) << "$" << monto << "\n";
        outFile << "\n";

        std::cout << "\nDepósito realizado con éxito. Datos guardados en " << nombreArchivo << std::endl;
    } else {
        std::cerr << "\nNo se pudo abrir el archivo " << nombreArchivo << std::endl;
    }
}

/*
void Movimientos::mostrarTabla(const std::string& cedulaIngresada){
    Cuenta nuevacuenta;
   std::string carpetaUsuarios = "Usuarios";
    int n_mostrados = 0;
    int n_mostrar=10;
   // Obtener la fecha actual
    Fecha fechaActual;
    std::string nombreArchivo = carpetaUsuarios + "/" + cedulaIngresada + ".txt";
    // Abrir el archivo de usuario en modo de añadir (append)
    // solo quiero mostrarlos
    DatosUsuario datosUsuario = nuevacuenta.mostrarDatosUsuarios("Usuarios.txt", cedula);
    std::string nombreCompleto = datosUsuario.nombreCompleto;
                std::string id = datosUsuario.id;
                std::string Ncuenta = datosUsuario.Ncuenta;
                archivoUsuarios.close();
                // Imprimir información del cliente
     std::ofstream archivo(nombreArchivo);
    archivo << "Datos del cliente:\n";
    archivo << "Cedula: " << cedula << "\n";
    archivo << "Nombre: " << nombreCompleto << "\n";
    archivo << "ID: " << id << "\n";
    archivo << "No.Cuenta: " << Ncuenta << "\n";
    Nodo<int>* _depositos = depositos->get_cabeza();
    Nodo<int>* _retiros = retiros->get_cabeza();
    Nodo<double>* _monto = monto->get_cabeza();
    Nodo<Fecha>* _fecha_de_pago = fecha_de_pago->get_cabeza();
    int ancho_fecha = 35, ancho_deposito = 10, ancho_retiro = 10, ancho_saldo = 10;
    std::cout << '|' << std::setw(ancho_fecha) << std::left << "FECHA Y HORA" << '|'
              << std::setw(ancho_deposito) << std::left << "DEPOSITOS" << '|'
              << std::setw(ancho_retiro) << std::left << "RETISOS" << '|'
              << std::setw(ancho_saldo) << std::left << "SALDO" << '|';
    std::cout << "\n========================================================" <<
    while(n_mostrados < n_mostrar){
        Fecha fecha_pagar;
        fecha_pagar = _fecha_de_pago->get_valor();
        std::cout<< '|'<<std::setw(ancho_fecha)<<ord->get_valor()<<'|'<<std::setw(ancho_deposito)<<valor_cuota->get_valor();
        std::cout<<'|'<<std::setw(ancho_retiro)<<capital_pag->get_valor()<<'|'<<std::setw(ancho_saldo)<<interes->get_valor();
        printf("\n");

        _depositos = _depositos->get_siguiente();
        _retiros = _retiros->get_siguiente();
        interes = interes->get_siguiente();
        _monto = _monto->get_siguiente();
        _fecha_de_pago = _fecha_de_pago->get_siguiente();
        n_mostrados++;
    }

    // Formato de salida en la consola
    std::cout << '|' << std::left << std::setw(20) << "FECHA Y HORA" << '|'
              << std::left << std::setw(10) << "DEPOSITOS" << '|'
              << std::left << std::setw(10) << "RETISOS" << '|'
              << std::left << std::setw(10) << "SALDO" << '|' << std::endl;

    std::cout << "========================================================" << std::endl;

    std::cout << '|' << std::left << std::setw(20) << fechaMovimiento.to_string() << '|'
              << std::left << std::setw(10) << montoMovimiento << '|'
              << std::left << std::setw(10) << 0 << '|'
              << std::left << std::setw(10) << 0 << '|' << std::endl;

    std::cout << "========================================================" << std::endl;



}*/


void Movimientos::pagoPrestamoAutomatico(){


}

void Movimientos::mostrarMovimientosPorCedula() {
    // Solicitar el número de cédula al usuario
    std::string cedulaIngresada;
    std::cout << "Ingrese su numero de cedula: ";
    std::cin >> cedulaIngresada;
    // Construir el nombre del archivo correspondiente
    std::string nombreArchivo = "Usuarios/" + cedulaIngresada + ".txt";
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
    std::string carpetaUsuarios = "Usuarios";
    if (!directorioExiste(carpetaUsuarios)) {
        if (crearDirectorio(carpetaUsuarios)) {
            std::cout << "Carpeta de usuarios creada correctamente." << std::endl;
        } else {
            std::cerr << "Error al crear la carpeta de usuarios." << std::endl;
            return;
        }
    }

    // Solicitar el monto al usuario
    double montoIngresado = valida.ingresar_reales("\nIngrese el monto a registrar ($): ");
    if (montoIngresado != 5.0) {
        std::cout << "\nSolo se permite registrar un monto de $5.\n" << std::endl;
        return;
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

    if (outFile.is_open()) {
        // Escribir los datos en el archivo
        outFile << "Fecha: " << fechaActual.to_string() << "\n";
        outFile << "Monto: $" << montoIngresado << "\n";
        outFile << "Cedula: " << datosUsuario.cedula << "\n";
        outFile << "Nombre: " << datosUsuario.nombreCompleto << "\n";
        outFile << "ID: " << datosUsuario.id << "\n";
        outFile << "No.Cuenta: " << datosUsuario.Ncuenta << "\n";

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
