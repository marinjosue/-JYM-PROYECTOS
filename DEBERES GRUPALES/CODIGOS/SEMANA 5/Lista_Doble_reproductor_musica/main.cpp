#include <iostream>
#include "ReproductorMusica.h"

int main() {
    ReproductorMusica reproductor;

    reproductor.agregarCancion("Cancion1");
    reproductor.agregarCancion("Cancion2");
    reproductor.agregarCancion("Cancion3");

    std::cout << "Lista de reproduccion inicial:" << std::endl;
    reproductor.mostrarListaReproduccion();

    reproductor.reproducirSiguiente();
    reproductor.reproducirAnterior();

    reproductor.eliminarCancion("Cancion2");

    std::cout << "Lista de reproduccion despues de eliminar Cancion2:" << std::endl;
    reproductor.mostrarListaReproduccion();

    return 0;
}
