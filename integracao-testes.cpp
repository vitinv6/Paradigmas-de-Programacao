#include <iostream>
#include "trig_classe.hpp"
#include "vetores.hpp"
#include "base.hpp"

int main(){
    std::cout << "=== Teste de Trigonometria ===" << std::endl;
    
    Trigonometria t1, t2;
    t1.definir_angulo(45);  // Define o ângulo de 45 graus
    t2.definir_angulo(30);  // Define o ângulo de 30 graus
    
    // Testando as funções trigonométricas
    std::cout << "Seno de 45 graus: " << t1.seno() << std::endl;
    std::cout << "Cosseno de 45 graus: " << t1.cosseno() << std::endl;
    std::cout << "Tangente de 45 graus: " << t1.tangente() << std::endl;
    std::cout << "Cotangente de 45 graus: " << t1.cotangente() << std::endl;
    std::cout << "Secante de 45 graus: " << t1.secante() << std::endl;
    std::cout << "Cossecante de 45 graus: " << t1.cossecante() << std::endl;

    // Testando os operadores sobrecarregados
    std::cout << "Seno da soma (30 + 45 graus): " << t1 + t2 << std::endl;  // Soma dos senos
    std::cout << "Seno da diferença (45 - 30 graus): " << t1 - t2 << std::endl;  // Diferença dos senos
    std::cout << "Cosseno da soma (30 + 45 graus): " << t1 * t2 << std::endl;  // Soma dos cossenos
    std::cout << "Cosseno da diferença (45 - 30 graus): " << t1 / t2 << std::endl;  // Diferença dos cossenos
    
    // Teste de outros ângulos
    t1.definir_angulo(0);
    std::cout << "Seno de 0 graus: " << t1.seno() << std::endl;
    std::cout << "Cosseno de 0 graus: " << t1.cosseno() << std::endl;
    
    t1.definir_angulo(90);
    std::cout << "Seno de 90 graus: " << t1.seno() << std::endl;
    std::cout << "Cosseno de 90 graus: " << t1.cosseno() << std::endl;
    std::cout << "Tangente de 90 graus: " << t1.tangente() << std::endl;  // Testando o valor indefinido

    // Teste da biblioteca vetores.hpp
    std::cout << "\n== Teste de Vetores ===" << std::endl;

    Vetores v1("vetor1.txt");
    Vetores v2("vetor2.txt");

    std::cout << "Norma do vetor 1: " << v1.norma() << std::endl; // Exibir a norma de v1

    // Teste de soma dos vetores
    if (v1.getTamanho() == v2.getTamanho()) {
        double* soma = v1 + v2;
        std::cout << "Soma dos vetores: [";
        for (int i = 0; i < v1.getTamanho(); i++) {
            std::cout << soma[i];
            if (i < v1.getTamanho() - 1) {
                std::cout << ", ";
            }
        }
        std::cout << "]" << std::endl;
        delete[] soma;
    } else {
        std::cerr << "Os vetores têm tamanhos diferentes, não é possível somá-los!" << std::endl;
    }

    // Produto interno
    if (v1.getTamanho() == v2.getTamanho()) {
        double produtoInterno = v1 * v2;
        std::cout << "Produto interno: " << produtoInterno << std::endl;
    } else {
        std::cerr << "Os vetores têm tamanhos diferentes, não é possível calcular o produto interno!" << std::endl;
    }

    // Teste de dependência linear
    if (dependente(v1, v2)) {
        std::cout << "Os vetores são linearmente dependentes." << std::endl;
    } else {
        std::cout << "Os vetores são linearmente independentes." << std::endl;
    }

    // Teste da biblioteca base.hpp
    std::cout << "\n== Teste de Matrizes ===" << std::endl;

    Matriz m1("matriz1.txt");
    Matriz m2("matriz2.txt");

    Matriz soma = m1 + m2;
    std::cout << "Soma das matrizes:" << std::endl;
    soma.exibir();  // Corrigido de imprimir() para exibir()

    std::cout << "Determinante da matriz 1: " << m1.determinante() << std::endl;

    std::cout << "Transposta da matriz 1:" << std::endl;
    m1.transposta().exibir();  // Corrigido de imprimir() para exibir()


    return 0;
}