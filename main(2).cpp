// MAIN.CPP
#include "matriz.hpp"
#include <iostream>

int main() {
    // Cria matrizes vazias
    Matriz A(3, 3);
    Matriz B(3, 3);
    
    // Carrega matrizes de arquivos
    A.carregar("matrizA.txt");
    B.carregar("matrizB.txt");
    
    std::cout << "Matriz A:\n" << A;
    std::cout << "\nMatriz B:\n" << B;
    
    // Testa transposta
    Matriz At = A.calcular_transposta();
    std::cout << "\nTransposta de A:\n" << At;
    
    // Testa determinante
    std::cout << "\nDeterminante de A: " << A.calcular_determinante() << "\n";
    
    // Testa inversa (se possível)
    if (A.calcular_determinante() != 0) {
        Matriz invA = A.calcular_inversa();
        std::cout << "\nInversa de A:\n" << invA;
    } else {
        std::cout << "\nA matriz A não possui inversa (determinante zero).\n";
    }
    
    // Testa autovalor/autovetor
    double autovalor;
    double autovetor[3];
    A.calcular_autovalor_autovetor(autovalor, autovetor);
    std::cout << "\nAutovalor dominante de A: " << autovalor << "\n";
    std::cout << "Autovetor correspondente:\n";
    for (int i = 0; i < 3; ++i) {
        std::cout << autovetor[i] << "\n";
    }
    
    // Testa operações
    Matriz C = A + B;
    std::cout << "\nA + B:\n" << C;
    
    Matriz D = A * 2.5;
    std::cout << "\nA * 2.5:\n" << D;
    
    Matriz E = A * B;
    std::cout << "\nA * B:\n" << E;
    
    // Salva matriz resultante
    C.salvar("matriz_resultante.txt");
    std::cout << "\nMatriz resultante salva em 'matriz_resultante.txt'\n";
    
    return 0;
}