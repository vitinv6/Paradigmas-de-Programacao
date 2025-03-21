#include "vetores.hpp"
#include <iostream>

int main() {
    // =====================
    // Importação dos dados
    // =====================
    const char* arquivo1 = "dados.txt";
    const char* arquivo2 = "dados2.txt";
    
    // ======================
    // Carregando nos vetores
    // ======================
    Vetores v1(arquivo1);
    Vetores v2(arquivo2);

    // ==========================
    // Mostrar vetores carregados
    // ==========================
    std::cout << "Vetor v1: ";
    v1.mostrarVetor();
    std::cout << "Vetor v2: ";
    v2.mostrarVetor();
    
    // =================
    // Norma dos vetores
    // =================
    double normav1 = v1.norma();
    printf("A norma do vetor v1 é igual a: %.2f", normav1);
    double normav2 =v2.norma();
    printf("A norma do vetor v1 é igual a: %.2f", normav2);

    // ========================
    // Soma dos vetores v1 e v2
    // ========================
    soma(v1, v2);

    // ==================================
    // Diferença entre os vetores v1 e v2
    // ==================================
    diferenca(v1, v2);
    
    // ========================================
    // Produto Escalar entre os vetores v1 e v2
    // ========================================
    //std::cout << "Produto Interno entre os vetores v1 e v2: " << std::fixed << std::setprecision(2) << prodEsc(v1, v2) << std::endl;
    printf("Produto Interno entre os vetores v1 e v2: %.2f", prodEsc(v1, v2));

    // ========================================
    // Produto Vetorial entre os vetores v1 e v2
    // ========================================
    std::cout << "Produto Externo entre os vetores v1 e v2: ";
    prodVet(v1, v2);

    // ========================
    // Sobrecarga de Operadores
    // ========================
    double* soma = v1 + v2;
    int tamanho = v1.getTamanho();
    std::cout << "A soma dos vetores é igual a:" << std::endl;
        std::cout << "[";
        for (int i = 0; i < tamanho; i++) {
            printf("%.2f", soma[i]);
            if (i < tamanho - 1) {
                std::cout << ", ";  // Imprime vírgula e espaço
            }
        }
        std::cout << "]" << std::endl;
        
    double* diferenca = v1 - v2;
    std::cout << "A diferença entre os vetores é igual a:" << std::endl;
        std::cout << "[";
        for (int i = 0; i < tamanho; i++) {
            printf("%.2f", diferenca[i]);
            if (i < tamanho - 1) {
                std::cout << ", ";  // Imprime vírgula e espaço
            }
        }
        std::cout << "]" << std::endl;
        
    double prodEsc = v1 * v2;
    std::cout << "O produto interno entre os vetores é igual a: ";
    printf("%.2f", prodEsc);
    std::cout<<std::endl;
      
    double* prodVet = v1 ^ v2;
    std::cout << "O produto externo entre os vetores é igual a:" << std::endl;
        std::cout << "[";
        for (int i = 0; i < tamanho; i++) {
            printf("%.2f", prodVet[i]);
            if (i < tamanho - 1) {
                std::cout << ", ";  // Imprime vírgula e espaço
            }
        }
        std::cout << "]" << std::endl;  
        
    if(dependente(v1,v2)){
        std::cout<<"Os vetores são linearmente dependentes";
    }else{
        std::cout<<"Os vetores não são linearmente dependentes";
    }
    
    return 0;
}