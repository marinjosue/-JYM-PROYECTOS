/*************************
 UFA - ESPE
 * Module:  CalculosCredito.cpp
 * Author:  Chiliquinga Yeshua, Marin Alquinga,Salcedo Micaela
 * Modified: domingo, 17 de diciembre de 2023
 * Purpose: Implementacion de clase Amortizacion
 *************************/
#include <iostream>
#include <fstream>
#include "Amortizacion.h"
#include "CalculosCredito.h"
#include "Fecha.h"
#include "ListaDoble.cpp"
#include "Extra.h"
#include "Nodo.cpp"
#include <iomanip>
#include <ctime>
#include "validaciones.h"
#include "Movimientos.h"
#include "Cuenta.h"
#include <sys/stat.h>
#include <cerrno>


using namespace std;

Amortizacion::Amortizacion(){

}
Amortizacion::Amortizacion(Credito credito_usar){
    credito = credito_usar;
    cuotas_ord = new ListaDoble<int>();
    saldos_capital= new ListaDoble<double>();
    intereses= new ListaDoble<double>();
    pagos_capital= new ListaDoble<double>();
    valor_cuotas= new ListaDoble<double>();
    fechas_pago= new ListaDoble<Fecha>();
    llenar_tabla_amortizacion();
}

Credito Amortizacion::get_credito(){
    return credito;
}

ListaDoble<int>* Amortizacion::get_cuotas_ord(){
    return cuotas_ord;
}

ListaDoble<double>* Amortizacion::get_saldos_capital(){
    return saldos_capital;
}

ListaDoble<double>* Amortizacion::get_intereses(){
    return intereses;
}

ListaDoble<double>* Amortizacion::get_pagos_capital(){
    return pagos_capital;
}

ListaDoble<double>* Amortizacion::get_valor_cuotas(){
    return valor_cuotas;
}

ListaDoble<Fecha>* Amortizacion::get_fechas_pago(){
    return fechas_pago;
}

void Amortizacion::set_credito(Credito nuevo_credito){
    credito = nuevo_credito;
}

void Amortizacion::set_cuotas_ord(ListaDoble<int>* nuevo_cuotas_ord){
    cuotas_ord = nuevo_cuotas_ord;
}

void Amortizacion::set_saldos_capital(ListaDoble<double>* nuevo_saldos_capital){
    saldos_capital = nuevo_saldos_capital;
}

void Amortizacion::set_intereses(ListaDoble<double>* nuevo_intereses){
    intereses = nuevo_intereses;
}

void Amortizacion::set_pagos_capital(ListaDoble<double>* nuevo_pagos_capital){
    pagos_capital = nuevo_pagos_capital;
}

void Amortizacion::set_valor_cuotas(ListaDoble<double>* nuevo_valor_cuotas){
    valor_cuotas = nuevo_valor_cuotas;
}

void Amortizacion::set_fechas_pago(ListaDoble<Fecha>* nuevo_fechas_pago){
    fechas_pago = nuevo_fechas_pago;
}

void Amortizacion::generar_fechas_pago(){
    Fecha fecha_sacado = credito.get_fecha_realizado();
    int ncuotas = credito.get_n_cuotas_pagar();
    int meses_gracia = credito.get_meses_gracia();
    int intervalo_pagos_mes = credito.get_intervalo_pagos_mes();
    Fecha fecha_gen = fecha_sacado;
    fecha_gen.set_mes(fecha_gen.get_mes() + meses_gracia);
    int n_gen = 0;

    while(fecha_gen.es_finde() || fecha_gen.es_feriado()){
        fecha_gen.set_dia(fecha_gen.get_dia()+1);
    }
    fechas_pago->insertar_cola(fecha_gen);
    n_gen++;

    while(n_gen<ncuotas){
        fecha_gen.set_mes(fecha_gen.get_mes() + intervalo_pagos_mes);
        while(fecha_gen.es_finde() || fecha_gen.es_feriado()){
            fecha_gen.set_dia(fecha_gen.get_dia()+1);
        }
        fechas_pago->insertar_cola(fecha_gen);
        n_gen++;
    }
}

