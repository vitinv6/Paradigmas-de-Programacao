#ifndef TRIG_CLASSE_HPP
#define TRIG_CLASSE_HPP

#include <iostream>

class Trigonometria {
private:
    double angulo_graus;
    double angulo_radianos;

    void atualizar_radianos();

    // Funções trigonométricas implementadas manualmente:
    double seno_aproximado(double radianos) const;
    double cosseno_aproximado(double radianos) const;
    double tangente_aproximada(double radianos) const;

public:
    // Construtor:
    Trigonometria(double graus = 0.0);

    // Método para definir ângulo:
    void definir_angulo(double graus);

    // Métodos para funções trigonométricas:
    double seno() const;
    double cosseno() const;
    double tangente() const;
    double cotangente() const;
    double secante() const;
    double cossecante() const;

    // Sobrecarga de operadores para seno e cosseno de soma/diferença:
    double operator+(const Trigonometria &outro) const; // Seno da soma
    double operator-(const Trigonometria &outro) const; // Seno da diferença
    double operator*(const Trigonometria &outro) const; // Cosseno da soma
    double operator/(const Trigonometria &outro) const; // Cosseno da diferença
};

#endif // TRIG_CLASSE_HPP