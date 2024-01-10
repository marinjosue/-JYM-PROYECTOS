/***********************************************************************
 * UFA - ESPE
 *Module:  Amortizacion.cpp
 * Author:  Ronny Ibarra-Jose Imbaquinga
 * Modified: sábado, 5 de noviembre de 2022 10:24:22
 * Purpose: Implementation of the class Amortizacion
 *Level: level three
 *NRC:799
 ***********************************************************************/

#if !defined(__Amortizacion2_Amortizacion_h)
#define __Amortizacion2_Amortizacion_h

class Amortizacion
{
public:
   int getAnio(void);
   void setAnio(int newAnio);
   int getSaldoInicial(void);
   void setSaldoInicial(int newSaldoInicial);
   double getInteres(void);
   void setInteres(double newInteres);
   double getAmortizacion(void);
   void setAmortizacion(double newAmortizacion);
   double getPago(void);
   void setPago(double newPago);
   double getSaldoFinal(void);
   void setSaldoFinal(double newSaldoFinal);
   int getDia(void);
   void setDia(int newDia);
   int getMes(void);
   void setMes(int newMes);
   Amortizacion();
   double calculoInteres(double saldo_Final, double interes);
   double calculoAmortizacion(double , double );
   double calculoPago(double interes, double calculo_amortizacion);
   double saldoFinal(double saldoInicial, double calculo_amortizacion);
   void generarTablaAmortizacion(int);
   void feriado(int dia, int mes);


protected:
private:

   int anio;
   int saldoInicial;
   double interes;
   double calculo_amortizacion;
   double pago;
   double saldo_Final;
   int dia;
   int mes;


};

#endif