void Amortizacion::llenar_tabla_amortizacion(){
    CalculosCredito calculos(15);
    double v_cuotas = calculos.calcular_valor_cuotas(credito.get_n_cuotas_pagar(), credito.get_monto());
    int n_ord = 1;
    while(n_ord<=credito.get_n_cuotas_pagar()){
        cuotas_ord->insertar_cola(n_ord);
        valor_cuotas->insertar_cola(v_cuotas);
        n_ord++;
    }

    calculos.calcular_valor_intereses(credito.get_n_cuotas_pagar(), credito.get_monto(), v_cuotas, intereses);
    calculos.calcular_capitales_pagados(v_cuotas, pagos_capital, intereses->get_cabeza());
    calculos.calcular_saldos_restantes(credito.get_monto(), v_cuotas, saldos_capital, pagos_capital->get_cabeza());
    generar_fechas_pago();
}
void Amortizacion::imprimirYGuardar(const std::string& cedula) {
    int n_mostrados = 0;
    int n_mostrar = credito.get_n_cuotas_pagar();
    Nodo<int>* ord = cuotas_ord->get_cabeza();
    Nodo<double>* saldo_cap = saldos_capital->get_cabeza();
    Nodo<double>* interes = intereses->get_cabeza();
    Nodo<double>* capital_pag = pagos_capital->get_cabeza();
    Nodo<double>* valor_cuota = valor_cuotas->get_cabeza();
    Nodo<Fecha>* aux_fecha_pagar = fechas_pago->get_cabeza();
    Fecha fecha_pagar;

    // Ruta del archivo para guardar la tabla
    std::string rutaArchivo = "DATOS/" + cedula + "tabla.txt";

    // Abrir el archivo para escritura (agregar al final)
    std::ofstream archivoTabla(rutaArchivo, std::ios::trunc);

    if (!archivoTabla.is_open()) {
        std::cerr << "Error al abrir el archivo para guardar la tabla." << std::endl;
        return;
    }

    int ancho_ord = 10, ancho_vcuota = 12, ancho_capital = 12, ancho_interes = 10, ancho_saldo = 15, ancho_fecha = 14;

    // Encabezado de la tabla
    archivoTabla << std::setw(ancho_ord) << "No." 
                 << std::setw(ancho_vcuota) << "CUOTA FIJA" 
                 << std::setw(ancho_capital) << "PAGO CAPITAL"
                 << std::setw(ancho_interes) << "INTERES"
                 << std::setw(ancho_saldo) << "SALDO CAPITAL"
                 << std::setw(ancho_fecha) << "FECHA DE PAGO"<< "\n";
    while (n_mostrados < n_mostrar) {
        fecha_pagar = aux_fecha_pagar->get_valor();
        archivoTabla << std::setw(ancho_ord) << ord->get_valor() 
                     << std::fixed << std::setprecision(2)  // Establecer precisión a 2 decimales
                     << std::setw(ancho_vcuota) << valor_cuota->get_valor() 
                     << std::setw(ancho_capital) << capital_pag->get_valor()
                     << std::setw(ancho_interes) << interes->get_valor()
                     << std::setw(ancho_saldo) << saldo_cap->get_valor()
                     << std::setw(ancho_fecha) << fecha_pagar.to_string()<< "\n";

        ord = ord->get_siguiente();
        saldo_cap = saldo_cap->get_siguiente();
        interes = interes->get_siguiente();
        capital_pag = capital_pag->get_siguiente();
        valor_cuota = valor_cuota->get_siguiente();
        aux_fecha_pagar = aux_fecha_pagar->get_siguiente();
        n_mostrados++;
    }

    // Cerrar el archivo
    archivoTabla.close();

    // Imprimir la tabla en la consola después de cerrar el archivo
    std::cout << "\nContenido de la tabla guardada:\n";
    std::ifstream archivoLectura(rutaArchivo);

    if (archivoLectura.is_open()) {
        std::string linea;
        while (std::getline(archivoLectura, linea)) {
            std::cout << linea << '\n';
        }
        archivoLectura.close();
    } else {
        std::cerr << "Error al abrir el archivo para lectura." << std::endl;
    }

    std::cout << "\nLa tabla se ha guardado en el archivo '" << rutaArchivo << "'.\n\n";
}


