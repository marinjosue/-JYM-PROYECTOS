#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <windows.h>
#include <string.h>
#include <iostream>
#define N 50

HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
using namespace std;

//Estructura que contiene las palabras en ingles y espa�ol
typedef struct{
	char eng[N];
	char esp[N];
	int lleno;
}traductor;

traductor trad[N];


//Prototipos de todas las funciones que se usan
void dibujarCuadro(int x1,int y1,int x2,int y2);
void gotoxy(int x,int y);
void CursorOn(bool visible, DWORD size);
void CursorOff();
void menu();
void limpia();
void ingresarp();
void vacio();
void traducirp();
void tradu(int op);
void cambio(char a[]);

int main(){

	cout << "               T R A D U C T O R";
	vacio();
	menu();
	getch();
	return 0;
}


void menu(){
	char op;
	CursorOn(1,10);
	do{
		gotoxy(4,6); cout << "MENU PRINCIPAL";
		gotoxy(4,9); cout << "(1) Ingresar palabras";
		gotoxy(4,11); cout << "(2) Traducir palabras";
		gotoxy(4,13); cout << "(3) Cerrar";
		gotoxy(4,15); cout << "Ingrese opcion: ";
		//scanf("%s",&op);
		cin >> op;

		if(op!='1' && op!='2' && op!='3'){
			gotoxy(4,22); cout << "Error al ingresar valores. Presione una tecla para volver a ingresar..";
			CursorOff();
			getch();
			gotoxy(4,22); cout << "                                                                       ";
			gotoxy(4,15); cout << "Ingrese opcion:               ";
			CursorOn(1,10);
		}

	}while(op!='1' && op!='2' && op!='3');


	if (op=='1'){
		ingresarp();
	}

	if (op=='2'){
		int a = 0;
		for(int i = 0; i < N && a==0; i++){
			if (trad[i].lleno == 1)
				a = 1;
		}
		if (a==0){
			CursorOff();
			gotoxy(4,21); cout << "No hay palabras para traducir. Primero se deben ingresar palabras.";
			gotoxy(4,23); cout << "Presione una tecla para continuar..";
			getch();
			gotoxy(4,15); cout << "                                                       ";
			gotoxy(4,21); cout << "                                                                    ";
			gotoxy(4,23); cout << "                                       ";
			menu();
		}
		else
			traducirp();
	}

	if (op=='3')
		exit(0);

}

void vacio(){
	for (int i = 0; i < N; i++){
		trad[i].lleno = 0;
	}
}

void ingresarp(){
	char op;
	int aux=0, rep=0;
	limpia();
	gotoxy(4,6); cout << "INGRESO DE PALABRAS";

	for (int i = 0; i < N && aux==0; i++){
		if(trad[i].lleno == 0){

			do{
			rep=0;
			CursorOn(1,10);
			gotoxy(4,9); cout << "Ingrese la palabra en Espanol: ";
			fflush(stdin);
			fgets(trad[i].esp,N,stdin);
			cambio(trad[i].esp);

			for(int j = 0; j < i && rep==0; j++){
				if(strcmp(trad[i].esp,trad[j].esp) == 0){
					rep = 1;
					CursorOff();
					gotoxy(4,22); cout << "Palabra ya guardada. Presione una tecla para volver a ingresar..";
					getch();
					gotoxy(4,22); cout << "                                                                  ";
					gotoxy(4,9); cout << "                                                           ";
				}
			}

			}while(rep!=0);

			CursorOn(1,10);
			gotoxy(4,11); cout << "Ingrese la palabra en Ingles: ";
			fflush(stdin);
			fgets(trad[i].eng,N,stdin);
			cambio(trad[i].eng);

			trad[i].lleno = 1;


			do{
				CursorOff();
				gotoxy(4,22); cout << "Pulse una tecla.. <1> Ingresar otra palabra / <2> Ir al menu principal ";
				op = getch();
			}while (op!='1' && op!='2');

			if(op=='1'){
					CursorOn(1,10);
					gotoxy(4,9); cout << "                                                        ";
					gotoxy(4,11); cout << "                                                        ";
					gotoxy(4,22); cout << "                                                                       ";
				}

			if (op == '2')
					aux=1;

		}
	}
	limpia();
	menu();
}

void traducirp(){
	int op, aux=0;
	limpia();
	gotoxy(4,6); cout << "TRADUCIR PALABRAS";

	do{
		gotoxy(4,9); cout << "(1) Traducir de Ingles a Espanol";
		gotoxy(4,11); cout << "(2) Traducir de Espanol a Ingles";
		gotoxy(4,13); cout << "Ingrese opcion: ";
		cin >> op;

		if(op<0 || op>2){
			gotoxy(4,22); cout << "Error al ingresar valores. Presione una tecla para volver a ingresar..";
			CursorOff();
			getch();
			gotoxy(4,13); cout << "Ingrese opcion:                     ";
			}

	}while(op<0 || op>2);


	if (op==1){
		tradu(op);
	}

	if (op==2)
		tradu(op);
}

