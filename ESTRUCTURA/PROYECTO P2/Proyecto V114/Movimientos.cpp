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
#include "Amortizacion.h"

using namespace std;

Movimientos::Movimientos(){
    depositos = new ListaDoble<double>();
    retiros = new ListaDoble<double>();
    monto = new ListaDoble<double>();
    fecha_de_pago = new ListaDoble<Fecha>();
}
Movimientos::~Movimientos() {
    delete depositos;
    delete retiros;
    delete monto;
    delete fecha_de_pago;
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
            std::cout << "\nCarpeta de usuarios creada correctamente." << std::endl;
        } else {
            std::cerr << "\nError al crear la carpeta de usuarios." << std::endl;
            return;
        }
    }
    // Crear la carpeta "DATOS" si no existe
    std::string carpetaDatos = "DATOS";
    if (!directorioExiste(carpetaDatos)) {
        if (crearDirectorio(carpetaDatos)) {
            std::cout << "\nCarpeta de datos creada correctamente." << std::endl;
        } else {
            std::cerr << "\nError al crear la carpeta de datos." << std::endl;
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
    std::cout << " \nSu saldo inicial es $0.0." << std::endl;
    saldoActual = 0.0;  // Establecer el saldo inicial en 0.0
        }
    if (saldoActual < 0.0) {
        std::cerr << "\nError al obtener el saldo actual." << std::endl;
        return;
    }

    if (tipoMovimiento == "Deposito") {
        deposito = valida.ingresar_reales("\nIngrese el monto del deposito: ");

        // Actualizar el saldo con el nuevo depósito
        saldoActual += deposito;
        // Insertar el monto en la cola de depósitos
        depositos->insertar_cola(static_cast<int>(deposito));
        monto->insertar_cola(saldoActual);  // Actualizar monto con el nuevo saldo
        
    } else if (tipoMovimiento == "Retiro") {
        retiro = valida.ingresar_enteros("\nIngrese el monto del retiro: ");

        // Validar que el monto de retiro no sea mayor que el saldo actual
        if (retiro > saldoActual) {
            std::cerr << "\nError: El monto de retiro supera el saldo actual." << std::endl;
            return;
        }
        // Actualizar el saldo con el nuevo retiro
        saldoActual -= retiro;

        // Insertar el monto en la cola de retiros
        retiros->insertar_cola(static_cast<int>(retiro));
        monto->insertar_cola(saldoActual);  // Actualizar monto con el nuevo saldo
    } else {
        std::cerr << "\nError: Tipo de movimiento no valido. Ingrese 'Deposito' o 'Retiro'." << std::endl;
        return;  // Salir del método si el tipo de movimiento no es válido
    }

    // Actualizar el saldo en el archivo correspondiente
    guardarSaldoActual(cedulaIngresada, carpetaDatos, saldoActual);

    // Ahora, abrir el archivo para escritura
    std::ofstream archivo;
    std::string rutaArchivo = carpetaUsuarios + "/" + cedulaIngresada + ".txt";

    archivo.open(rutaArchivo, std::ios_base::app);

    if (!archivo.is_open()) {
        std::cerr << "\nError al abrir el archivo para escritura." << std::endl;
        return;
    }
    int ancho_fecha = 20, ancho_deposito = 10, ancho_retiro = 10, ancho_saldo = 10;
    // Formato de salida en el archivo
    archivo   << '|' <<std::left << std::setw(ancho_fecha) << fecha.obtenerFechaHoraActual() << '|'
              << std::left << std::setw(ancho_deposito) << deposito << '|'
              << std::left << std::setw(ancho_retiro) << retiro << '|'
              << std::left << std::setw(ancho_saldo) << saldoActual << '|' << std::endl;
    archivo.close();
    mostrarMovimientosPorCedula(cedulaIngresada);
    std::cout << "\nMovimiento registrado con exito." << std::endl;
}


