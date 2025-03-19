#include <iostream>
#include "trigonometria.hpp"
#include "vetores.hpp"
#include "matrizes.hpp"

int main(){
    //Teste da biblioteca trigonometria.hpp
    std::cout << "=== Teste de Trigonometria" << std::endl;
    Trigonometria t1, t2;
    t1.definirAngulo(45);
    t2.definirAngulo(30);
    std::cout << "Seno de 45 graus: " << t1.seno() << std::endl;
    std::cout << "Cosseno de 45 graus: " << t1.cosseno() << std::endl;
    std::cout << "Seno da soma (30 + 45): " << t1.senoSoma(t2) << std::endl;
    std::cout << "Cosseno da soma (30 + 45): " << t1.cossenoSoma(t2) << std::endl;

    //Teste da biblioteca vetores.hpp
    std::cout << "\n== Teste de Vetores ===" << std::endl;
    Vetor v1, v2;
    v1.carregarValores("vetor1.txt");
    v2.carregarValores("vetor2.txt");
    std::cout << "Norma do vetor 1: " << v1.norma() << std::endl;
    std::cout << "Soma dos vetores: " << (v1 + v2) << std::endl;
    std::cout << "Produto interno: " << v1.produtoInterno(v2) << std::endl;

    //Teste da biblioteca matrizes.hpp
    std::cout << "\n== Teste de Matrizes ===" << std::endl;
    Matriz m1, m2;
    m1.carregarValores("matriz1.txt");
    m2.carregarValores("matriz2.txt");
    Matriz soma = m1 + m2;
    std::cout << "Soma das matrizes:" << std::endl;
    soma.imprimir();
    std::cout << "Determinante da matriz 1: " << m1.determinante() << std::endl;
    std::cout << "Transposta da matriz 1:" << std::endl;
    m1.transposta().imprimir();

    return 0;
}