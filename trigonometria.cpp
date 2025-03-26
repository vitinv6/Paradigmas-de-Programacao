#include "trig_classe.hpp"
#include <cmath>  // Para usar a constante M_PI se precisar

void Trigonometria::atualizar_radianos() {
    angulo_radianos = angulo_graus * M_PI / 180.0;  // Usando a constante M_PI
}

Trigonometria::Trigonometria(double graus) : angulo_graus(graus) {
    atualizar_radianos();
}

void Trigonometria::definir_angulo(double graus) {
    angulo_graus = graus;
    atualizar_radianos();
}

// Aproximação usando série de Taylor para seno
double Trigonometria::seno_aproximado(double radianos) const {
    double termo = radianos;
    double resultado = termo;
    for (int i = 3; i < 10; i += 2) {
        termo *= -radianos * radianos / (i * (i - 1));
        resultado += termo;
    }
    return resultado;
}

// Aproximação usando série de Taylor para cosseno
double Trigonometria::cosseno_aproximado(double radianos) const {
    double termo = 1.0;
    double resultado = termo;
    for (int i = 2; i < 10; i += 2) {
        termo *= -radianos * radianos / (i * (i - 1));
        resultado += termo;
    }
    return resultado;
}

// Aproximação usando série de Taylor para tangente
double Trigonometria::tangente_aproximada(double radianos) const {
    return seno_aproximado(radianos) / cosseno_aproximado(radianos);
}

double Trigonometria::seno() const {
    return seno_aproximado(angulo_radianos); // Usa a versão aproximada
}

double Trigonometria::cosseno() const {
    return cosseno_aproximado(angulo_radianos); // Usa a versão aproximada
}

double Trigonometria::tangente() const {
    return tangente_aproximada(angulo_radianos); // Usa a versão aproximada
}

double Trigonometria::cotangente() const {
    return 1.0 / tangente_aproximada(angulo_radianos); // Usa a versão aproximada
}

double Trigonometria::secante() const {
    return 1.0 / cosseno_aproximado(angulo_radianos); // Usa a versão aproximada
}

double Trigonometria::cossecante() const {
    return 1.0 / seno_aproximado(angulo_radianos); // Usa a versão aproximada
}

// Sobrecarga de operador para seno da soma (identidade trigonométrica)
double Trigonometria::operator+(const Trigonometria &outro) const {
    return seno_aproximado(angulo_radianos + outro.angulo_radianos); // Seno da soma
}

// Sobrecarga de operador para seno da diferença (identidade trigonométrica)
double Trigonometria::operator-(const Trigonometria &outro) const {
    return seno_aproximado(angulo_radianos - outro.angulo_radianos); // Seno da diferença
}

// Sobrecarga de operador para cosseno da soma (identidade trigonométrica)
double Trigonometria::operator*(const Trigonometria &outro) const {
    return cosseno_aproximado(angulo_radianos) * cosseno_aproximado(outro.angulo_radianos) 
           - seno_aproximado(angulo_radianos) * seno_aproximado(outro.angulo_radianos); // Cosseno da soma
}

// Sobrecarga de operador para cosseno da diferença (identidade trigonométrica)
double Trigonometria::operator/(const Trigonometria &outro) const {
    return cosseno_aproximado(angulo_radianos) * cosseno_aproximado(outro.angulo_radianos)
           + seno_aproximado(angulo_radianos) * seno_aproximado(outro.angulo_radianos); // Cosseno da diferença
}