void Movimientos::guardarSaldoActual(const std::string& cedula, const std::string& carpeta, double saldo) {
   std::ofstream archivo;
std::string rutaArchivo = carpeta + "/" + cedula + ".txt";

archivo.open(rutaArchivo, std::ios_base::trunc);  // Cambiado a std::ios_base::trunc

if (!archivo.is_open()) {
    std::cerr << "\nError al abrir el archivo para escritura." << std::endl;
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
            std::cerr << "\nError al convertir el saldo a double." << std::endl;
            saldoActual = -1.0;
        }
    } else {
        std::cerr << "\nError al leer la línea del saldo actual." << std::endl;
        saldoActual = -1.0;
    }

    archivo.close();
    return saldoActual;
}
void Movimientos::mostrarMovimientosPorCedula(const std::string& cedulaIngresada) {
      
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
        std::cerr << "\nError al crear el directorio: " << strerror(errno) << std::endl;
        return false;
    }
    return true;
}
void Movimientos::mostrarMovimientos() {
    // Implementa la lógica para mostrar los movimientos realizados
}

void Movimientos::registrarMovimiento(const std::string& cedulaIngresada, double montoDeuda) {
    validaciones valida;
    Cuenta nuevacuenta;

    // Crear la carpeta "Usuarios" si no existe
    std::string carpetaUsuarios = "Movimientos";
    if (!directorioExiste(carpetaUsuarios)) {
        if (crearDirectorio(carpetaUsuarios)) {
            std::cout << "\nCarpeta de usuarios creada correctamente." << std::endl;
        } else {
            std::cerr << "\nError al crear la carpeta de usuarios." << std::endl;
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

    if (outFile.is_open()) {
        // Escribir los datos en el archivo
        outFile << "Fecha de Creacion: " << fechaActual.to_string() << "\n";
        outFile << "Cedula/CI: " << datosUsuario.cedula << "\n";
        outFile << "Cliente: " << datosUsuario.nombreCompleto << "\n";
        outFile << "ID de Cliente: " << datosUsuario.id << "\n";
        outFile << "No.Cuenta Cliente: " << datosUsuario.Ncuenta << "\n";
        outFile << "Monto de Deuda: " << montoDeuda  << "\n";

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

void Movimientos::guardarMontoDeuda(const std::string& cedula, double montoDeuda) {
    std::ifstream archivoLectura;
    std::ofstream archivoEscritura;
    std::string rutaArchivo = "Movimientos/" + cedula + ".txt";

    archivoLectura.open(rutaArchivo);

    if (!archivoLectura.is_open()) {
        std::cerr << "\nError al abrir el archivo para lectura." << std::endl;
        return;
    }

    std::string contenidoArchivo;

    // Leer el contenido actual del archivo
    while (!archivoLectura.eof()) {
        std::string linea;
        std::getline(archivoLectura, linea);
        contenidoArchivo += linea + "\n";
    }

    archivoLectura.close();

    // Buscar la línea que contiene "Monto de Deuda:"
    size_t pos = contenidoArchivo.find("Monto de Deuda:");

    if (pos != std::string::npos) {
        // Encontrar la posición de fin de la línea actual
        size_t posFinLinea = contenidoArchivo.find("\n", pos);

        // Formatear el monto de deuda con dos decimales
        std::stringstream montoFormateado;
        montoFormateado << std::fixed << std::setprecision(2) << montoDeuda;

        // Reemplazar la línea actual con el nuevo monto de deuda formateado
        contenidoArchivo.replace(pos, posFinLinea - pos, "Monto de Deuda: " + montoFormateado.str());
    } else {
        // Si no se encuentra la línea, agregarla al final formateada
        std::stringstream montoFormateado;
        montoFormateado << std::fixed << std::setprecision(2) << montoDeuda;
        contenidoArchivo += "Monto de Deuda: " + montoFormateado.str();
    }

    // Abrir el archivo para escritura
    archivoEscritura.open(rutaArchivo);

    if (!archivoEscritura.is_open()) {
        std::cerr << "\nError al abrir el archivo para escritura." << std::endl;
        return;
    }

    // Escribir el contenido actualizado en el archivo
    archivoEscritura << contenidoArchivo;

    archivoEscritura.close();
    std::cout << "\nMonto de deuda guardado correctamente en " << rutaArchivo << std::endl;
}

void Movimientos::pagoAutomatico(const std::string& cedula, bool pagoTotal) {
    // Ruta del archivo de Movimientos
    std::string rutaArchivoMovimientos = "Movimientos/" + cedula + ".txt";

    // Abrir el archivo de Movimientos para lectura
    std::ifstream archivoMovimientosLectura(rutaArchivoMovimientos);

    if (!archivoMovimientosLectura.is_open()) {
        std::cerr << "\nError al abrir el archivo de Movimientos para lectura." << std::endl;
        return;
    }

    // Variable para almacenar el monto de deuda
    double montoDeuda = 0.0;

    // Leer el contenido de Movimientos y obtener el monto de deuda
    std::string linea;
    while (std::getline(archivoMovimientosLectura, linea)) {
        size_t pos = linea.find("Monto de Deuda:");
        if (pos != std::string::npos) {
            montoDeuda = std::stod(linea.substr(pos + 15));  // Longitud de "Monto de Deuda: "
            break;  // Salir del bucle si se encuentra el monto de deuda
        }
    }

    archivoMovimientosLectura.close();

    // Verificar si hay una deuda mayor a 0
    if (montoDeuda > 0.0) {
        // Realizar el pago automático
        system("cls");

        std::string rutaArchivoTabla = "DATOS/" + cedula + "tabla.txt";

        if (pagoTotal) {
            imprimirPagototal(cedula);
        } else {
            // Pago individual
           imprimirPagoUnitario(cedula);
        }
    } else {
        std::cout << "\nNo hay deuda pendiente para realizar el pago automatico." << std::endl;
    }
    mostrarMovimientosPorCedula(cedula);
}

vector<DatosTabla> Movimientos::obtenerDatosTabla(const string& cedula) {
    vector<DatosTabla> datosTabla;

    string rutaTabla = "DATOS/" + cedula + "tabla.txt";
    ifstream archivo(rutaTabla);

    if (!archivo.is_open()) {
        cerr << "\nError al abrir el archivo de la tabla: " << rutaTabla << endl;
        return datosTabla;
    }

    string linea;
    // Saltar la línea de encabezado de la tabla
    getline(archivo, linea);

    // Leer los datos de la tabla
    while (getline(archivo, linea)) {
        DatosTabla datos;

        // Utilizamos istringstream para leer cada campo
        istringstream iss(linea);

        if (!(iss >> datos.numero >> datos.cuotaFija >> datos.pagoCapital >> datos.interes >> datos.saldoCapital >> datos.fechaPago)) {
            cerr << "\nError al leer datos de la tabla en la linea: " << linea << endl;
            break;  // Salir del bucle si hay un error en la lectura
        }

        // Verificar si se leyó la información correctamente
        if (datos.numero > 0 && datos.cuotaFija >= 0 && datos.pagoCapital >= 0 && datos.interes >= 0 && datos.saldoCapital >= 0) {
            datosTabla.push_back(datos);
        } else {
            cerr << "\nError: Datos inconsistentes en la linea: " << linea << endl;
        }
    }

    archivo.close();
    return datosTabla;
}

void Movimientos::imprimirPagoUnitario(const std::string& cedula) {
    // Obtener los datos de la tabla original
    std::vector<DatosTabla> datosTablaOriginal = obtenerDatosTabla(cedula);
    
    // Obtener la posición actual desde el archivo
    int posicionActual = cargarPosicionActual(cedula);

    // Verificar si hay datos en la tabla original
    if (datosTablaOriginal.empty()) {
        std::cerr << "\nError: No se encontraron datos en la tabla original." << std::endl;
        return;
    }

    // Verificar si la posición actual está dentro de los límites
    if (posicionActual >= datosTablaOriginal.size()) {
        std::cerr << "\nError: Se alcanzó el final de la tabla original." << std::endl;
        return;
    }
    std::ofstream archivoMovimientos("Movimientos/" + cedula + ".txt", std::ios::app);
                            if (!archivoMovimientos.is_open()) {
                                std::cerr << "\nError al abrir el archivo de movimientos." << std::endl;
                                return;
                            }
    // Obtener el dato actual de la tabla original
    DatosTabla datoActual = datosTablaOriginal[posicionActual];

    int ancho_fecha = 20, ancho_deposito = 10, ancho_retiro = 10, ancho_saldo = 10;
    // Imprimir en el archivo
    archivoMovimientos << '|' << std::left << std::setw(ancho_fecha) << datoActual.fechaPago << '|'
                       << std::left << std::setw(ancho_deposito) << datoActual.cuotaFija << '|'
                       << std::left << std::setw(ancho_retiro) << datoActual.cuotaFija << '|'
                       << std::left << std::setw(ancho_saldo) << datoActual.cuotaFija - datoActual.cuotaFija << '|' << std::endl;

    // Incrementar la posición actual
     double montoDeudaActualizado = datoActual.saldoCapital;
        // Actualizar el Monto de Deuda en la tabla original
    actualizarMontoDeudaEnTablaOriginal(cedula, montoDeudaActualizado);
    +posicionActual;
    // Guardar la posición actual incrementada en el archivo
    guardarPosicionActual(cedula, posicionActual);

}
void Movimientos::guardarPosicionActual(const std::string& cedula, size_t posicion) {
    // Incrementar la posición antes de guardarla
    ++posicion;

    std::ofstream archivoPosicion("Movimientos/posicion_" + cedula + ".txt");
    if (!archivoPosicion.is_open()) {
        std::cerr << "\nError al abrir el archivo de posición." << std::endl;
        return;
    }

    archivoPosicion << posicion;
    archivoPosicion.close();
}

int Movimientos::cargarPosicionActual(const std::string& cedula) {
    std::ifstream archivoPosicion("Movimientos/posicion_" + cedula + ".txt");
    size_t posicion = 0;

    if (archivoPosicion.is_open()) {
        archivoPosicion >> posicion;
        archivoPosicion.close();
    }

    return posicion;
}


void Movimientos::imprimirPagototal(const std::string& cedula) {
    // Obtener los datos de la tabla original
    std::vector<DatosTabla> datosTabla = obtenerDatosTabla(cedula);

    // Verificar si hay datos en la tabla original
    if (datosTabla.empty()) {
        std::cerr << "\nError: No se encontraron datos en la tabla original." << std::endl;
        return;
    }

    // Obtener la posición actual desde el archivo
    size_t posicionActual = cargarPosicionActual(cedula);

    // Abrir el archivo en modo de apendizaje
    std::ofstream archivoMovimientos("Movimientos/" + cedula + ".txt", std::ios::app);
    int ancho_fecha = 20, ancho_deposito = 10, ancho_retiro = 10, ancho_saldo = 10, ancho_interes = 10;

    if (!archivoMovimientos.is_open()) {
        std::cerr << "\nError al abrir el archivo de movimientos." << std::endl;
        return;
    }

    // Imprimir la tabla desde la posición actual
    for (size_t i = posicionActual; i < datosTabla.size(); ++i) {
        const DatosTabla& datos = datosTabla[i];
        double deposito = datos.cuotaFija;
        double retiro = datos.cuotaFija;
        double interes = datos.interes;

        // Calcular el saldo
        double saldo = 0.0;

        // Imprimir en el archivo
        archivoMovimientos << '|' << std::left << std::setw(ancho_fecha) << datos.fechaPago << '|'
                           << std::left << std::setw(ancho_deposito) << deposito << '|'
                           << std::left << std::setw(ancho_retiro) << retiro << '|'
                           << std::left << std::setw(ancho_saldo) << saldo << '|' << std::endl;
    }

    // Cierra el archivo
    archivoMovimientos.close();
    actualizarMontoDeudaEnTablaOriginal(cedula, 0.0);

    // Actualizar la posición actual en el archivo
    guardarPosicionActual(cedula, datosTabla.size());
}

void Movimientos::actualizarMontoDeudaEnTablaOriginal(const std::string& cedula, double montoDeudaActualizado) {
    std::ifstream archivoLectura;
    std::ofstream archivoEscritura;
    std::string rutaArchivo = "Movimientos/" + cedula + ".txt";

    archivoLectura.open(rutaArchivo);

    if (!archivoLectura.is_open()) {
        std::cerr << "\nError al abrir el archivo para lectura." << std::endl;
        return;
    }

    std::string contenidoArchivo;
    std::string nuevaTabla;

    // Leer el contenido actual del archivo
    while (!archivoLectura.eof()) {
        std::string linea;
        std::getline(archivoLectura, linea);
        contenidoArchivo += linea + "\n";

        // Buscar la línea que contiene "Monto de Deuda:"
        size_t pos = linea.find("Monto de Deuda:");

        if (pos != std::string::npos) {
            // Reemplazar el valor actualizado en la línea
            std::stringstream montoFormateado;
            montoFormateado << std::fixed << std::setprecision(2) << montoDeudaActualizado;
            std::string nuevaLinea = "Monto de Deuda: " + montoFormateado.str();
            nuevaTabla += nuevaLinea + "\n";
        } else {
            // Conservar las demás líneas sin cambios
            nuevaTabla += linea + "\n";
        }
    }

    archivoLectura.close();

    // Escribir el contenido actualizado en el archivo
    archivoEscritura.open(rutaArchivo);

    if (!archivoEscritura.is_open()) {
        std::cerr << "\nError al abrir el archivo para escritura." << std::endl;
        return;
    }

    archivoEscritura << nuevaTabla;

    archivoEscritura.close();
}

void Movimientos::eliminarUsuario(const std::string& cedula) {
    // Verificar si el usuario tiene deuda pendiente
    if (tieneDeudaPendiente(cedula)) {
        std::cout << "\nEl usuario tiene deuda pendiente y no puede ser eliminado." << std::endl;
        return;
    }

    // Construir las rutas de los archivos y directorios asociados al usuario
    std::string rutaDatos = "DATOS/" + cedula + "tabla.txt";
    std::string rutaMovimientos = "Movimientos/" + cedula + ".txt";
    std::string rutaPrestamos = "Prestamos/" + cedula + ".txt";

    // Eliminar los archivos asociados al usuario
    eliminarArchivo(rutaDatos);
    eliminarArchivo(rutaMovimientos);
    eliminarArchivo(rutaPrestamos);
    eliminarUsuarioDeArchivo(cedula);
}

bool Movimientos::eliminarArchivo(const std::string& rutaArchivo) {
    if (remove(rutaArchivo.c_str()) != 0) {
        std::cerr << "\nError al eliminar el archivo " << rutaArchivo << std::endl;
        return false;
    }
    std::cout << "\nArchivo " << rutaArchivo << " eliminado correctamente." << std::endl;
    return true;
}

bool Movimientos::eliminarDirectorio(const std::string& rutaDirectorio) {
    if (rmdir(rutaDirectorio.c_str()) != 0) {
        std::cerr << "\nError al eliminar el directorio " << rutaDirectorio << std::endl;
        return false;
    }
    std::cout << "\nDirectorio " << rutaDirectorio << " eliminado correctamente." << std::endl;
    return true;
}

bool Movimientos::eliminarUsuarioDeArchivo(const std::string& cedulaAEliminar) {
    std::string nombreArchivo = "Usuarios.txt";

    // Abrir el archivo de Usuarios.txt para lectura
    std::ifstream archivoEntrada(nombreArchivo);
    if (!archivoEntrada.is_open()) {
        std::cerr << "\nError al abrir el archivo Usuarios.txt para lectura." << std::endl;
        return false;
    }

    // Leer todo el contenido del archivo línea por línea y almacenarlo en un vector
    std::vector<std::string> lineasArchivo;
    std::string linea;
    while (std::getline(archivoEntrada, linea)) {
        // Si la línea no contiene la cédula a eliminar, agrégala al vector
        if (linea.find(cedulaAEliminar) == std::string::npos) {
            lineasArchivo.push_back(linea);
        }
    }
    archivoEntrada.close();

    // Abrir el archivo de Usuarios.txt para escritura (truncar el archivo)
    std::ofstream archivoSalida(nombreArchivo, std::ios::trunc);
    if (!archivoSalida.is_open()) {
        std::cerr << "\nError al abrir el archivo Usuarios.txt para escritura." << std::endl;
        return false;
    }

    // Escribir todas las líneas excepto la del usuario a eliminar
    for (const std::string& linea : lineasArchivo) {
        archivoSalida << linea << std::endl;
    }
    archivoSalida.close();

    std::cout << "\nUsuario con cedula " << cedulaAEliminar << " eliminado correctamente del archivo Usuarios.txt." << std::endl;
    return true;
}

bool Movimientos::tieneDeudaPendiente(const std::string& cedula) {
    // Lógica para verificar si el usuario tiene deuda pendiente
    std::string rutaArchivoMovimientos = "Movimientos/" + cedula + ".txt";

    // Abrir el archivo de Movimientos para lectura
    std::ifstream archivoMovimientosLectura(rutaArchivoMovimientos);

    if (!archivoMovimientosLectura.is_open()) {
        std::cerr << "\nError al abrir el archivo de Movimientos para lectura." << std::endl;
        return false;
    }

    // Variable para almacenar el monto de deuda
    double montoDeuda = 0.0;

    // Leer el contenido de Movimientos y obtener el monto de deuda
    std::string linea;
    while (std::getline(archivoMovimientosLectura, linea)) {
        size_t pos = linea.find("Monto de Deuda:");
        if (pos != std::string::npos) {
            montoDeuda = std::stod(linea.substr(pos + 15));  // Longitud de "Monto de Deuda: "
            break;  // Salir del bucle si se encuentra el monto de deuda
        }
    }

    archivoMovimientosLectura.close();

    // Verificar si hay una deuda mayor a 0
    if (montoDeuda > 0.0) {
        return true; // El usuario tiene deuda pendiente
    }

    return false; // El usuario no tiene deuda pendiente
}

bool Movimientos::validarNuevoCredito(const std::string& cedula) {
    // Ruta del archivo de Movimientos
    std::string rutaArchivoMovimientos = "Movimientos/" + cedula + ".txt";

    // Abrir el archivo de Movimientos para lectura
    std::ifstream archivoMovimientosLectura(rutaArchivoMovimientos);

    if (!archivoMovimientosLectura.is_open()) {
        std::cerr << "\nError al abrir el archivo de Movimientos para lectura." << std::endl;
        return false;
    }

    // Variable para almacenar el monto de deuda
    double montoDeuda = 0.0;

    // Leer el contenido de Movimientos y obtener el monto de deuda
    std::string linea;
    while (std::getline(archivoMovimientosLectura, linea)) {
        size_t pos = linea.find("Monto de Deuda:");
        if (pos != std::string::npos) {
            montoDeuda = std::stod(linea.substr(pos + 15));  // Longitud de "Monto de Deuda: "
            break;  // Salir del bucle si se encuentra el monto de deuda
        }
    }

    archivoMovimientosLectura.close();

    // Verificar si hay una deuda mayor a 0
    if (montoDeuda > 0.0) {
        std::cout << "\nNo puede realizar un nuevo ingreso de credito. Tiene una deuda pendiente de: " << montoDeuda << std::endl;
        return false;
    } else {
        std::cout << "\nPuede realizar un nuevo ingreso de credito." << std::endl;
        return true;
    }
}


