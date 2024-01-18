// main.cpp
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include "playlist.h"

int main() {
    // Lectura de la lista de reproducción desde un archivo
    std::ifstream inputFile("playlist.txt");
    std::vector<Song> playlist;

    // Asume que cada línea del archivo tiene el formato "Título,Artista"
    std::string line;
    while (getline(inputFile, line)) {
        size_t pos = line.find(',');
        Song song;
        song.title = line.substr(0, pos);
        song.artist = line.substr(pos + 1);
        playlist.push_back(song);
    }

    inputFile.close();

    // Realiza el ordenamiento externo de mezcla
    externalMergeSort(playlist, 0, playlist.size() - 1);

    // Imprime la lista de reproducción ordenada
    for (const auto& song : playlist) {
        std::cout << "Titulo: " << song.title << ", Artista: " << song.artist << std::endl;
    }

    return 0;
}
