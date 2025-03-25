#ifndef MATRIZES_HPP
#define MATRIZES_HPP

#include <iostream>
#include <vector>
#include <fstream>
#include <stdexcept>
#include <cmath>

class Matriz {
private:
    std::vector<std::vector<double>> dados;
    int linhas;
    int colunas;

public:
    // Construtores
    Matriz(int linhas, int colunas);
    Matriz(const std::string& arquivo);

    // Métodos
    void carregarDeArquivo(const std::string& arquivo);
    void exibir() const;
    double determinante() const;
    Matriz transposta() const;
    Matriz inversa() const;
    std::vector<double> autovalores() const;
    std::vector<std::vector<double>> autovetores() const;

    // Sobrecarga de operadores
    Matriz operator+(const Matriz& outra) const;
    Matriz operator-(const Matriz& outra) const;
    Matriz operator*(const Matriz& outra) const;
    friend std::ostream& operator<<(std::ostream& os, const Matriz& matriz);
};

#endif
