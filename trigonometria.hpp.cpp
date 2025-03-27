// CÓDIGO MODIFICADO!
#ifndef TRIGONOMETRIA_HPP
#define TRIGONOMETRIA_HPP

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
    void definirAngulo(double graus);

    // Métodos para funções trigonométricas:
    double seno() const;
    double cosseno() const;
    double tangente() const;

    // Métodos auxiliares:
    double getRadianos() const;
};

#endif // TRIGONOMETRIA_HPP