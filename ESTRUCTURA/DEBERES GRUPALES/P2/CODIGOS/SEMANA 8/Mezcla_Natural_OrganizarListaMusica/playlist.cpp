// playlist.cpp
#include "playlist.h"

void merge(std::vector<Song>& playlist, int left, int middle, int right) {
    int n1 = middle - left + 1;
    int n2 = right - middle;

    // Crear listas temporales
    std::vector<Song> leftList(n1);
    std::vector<Song> rightList(n2);

    // Copiar datos a las listas temporales leftList[] y rightList[]
    for (int i = 0; i < n1; i++)
        leftList[i] = playlist[left + i];
    for (int j = 0; j < n2; j++)
        rightList[j] = playlist[middle + 1 + j];

    // Combinar las listas temporales en la lista original playlist[]
    int i = 0, j = 0, k = left;
    while (i < n1 && j < n2) {
        // Cambia el criterio de comparación según sea necesario (por ejemplo, por título o artista)
        if (leftList[i].title <= rightList[j].title) {
            playlist[k] = leftList[i];
            i++;
        } else {
            playlist[k] = rightList[j];
            j++;
        }
        k++;
    }

    // Copiar los elementos restantes de leftList[], si los hay
    while (i < n1) {
        playlist[k] = leftList[i];
        i++;
        k++;
    }

    // Copiar los elementos restantes de rightList[], si los hay
    while (j < n2) {
        playlist[k] = rightList[j];
        j++;
        k++;
    }
}

void externalMergeSort(std::vector<Song>& playlist, int left, int right) {
    if (left < right) {
        // Encuentra el punto medio del arreglo
        int middle = left + (right - left) / 2;

        // Ordena primero y segundo semirrangos
        externalMergeSort(playlist, left, middle);
        externalMergeSort(playlist, middle + 1, right);

        // Mezcla los semirrangos ordenados
        merge(playlist, left, middle, right);
    }
}