void tradu(int op){
	int aux = 0;
	char palabra[N];
	char op2;
	limpia();


	if (op==1){
		gotoxy(4,6); cout << "TRADUCIR PALABRAS: INGLES A ESPANOL";

		gotoxy(4,9); cout << "Ingrese la palabra: ";
		fflush(stdin);
		fgets(palabra,N,stdin);
		cambio(palabra);

		for (int i = 0; i < N && aux == 0; i++){

			if(strcmp(palabra,trad[i].eng)	== 0){
				gotoxy(4,9); cout << "                                             ";
				gotoxy(4,9); cout << "INGLES:  " <<palabra;
				gotoxy(4,11); cout << "ESPANOL: " <<trad[i].esp;

				do{
					CursorOff();
					gotoxy(4,22); cout << "Pulse una tecla.. <1> Traducir otra palabra / <2> Ir al menu principal ";
					op2 = getch();
				}while (op2!='1' && op2!='2');

				if(op2=='1'){
					i=-1;
					CursorOn(1,10);
					gotoxy(4,9); cout << "                                                        ";
					gotoxy(4,11); cout << "                                                        ";
					gotoxy(4,22); cout << "                                                                       ";

					gotoxy(4,9); cout<< "Ingrese la palabra: ";
					fflush(stdin);
					fgets(palabra,N,stdin);
					cambio(palabra);
				}

				if (op2 == '2')
					aux=1;

			}

			if(i==N-1 && strcmp(palabra,trad[N-1].esp) != 0){
				CursorOff();
				gotoxy(4,22); cout << "Palabra no encontrada. Pulse una tecla para volver..";
				getch();
				limpia();
				menu();
			}

		}
	}

	if (op==2){
		gotoxy(4,6); cout << "TRADUCIR PALABRAS: ESPANOL A INGLES";

		gotoxy(4,9); cout << "Ingrese la palabra: ";
		fflush(stdin);
		fgets(palabra,N,stdin);
		cambio(palabra);

		for (int i = 0; i < N && aux == 0; i++){

			if(strcmp(palabra,trad[i].esp)	== 0){
				gotoxy(4,9); cout << "                                             ";
				gotoxy(4,9);  cout << "ESPANOL:  " <<palabra;
				gotoxy(4,11); cout << "INGLES:   " <<trad[i].eng;

				do{
					CursorOff();
					gotoxy(4,22); cout << "Pulse una tecla.. <1> Traducir otra palabra / <2> Ir al menu principal ";
					op2 = getch();
				}while (op2!='1' && op2!='2');

				if(op2=='1'){
					i=-1;
					CursorOn(1,10);
					gotoxy(4,9); cout<< "                                                        ";
					gotoxy(4,11); cout<< "                                                        ";
					gotoxy(4,22); cout<< "                                                                       ";

					gotoxy(4,9); cout << "Ingrese la palabra: ";
					fflush(stdin);
					fgets(palabra,N,stdin);
					cambio(palabra);
				}

				if (op2 == '2')
					aux=1;

			}

			if(i==N-1 && strcmp(palabra,trad[N-1].esp) != 0){
				CursorOff();
				gotoxy(4,22); cout << "Palabra no encontrada. Pulse una tecla para volver..";
				getch();
				limpia();
				menu();
			}

		}
	}

	limpia();
	menu();
}


void cambio(char a[]){
	int aux;
	aux = strlen(a);
	a[aux-1] = '\0';
}



void dibujarCuadro(int x1,int y1,int x2,int y2){
    int i;
    for (i=x1;i<x2;i++){
		gotoxy(i,y1); cout << "�";
		gotoxy(i,y2); cout << "�";
    }

    for (i=y1;i<y2;i++){
		gotoxy(x1,i); cout << "�";
		gotoxy(x2,i); cout << "�";
    }

    gotoxy(x1,y1); cout << "�";
    gotoxy(x1,y2); cout << "�";
    gotoxy(x2,y1); cout << "�";
    gotoxy(x2,y2); cout << "�";
}


void limpia(){
	int i,j;
	for(i=5;i<=23;i++){
		for(j=4;j<=74;j++){
			gotoxy(j,i); printf(" ");}}
}


void gotoxy(int x,int y){
      HANDLE hcon;
      hcon = GetStdHandle(STD_OUTPUT_HANDLE);
      COORD dwPos;
      dwPos.X = x;
      dwPos.Y= y;
      SetConsoleCursorPosition(hcon,dwPos);
}



void CursorOff(){
  CONSOLE_CURSOR_INFO cursor = {1, FALSE};
  SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursor);
}



void CursorOn(bool visible, DWORD size)
{
	if(size == 0)
	{
		size = 20;
	}
	CONSOLE_CURSOR_INFO lpCursor;
	lpCursor.bVisible = visible;
	lpCursor.dwSize = size;
	SetConsoleCursorInfo(console,&lpCursor);
}
