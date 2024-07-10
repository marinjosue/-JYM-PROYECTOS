#include <iostream>
#include <cmath>
#include <omp.h>
#include <sys/time.h>

// Definición de la función a integrar
double f(double x) {
    return sin(x); // Ejemplo: integrando sin(x)
}

// Algoritmo de cuadratura recursiva paralela
double cuadratura_paralela(double a, double b, double tol, double fa, double fb, double area, int depth = 0) {
    double c = (a + b) / 2;
    double fc = f(c);
    double izquierda = (fa + fc) * (c - a) / 2;
    double derecha = (fc + fb) * (b - c) / 2;
    double nueva_area = izquierda + derecha;

    if (std::fabs(nueva_area - area) < tol) {
        return nueva_area;
    } else {
        if (depth < 4) { // Limitar la recursión paralela para evitar overhead excesivo
            double resultado_izq, resultado_der;

            #pragma omp parallel sections
            {
                #pragma omp section
                resultado_izq = cuadratura_paralela(a, c, tol / 2, fa, fc, izquierda, depth + 1);
                #pragma omp section
                resultado_der = cuadratura_paralela(c, b, tol / 2, fc, fb, derecha, depth + 1);
            }

            return resultado_izq + resultado_der;
        } else {
            return cuadratura_paralela(a, c, tol / 2, fa, fc, izquierda, depth + 1) + cuadratura_paralela(c, b, tol / 2, fc, fb, derecha, depth + 1);
        }
    }
}

double integrar_paralelo(double a, double b, double tol) {
    double fa = f(a);
    double fb = f(b);
    double area_inicial = (fa + fb) * (b - a) / 2;
    return cuadratura_paralela(a, b, tol, fa, fb, area_inicial);
}

int main() {
    double a = 0.0;
    double b = M_PI;
    double tol = 1e-6;

    struct timeval t0, t1;
    double resultado;

    // Proceso secuencial
    gettimeofday(&t0, 0);
    resultado = integrar_paralelo(a, b, tol);
    gettimeofday(&t1, 0);
    double tiempo_secuencial = (t1.tv_sec - t0.tv_sec) * 1.0f + (t1.tv_usec - t0.tv_usec) / 1000000.0f;
    std::cout << "Resultado de la integración (paralela): " << resultado << std::endl;
    std::cout << "Tiempo de ejecución (paralela): " << tiempo_secuencial * 1000 << " ms" << std::endl;

    return 0;
}
