#include "trigonometria.hpp"
#include "vetores.hpp"
#include "matrizes.hpp"
#include <iostream>

int main() {
    std::cout << "=== Teste de Trigonometria ===\n" << std::endl;

    Trigonometria t1, t2;
    t1.definir_angulo(45);
    t2.definir_angulo(30);

    // --------------- Testando as funções trigonométricas ---------------------
    std::cout << "Seno de 45 graus: " << t1.seno() << std::endl;
    std::cout << "Cosseno de 45 graus: " << t1.cosseno() << std::endl;
    std::cout << "Tangente de 45 graus: " << t1.tangente() << std::endl;
    std::cout << "Cotangente de 45 graus: " << t1.cotangente() << std::endl;
    std::cout << "Secante de 45 graus: " << t1.secante() << std::endl;
    std::cout << "Cossecante de 45 graus: " << t1.cossecante() << std::endl;

    // Testando os operadores sobrecarregados
    std::cout << "Seno da soma (30 + 45 graus): " << t1 + t2 << std::endl;
    std::cout << "Seno da diferença (45 - 30 graus): " << t1 - t2 << std::endl;
    std::cout << "Cosseno da soma (30 + 45 graus): " << t1 * t2 << std::endl;
    std::cout << "Cosseno da diferença (45 - 30 graus): " << t1 / t2 << std::endl;

    // Teste de outros ângulos
    t1.definir_angulo(0);
    std::cout << "Seno de 0 graus: " << t1.seno() << std::endl;
    std::cout << "Cosseno de 0 graus: " << t1.cosseno() << std::endl;

    t1.definir_angulo(90);
    std::cout << "Seno de 90 graus: " << t1.seno() << std::endl;
    std::cout << "Cosseno de 90 graus: " << t1.cosseno() << std::endl;
    std::cout << "Tangente de 90 graus: " << t1.tangente() << std::endl;

    // --------------- Teste da biblioteca vetores.hpp ----------------------
    std::cout << "\n== Teste de Vetores ===\n" << std::endl;

 
    // Importação dos dados
    const char* arquivo1 = "dados.txt";
    const char* arquivo2 = "dados2.txt";

    // Carregando nos vetores
    Vetores v1(arquivo1);
    Vetores v2(arquivo2);

    // Mostrar vetores carregados
    std::cout << "Vetor v1: ";
    v1.mostrarVetor();
    std::cout << "Vetor v2: ";
    v2.mostrarVetor();

    // Norma dos vetores
    double normav1 = v1.norma();
    printf("A norma do vetor v1 é igual a: %.2f", normav1);
    double normav2 =v2.norma();
    printf("A norma do vetor v1 é igual a: %.2f", normav2);

    // Soma dos vetores v1 e v2
    soma(v1, v2);

    // Diferença entre os vetores v1 e v2
    diferenca(v1, v2);

    // Produto Escalar entre os vetores v1 e v2
    //std::cout << "Produto Interno entre os vetores v1 e v2: " << std::fixed << std::setprecision(2) << prodEsc(v1, v2) << std::endl;
    printf("Produto Interno entre os vetores v1 e v2: %.2f", prodEsc(v1, v2));

    // Produto Vetorial entre os vetores v1 e v2
    std::cout << "Produto Externo entre os vetores v1 e v2: ";
    prodVet(v1, v2);

    // Sobrecarga de Operadores
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

    // Dependência entre vetores
    if(dependente(v1,v2)){
        std::cout<<"Os vetores são linearmente dependentes";
    }else{
        std::cout<<"Os vetores não são linearmente dependentes"<<std::endl;
    }

    // Distância entre vetores
    printf("A distância entre os vetores é: %.2f", distancia(v1, v2));

    // --------------------- Teste da biblioteca matrizes.hpp -------------------------
    std::cout << "\n== Teste de Matrizes ===\n" << std::endl;

    // Cria matrizes vazias
    Matriz A(3, 3);
    Matriz B(3, 3);
    
    // Carrega matrizes de arquivos
    A.carregar("matriza.txt");
    B.carregar("matrizb.txt");
    
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