void Amortizacion::guardarTabla(const std::string& nombreArchivo, const std::string& cedula,
                                const std::string& nombreCompleto, const std::string& id,
                                const std::string& Ncuenta, double monto, int ncuotas,
                                double tasa_interes) {
    std::ofstream archivo(nombreArchivo);
    Fecha fecha;

    if (!archivo.is_open()) {
        std::cerr << "Error al abrir el archivo: " << nombreArchivo << std::endl;
        return;
    }
    // Obtener la fecha y hora actual utilizando la nueva función
    std::string fechaHoraGeneracion = fecha.obtenerFechaHoraActual();

    // Imprimir la fecha y hora de generación de la tabla
    archivo << "Tabla generada el " << fechaHoraGeneracion << "\n\n";

    // Imprimir información del cliente
    archivo << "Datos del cliente:\n";
    archivo << "Cedula: " << cedula << "\n";
    archivo << "Nombre: " << nombreCompleto << "\n";
    archivo << "ID: " << id << "\n";
    archivo << "No.Cuenta: " << Ncuenta << "\n";
    archivo << "Monto: " << monto << "\n";
    archivo << "No.Cuotas: " << ncuotas << "\n";
    archivo << "Tasa de interes: " << tasa_interes << "\n\n";

    int n_mostrados = 0;
    int n_mostrar = credito.get_n_cuotas_pagar();
    Nodo<int>* ord = cuotas_ord->get_cabeza();
    Nodo<double>* saldo_cap = saldos_capital->get_cabeza();
    Nodo<double>* interes = intereses->get_cabeza();
    Nodo<double>* capital_pag = pagos_capital->get_cabeza();
    Nodo<double>* valor_cuota = valor_cuotas->get_cabeza();
    Nodo<Fecha>* aux_fecha_pagar = fechas_pago->get_cabeza();
    Fecha fecha_pagar;

    // Configurar el ancho de cada columna
    int ancho_ord = 10, ancho_vcuota = 12, ancho_capital = 12, ancho_interes = 10, ancho_saldo = 15, ancho_fecha = 14;

    // Encabezado de la tabla
    archivo << '|' << std::setw(ancho_ord) << "No." << '|'
                 << std::setw(ancho_vcuota) << "CUOTA FIJA" << '|'
                 << std::setw(ancho_capital) << "PAGO CAPITAL" << '|'
                 << std::setw(ancho_interes) << "INTERES" << '|'
                 << std::setw(ancho_saldo) << "SALDO CAPITAL" << '|'
                 << std::setw(ancho_fecha) << "FECHA DE PAGO" << '|' << "\n";
    archivo << std::string(ancho_ord + ancho_vcuota + ancho_capital + ancho_interes + ancho_saldo + ancho_fecha + 6 * 2, '-') << "\n";

     while (n_mostrados < n_mostrar) {
        fecha_pagar = aux_fecha_pagar->get_valor();
        archivo << '|' << std::setw(ancho_ord) << ord->get_valor() << '|'
                     << std::setw(ancho_vcuota) << std::fixed << std::setprecision(2) << valor_cuota->get_valor() << '|'
                     << std::setw(ancho_capital) << std::fixed << std::setprecision(2) << capital_pag->get_valor() << '|'
                     << std::setw(ancho_interes) << std::fixed << std::setprecision(2) << interes->get_valor() << '|'
                     << std::setw(ancho_saldo) << std::fixed << std::setprecision(2) << saldo_cap->get_valor() << '|'
                     << std::setw(ancho_fecha) << fecha_pagar.to_string() << '|' << "\n";

        ord = ord->get_siguiente();
        saldo_cap = saldo_cap->get_siguiente();
        interes = interes->get_siguiente();
        capital_pag = capital_pag->get_siguiente();
        valor_cuota = valor_cuota->get_siguiente();
        aux_fecha_pagar = aux_fecha_pagar->get_siguiente();
        n_mostrados++;
    }

    archivo.close();
    cout<<"\nLA TABLA DE CREDITOS SE GUARDO EN EL ARCHIVO '"<<nombreArchivo<<"'.\n\n'";
    createBackupRegistro();
    createBackupRegistro(cedula);
   
}



