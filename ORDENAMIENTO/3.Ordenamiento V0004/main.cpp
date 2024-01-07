/***********************************************************************
 * Module:  main.cpp
 * Author:  Josue Marin
 * Modified: viernes, 1 de diciembre de 2023 12:05:38 a. m.
 * Purpose: Declaration of the class main
 ***********************************************************************/

#include <iostream>
#include "Nodo.h"
#include "menu.h"
#include "ListaDoble.h"



int main()
{
    Menus menu;
    menu.Menu_Principal();
    /*
    int opcion, dato, seguir;
    std::string opcion2;
    ListaDoble lista;
    ListaDoble lista2; // Cambiando la instancia de ListaSimple a ListaDoble

    do {
        system("cls");
        printf("\n1. Insertar elementos a la lista por la cabeza");
        printf("\n2. Insertar elementos a la lista por la cola");
        printf("\n3. Imprimir elementos de la lista empezando por la cabeza");
        printf("\n4. Imprimir elementos de la lista empezando por la cola");
        printf("\n5. Buscar primera ocurrencia del elemento");
        printf("\n6. Eliminar elemento de la lista por la cola");
        printf("\n7. Eliminar elemento de la lista por la cabeza");
        printf("\n8. Invertir lista");
        printf("\n9. Insertar despues de");
        printf("\n0. Salir");
        opcion2 = ingresar_alfabetico("\nIngrese una opcion del menu");

        switch(opcion) {
            case 1:
                dato = ingresar_enteros("\nIngresar un entero como dato del nodo a insertar");
                printf("\n");
                lista.insertar_cabeza(dato);
                lista2.insertar_cabeza(dato);
                lista.imprimir_cabeza();
                system("pause");
                break;
            case 2:
                dato = ingresar_enteros("\nIngresar un entero como dato del nodo a insertar");
                printf("\n");
                lista.insertar_cola(dato);
                lista2.insertar_cola(dato);
                lista.imprimir_cabeza();
                system("pause");
                break;
            case 3:
                lista.imprimir_cabeza();
                system("pause");
                break;
            case 4:
                lista.imprimir_cola();
                system("pause");
                system("pause");
                break;
            case 5:
                dato = ingresar_enteros("\nIngrese el numero a buscar");
                lista.buscar(dato);
                system("pause");
                break;
            case 6:
                lista.eliminar_cola();
                lista.imprimir_cabeza();
                system("pause");
                break;
            case 7:
                lista.eliminar_cabeza();
                lista.imprimir_cabeza();
                system("pause");
                break;
            case 8:
                lista.imprimir_cabeza();
                printf("Lista invertida: ");
                lista2.invertirUnaVez();
                lista2.imprimir_cabeza();
                system("pause");
                break;

            system("pause");
            break;
            case 9:
                int dato, posicion_nodo_actual;
                dato = ingresar_enteros("\nIngresar un entero como dato del nuevo nodo");
                posicion_nodo_actual = ingresar_enteros("\nIngresar la posici�n del nodo despu�s del cual deseas insertar");

                Nodo* nodo_actual = lista.buscar_nodo(posicion_nodo_actual);

                if (nodo_actual != nullptr) {
                    lista.insertar_despues_de(nodo_actual, dato);
                    printf("\nElemento %d insertado despues del nodo en la posicion %d\n", dato, posicion_nodo_actual);
                    lista.imprimir_cabeza();
                } else {
                    printf("\nNodo en la posici�n %d no encontrado\n", posicion_nodo_actual);
                }

                system("pause");
                break;


        }
    } while(opcion != 0);
*/
    return 0;
}
