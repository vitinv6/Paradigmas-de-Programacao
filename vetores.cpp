#include "vetores.hpp"
#include <iostream>
#include <fstream>


// =====================
// Construtor e Destrutor
// =====================
Vetores::Vetores(const char*& arquivo) {
    double* numeros = carregarValores(arquivo);
    if (numeros) {
        setArray(numeros);
        delete[] numeros; // Libera a memória temporária
    } else {
        std::cerr << "Erro ao carregar valores!" << std::endl;
    }
}

Vetores::~Vetores() {
    delete[] array;
}

// =====================
// Métodos de Manipulação
// =====================
void Vetores::setArray(double* numeros) {
    array = new double[tamanho]; 
    for (int i = 0; i < tamanho; i++) {
        array[i] = numeros[i];
    }
}

double* Vetores::getArray() {
    return array;
}

double Vetores::getValor(int indice) const{
    return array[indice];
}

int Vetores::getTamanho() const{
    return tamanho;
}

void Vetores::mostrarVetor() {
    if (array == nullptr || tamanho <= 0) {
        std::cout << "Vetor vazio!" << std::endl;
        return;
    }

    std::cout << "[";
    for (int i = 0; i < tamanho; i++) {
        std::cout << array[i];
        if (i < tamanho - 1) {
            std::cout << ", ";  // Imprime vírgula e espaço
        }
    }
    std::cout << "]" << std::endl;
}

// =====================
// Carregamento de Valores
// =====================
double* Vetores::carregarValores(const char*& arquivo) {
    std::ifstream file(arquivo);
    if (!file.is_open()) {
        std::cerr << "Não foi possível abrir o arquivo: " << arquivo << std::endl;
        return nullptr;
    }

    std::string line;
    int qtdNums = 0; 
    while (std::getline(file, line, ',')) { 
        qtdNums += 1;
    }
    tamanho = qtdNums;

    file.clear();
    file.seekg(0);

    double* numeros = new double[tamanho];
    int i = 0;
    while (std::getline(file, line, ',') && i < tamanho) {
        numeros[i] = std::stod(line);
        i++;
    }

    file.close();
    return numeros;
}

void Vetores::debugCarregarValores(const char*& arquivo) {
    std::ifstream file(arquivo);
    if (!file.is_open()) {
        std::cerr << "Não foi possível abrir o arquivo: " << arquivo << std::endl;
        return;
    }

    std::string line;
    while (std::getline(file, line, ',')) {
        std::cout << "Valor lido: " << line << std::endl; // Exibe cada número lido
    }
}

// =====================
// Operações Matemáticas
// =====================

double raizQuadrada(double N, double precisao = 0.00001) {
    if (N < 0) {
        std::cerr << "Erro: Não é possível calcular a raiz quadrada de um número negativo!" << std::endl;
        return -1;
    }
    
    double x = N;
    double y = 1;
    
    while (x - y > precisao) {
        x = (x + y) / 2;
        y = N / x;
    }
    
    return x;
}

double Vetores::norma() {
    double norma = 0;
    for (int i = 0; i < tamanho; i++) {
        norma += array[i]*array[i];
    }
    norma = raizQuadrada(norma);
    return norma;
}

// =====================
// Funções Globais
// =====================
double* soma(const Vetores& v1, const Vetores& v2) {
    int tamanho = v1.getTamanho();
    double* soma = new double[tamanho];

    if (v1.getTamanho() == v2.getTamanho()) {
        for (int i = 0; i < tamanho; i++) {
            soma[i] = v1.getValor(i) + v2.getValor(i);
        }

        std::cout << "A soma dos vetores é igual a:" << std::endl;
        std::cout << "[";
        for (int i = 0; i < tamanho; i++) {
            printf("%.2f", soma[i]);
            if (i < tamanho - 1) {
                std::cout << ", ";  // Imprime vírgula e espaço
            }
        }
        std::cout << "]" << std::endl;
    }

    return soma;
}

