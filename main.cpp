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

            // Testar inversa
            try {
                Matriz inversa = matriz1.inversa();
                std::cout << "\nInversa da Matriz 1:" << std::endl;
                inversa.exibir();

                // Verificar se A * A^-1 = I
                Matriz identidade = matriz1 * inversa;
                std::cout << "\nMatriz 1 * Inversa (deve ser identidade):" << std::endl;
                identidade.exibir();
            } catch (const std::exception& e) {
                std::cerr << "\nErro ao calcular inversa: " << e.what() << std::endl;
            }

            // Testar autovalores e autovetores
            try {
                std::vector<double> autovalores = matriz1.autovalores();
                std::cout << "\nAutovalor dominante: " << autovalores[0] << std::endl;

                std::vector<std::vector<double>> autovetores = matriz1.autovetores();
                std::cout << "Autovetor correspondente:" << std::endl;
                for (double val : autovetores[0]) {
                    std::cout << val << " ";
                }
                std::cout << std::endl;
            } catch (const std::exception& e) {
                std::cerr << "\nErro ao calcular autovalores/autovetores: " << e.what() << std::endl;
            }
        }

        // Restante do seu código original...
    }
    catch (const std::exception& e) {
        std::cerr << "Erro: " << e.what() << std::endl;
    }

    return 0;
}