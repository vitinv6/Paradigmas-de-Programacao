#include "matrizes.hpp"
#include <iostream>

int main() {
    try {
        // Carregar matriz de um arquivo
        Matriz matriz1("matriz1.txt");
        std::cout << "Matriz 1 carregada do arquivo:" << std::endl;
        matriz1.exibir();

        // Testar a transposta
        Matriz transposta = matriz1.transposta();
        std::cout << "\nTransposta da Matriz 1:" << std::endl;
        transposta.exibir();

        // Calcular determinante (apenas para matrizes quadradas)
        if (matriz1.getLinhas() == matriz1.getColunas()) {
            double det = matriz1.determinante();
            std::cout << "\nDeterminante da Matriz 1: " << det << std::endl;
        }

        // Exemplo de operações básicas
        Matriz matriz2("matriz2.txt");
        std::cout << "\nMatriz 2 carregada do arquivo:" << std::endl;
        matriz2.exibir();

        Matriz soma = matriz1 + matriz2;
        std::cout << "\nSoma das Matrizes:" << std::endl;
        soma.exibir();

        Matriz diferenca = matriz1 - matriz2;
        std::cout << "\nDiferença das Matrizes:" << std::endl;
        diferenca.exibir();

        if (matriz1.getColunas() == matriz2.getLinhas()) {
            Matriz produto = matriz1 * matriz2;
            std::cout << "\nProduto das Matrizes:" << std::endl;
            produto.exibir();
        }
    }
    catch (const std::exception& e) {
        std::cerr << "Erro: " << e.what() << std::endl;
    }

    return 0;
}