double* diferenca(const Vetores& v1, const Vetores& v2) {
    int tamanho = v1.getTamanho();
    double* diferenca = new double[tamanho];

    if (v1.getTamanho() == v2.getTamanho()) {
        for (int i = 0; i < tamanho; i++) {
            diferenca[i] = v1.getValor(i) - v2.getValor(i);
        }

        std::cout << "A diferenca dos vetores é igual a:" << std::endl;
        std::cout << "[";
        for (int i = 0; i < tamanho; i++) {
            printf("%.2f", diferenca[i]);
            if (i < tamanho - 1) {
                std::cout << ", "; 
            }
        }
        std::cout << "]" << std::endl;
    }

    return diferenca;
}

double prodEsc(const Vetores& v1, const Vetores& v2){
    int tamanho = v1.getTamanho();
    double prodEsc = 0.00;

    if (v1.getTamanho() == v2.getTamanho()) {
        for (int i = 0; i < tamanho; i++) {
            prodEsc += v1.getValor(i) * v2.getValor(i);
        }
    }
    return prodEsc;
}

double* prodVet(const Vetores& v1, const Vetores& v2){
    int tamanho = v1.getTamanho();
    double* prodVet = new double[tamanho];

    if (v1.getTamanho() == v2.getTamanho()) {
        for (int i = 0; i < tamanho; i++) {
            prodVet[i] = v1.getValor(i) * v2.getValor(i);
        }
    }
    std::cout << "[";
    for (int i = 0; i < tamanho; i++) {
            printf("%.2f", prodVet[i]);
            if (i < tamanho - 1) {
                std::cout << ", ";
            }
        }
        std::cout << "]" << std::endl;
    return prodVet;
}

double* operator+(const Vetores& v1, const Vetores& v2) {
    int tamanho = v1.getTamanho();
    double* soma = new double[tamanho];

    if (v1.getTamanho() == v2.getTamanho()) {
        for (int i = 0; i < tamanho; i++) {
            soma[i] = v1.getValor(i) + v2.getValor(i);
        }

    }

    return soma;
}

double* operator-(const Vetores& v1, const Vetores& v2) {
    int tamanho = v1.getTamanho();
    double* diferenca = new double[tamanho];

    if (v1.getTamanho() == v2.getTamanho()) {
        for (int i = 0; i < tamanho; i++) {
            diferenca[i] = v1.getValor(i) - v2.getValor(i);
        }

    }

    return diferenca;
}

double operator*(const Vetores& v1, const Vetores& v2) {
    int tamanho = v1.getTamanho();
    double prodEsc = 0.00;

    if (v1.getTamanho() == v2.getTamanho()) {
        for (int i = 0; i < tamanho; i++) {
            prodEsc += v1.getValor(i) * v2.getValor(i);
        }
    }
    return prodEsc;
}

double* operator^(const Vetores& v1, const Vetores& v2) {
    int tamanho = v1.getTamanho();
    double* prodVet = new double[tamanho];

    if (v1.getTamanho() == v2.getTamanho()) {
        for (int i = 0; i < tamanho; i++) {
            prodVet[i] = v1.getValor(i) * v2.getValor(i);
        }
    }
    return prodVet;
}

bool dependente(const Vetores& v1, const Vetores& v2) {
    if (v1.getTamanho() != v2.getTamanho()) {
        std::cerr << "Os vetores não têm o mesmo tamanho!" << std::endl;
        return false;
    }
    int tamanho = v1.getTamanho();
    double k = v1.getValor(0) / v2.getValor(0); // Inicializa k com base no primeiro elemento
    for (int i = 1; i < tamanho; i++) {
        if (v1.getValor(i) * k != v2.getValor(i)) {
            return false; // Se não for múltiplo, os vetores são independentes
        }
    }
    return true; // Se todos os elementos forem múltiplos, os vetores são dependentes
}