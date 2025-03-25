#ifndef MATRIZES_HPP
#define MATRIZES_HPP

#include <iostream>
#include <vector>
#include <fstream>
#include <stdexcept>
#include <cmath>
#include <algorithm>

class Matriz {
private:
    std::vector<std::vector<double>> dados;
    int linhas;
    int colunas;

    // Helper methods for inverse and eigenvalues
    Matriz submatriz(int excluir_linha, int excluir_coluna) const;
    static double calcularTolerancia();
    static bool isConverged(const std::vector<double>& prev, const std::vector<double>& curr, double tolerance);
    static std::vector<double> normalizarVetor(const std::vector<double>& vetor);

public:
    // Construtores
    Matriz(int linhas, int colunas);
    Matriz(const std::string& arquivo);

    // Getters
    int getLinhas() const { return linhas; }
    int getColunas() const { return colunas; }
    const std::vector<std::vector<double>>& getDados() const { return dados; }

    // Métodos básicos
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
    Matriz operator*(double escalar) const;
    friend std::ostream& operator<<(std::ostream& os, const Matriz& matriz);
};

#endif