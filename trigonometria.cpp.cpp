// CÓDIGO MODIFICADO!
#include "trigonometria.hpp"

// Aproximação de PI sem usar <cmath>
const double PI = 3.141592653589793;

void Trigonometria::atualizar_radianos() {
    angulo_radianos = angulo_graus * PI / 180.0;
}

Trigonometria::Trigonometria(double graus) : angulo_graus(graus) {
    atualizar_radianos();
}

void Trigonometria::definirAngulo(double graus) {
    angulo_graus = graus;
    atualizar_radianos();
}

// Aproximação usando série de Taylor para seno
double Trigonometria::seno_aproximado(double radianos) const {
    double termo = radianos;
    double resultado = termo;
    for (int i = 3; i <= 15; i += 2) {
        termo *= -radianos * radianos / (i * (i - 1));
        resultado += termo;
    }
    return resultado;
}

// Aproximação usando série de Taylor para cosseno
double Trigonometria::cosseno_aproximado(double radianos) const {
    double termo = 1.0;
    double resultado = termo;
    for (int i = 2; i <= 14; i += 2) {
        termo *= -radianos * radianos / (i * (i - 1));
        resultado += termo;
    }
    return resultado;
}

// Aproximação usando razão entre seno e cosseno para tangente
double Trigonometria::tangente_aproximada(double radianos) const {
    return seno_aproximado(radianos) / cosseno_aproximado(radianos);
}

double Trigonometria::seno() const {
    return seno_aproximado(angulo_radianos);
}

double Trigonometria::cosseno() const {
    return cosseno_aproximado(angulo_radianos);
}

double Trigonometria::tangente() const {
    return tangente_aproximada(angulo_radianos);
}

double Trigonometria::getRadianos() const {
    return angulo_radianos;
}