void Amortizacion::ingresar_datos_credito() {
    validaciones valida;
    Movimientos mov;
    Cuenta nuevacuenta;
    std::string cedula;

    do {
        cedula = valida.ingresar_numeros_como_string("\nIngrese el numero de cedula: ");

        if (valida.validarCedula(cedula) && nuevacuenta.verificarCedulaA("Usuarios.txt", cedula)) {
            system("cls");

            // Validar si la persona puede realizar un nuevo ingreso de crédito
            if (!mov.validarNuevoCredito(cedula)) {
                // Si tiene deuda pendiente, mostrar mensaje y salir de la función
                return;
            }

            // Obtener datos del usuario
            std::ifstream archivoUsuarios("Usuarios.txt");
            if (archivoUsuarios.is_open()) {
                DatosUsuario datosUsuario = nuevacuenta.mostrarDatosUsuarios("Usuarios.txt", cedula);
                std::string nombreCompleto = datosUsuario.nombreCompleto;
                std::string id = datosUsuario.id;
                std::string Ncuenta = datosUsuario.Ncuenta;
                archivoUsuarios.close();

                // Resto de la lógica para ingresar los datos del crédito
                Fecha sacado;
                double monto = 0, tasa_interes = 0;
                int ncuotas = 0;

                // Bucle para ingresar monto
                while (monto <= 999 || monto > 99999999.99) {
                    monto = valida.ingresar_reales("\nIngrese el monto del credito");

                    if (monto <= 999 || monto > 99999999.99) {
                        printf("\nEl monto debe ser mayor a 999 y menor a 100M");
                    } else {
                        printf("                                                           ");
                    }
                }

                // Bucle para ingresar número de cuotas
                while (ncuotas <= 0 || ncuotas > 500) {
                    ncuotas = valida.ingresar_enteros("\nIngrese el numero de cuotas a pagar del credito");

                    if (ncuotas <= 0 || ncuotas > 500) {
                        printf("El numero de cuotas debe ser mayor a 0 y menor a 500");
                    } else {
                        printf("                                                           ");
                    }
                }
                // Bucle para ingresar tasa de interés
                while (tasa_interes <= 0 || tasa_interes > 99.99) {
                    tasa_interes = valida.ingresar_reales("\nIngrese la tasa de interes del credito");

                    if (tasa_interes <= 0 || tasa_interes > 99.99) {
                        printf("La tasa de interes debe ser mayor a 0 y menor a 100%");
                    } else {
                        printf("                                                           ");
                    }
                }

                // Crear objetos Credito y Amortizacion con los datos ingresados
                Credito credito(ncuotas, monto, sacado, tasa_interes);
                Amortizacion tabla(credito);

                // Imprimir y guardar la tabla de amortización
                printf("\n");
                tabla.imprimirYGuardar(cedula);
                printf("\nTABLA GUARDADA CORRECTAMENTE");
                tabla.guardarTabla("tabla_amortizacion.txt",cedula, datosUsuario.nombreCompleto, datosUsuario.id, datosUsuario.Ncuenta, monto, ncuotas, tasa_interes);
                printf("\n");
                mov.guardarMontoDeuda(cedula, monto);
                system("pause");

                break;  // Salir del bucle do-while
            } else {
                cout << "\nLa cedula ingresada no es valida o no existe. Vuelva a intentarlo." << endl;
            }
        }
    } while (true);
}

