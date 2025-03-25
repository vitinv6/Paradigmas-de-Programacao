#include "trig_classe.hpp"

void Trigonometria::atualizar_radianos() {
    angulo_radianos = angulo_graus * M_PI / 180.0;
}

Trigonometria::Trigonometria(double graus) : angulo_graus(graus) {
    atualizar_radianos();
}

void Trigonometria::definir_angulo(double graus) {
    angulo_graus = graus;
    atualizar_radianos();
}

double Trigonometria::seno() const {
    return std::sin(angulo_radianos);
}

double Trigonometria::cosseno() const {
    return std::cos(angulo_radianos);
}

double Trigonometria::tangente() const {
    return std::tan(angulo_radianos);
}

double Trigonometria::cotangente() const {
    return 1.0 / std::tan(angulo_radianos);
}

double Trigonometria::secante() const {
    return 1.0 / std::cos(angulo_radianos);
}

double Trigonometria::cossecante() const {
    return 1.0 / std::sin(angulo_radianos);
}

double Trigonometria::operator+(const Trigonometria &outro) const {
    return std::sin(angulo_radianos + outro.angulo_radianos);
}

double Trigonometria::operator-(const Trigonometria &outro) const {
    return std::sin(angulo_radianos - outro.angulo_radianos);
}

double Trigonometria::operator*(const Trigonometria &outro) const {
    return std::cos(angulo_radianos + outro.angulo_radianos);
}

double Trigonometria::operator/(const Trigonometria &outro) const {
    return std::cos(angulo_radianos - outro.angulo_radianos);
}