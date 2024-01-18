// playlist.h
#pragma once

#include <vector>
#include <string>

struct Song {
    std::string title;
    std::string artist;
    // Agrega más campos según sea necesario
};

void merge(std::vector<Song>& playlist, int left, int middle, int right);
void externalMergeSort(std::vector<Song>& playlist, int left, int right);


