#include <iostream>
#include <cmath>
#include <sys/time.h>

// Definición de la función a integrar
double f(double x) {
    return sin(x); // Ejemplo: integrando sin(x)
}

// Algoritmo de cuadratura recursiva
double cuadratura_recursiva(double a, double b, double tol, double fa, double fb, double area) {
    double c = (a + b) / 2;
    double fc = f(c);
    double izquierda = (fa + fc) * (c - a) / 2;
    double derecha = (fc + fb) * (b - c) / 2;
    double nueva_area = izquierda + derecha;

    if (std::fabs(nueva_area - area) < tol) {
        return nueva_area;
    } else {
        return cuadratura_recursiva(a, c, tol / 2, fa, fc, izquierda) + cuadratura_recursiva(c, b, tol / 2, fc, fb, derecha);
    }
}

double integrar(double a, double b, double tol) {
    double fa = f(a);
    double fb = f(b);
    double area_inicial = (fa + fb) * (b - a) / 2;
    return cuadratura_recursiva(a, b, tol, fa, fb, area_inicial);
}

int main() {
    double a = 0.0;
    double b = M_PI;
    double tol = 1e-6;

    struct timeval t0, t1;
    gettimeofday(&t0, 0);
    double resultado = integrar(a, b, tol);
    gettimeofday(&t1, 0);

    double tiempo = (t1.tv_sec - t0.tv_sec) * 1.0f + (t1.tv_usec - t0.tv_usec) / 1000000.0f;

    std::cout << "Resultado de la integración (secuencial): " << resultado << std::endl;
    std::cout << "Tiempo de ejecución (secuencial): " << tiempo * 1000 << " ms" << std::endl;

    return 0;
}
