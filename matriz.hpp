#ifndef MATRIZ_HPP
#define MATRIZ_HPP

#include <iostream>
#include <fstream>

class Matriz {
private:
    double** dados;       // Armazena os elementos da matriz
    int linhas;           // Número de linhas
    int colunas;          // Número de colunas

    // Métodos auxiliares
    void alocar_memoria();                     // Aloca memória para a matriz
    void liberar_memoria();                    // Libera memória alocada
    Matriz criar_submatriz(int l, int c) const; // Cria submatriz sem linha l e coluna c
    double calcular_raiz_quadrada(double x) const; // Implementa raiz quadrada

public:
    // Construtores e destrutor
    Matriz(int l, int c);                      // Construtor básico
    Matriz(int l, int c, double valores[]);    // Construtor com valores iniciais
    Matriz(const Matriz& m);                   // Construtor de cópia
    ~Matriz();                                 // Destrutor

    // Operações básicas
    void carregar(const std::string& arquivo); // Carrega matriz de arquivo
    void salvar(const std::string& arquivo) const; // Salva matriz em arquivo
    void imprimir() const;                     // Exibe matriz na tela

    // Operações matemáticas
    Matriz calcular_transposta() const;        // Retorna matriz transposta
    double calcular_determinante() const;      // Calcula determinante
    Matriz calcular_inversa() const;           // Calcula matriz inversa

    // Autovalores e autovetores
    void calcular_autovalor_autovetor(double& autovalor, double* autovetor) const;

    // Sobrecarga de operadores
    Matriz operator+(const Matriz& m) const;   // Soma de matrizes
    Matriz operator-(const Matriz& m) const;   // Subtração de matrizes
    Matriz operator*(const Matriz& m) const;   // Multiplicação de matrizes
    Matriz operator*(double escalar) const;    // Multiplicação por escalar

    // Getters
    int get_linhas() const { return linhas; }
    int get_colunas() const { return colunas; }
    double get_elemento(int i, int j) const;   // Acesso seguro aos elementos

    // Operador de saída
    friend std::ostream& operator<<(std::ostream& os, const Matriz& m);
};

#endif