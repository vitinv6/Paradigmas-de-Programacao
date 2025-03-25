#include "matrizes.hpp"
#include <iostream>
#include <vector>
#include <fstream>
#include <stdexcept>
#include <cmath>
#include <algorithm>
#include <limits>

// Constructors
Matriz::Matriz(int linhas, int colunas) : linhas(linhas), colunas(colunas) {
    if (linhas <= 0 || colunas <= 0) {
        throw std::invalid_argument("Dimensões da matriz devem ser positivas.");
    }
    dados.resize(linhas, std::vector<double>(colunas, 0.0));
}

Matriz::Matriz(const std::string& arquivo) {
    carregarDeArquivo(arquivo);
}

// Basic methods
void Matriz::carregarDeArquivo(const std::string& arquivo) {
    std::ifstream file(arquivo);
    if (!file.is_open()) {
        throw std::runtime_error("Não foi possível abrir o arquivo.");
    }

    file >> linhas >> colunas;
    if (linhas <= 0 || colunas <= 0) {
        throw std::runtime_error("Dimensões da matriz no arquivo devem ser positivas.");
    }

    dados.resize(linhas, std::vector<double>(colunas));

    for (int i = 0; i < linhas; ++i) {
        for (int j = 0; j < colunas; ++j) {
            if (!(file >> dados[i][j])) {
                throw std::runtime_error("Erro ao ler os dados da matriz do arquivo.");
            }
        }
    }
}

void Matriz::exibir() const {
    for (const auto& linha : dados) {
        for (double valor : linha) {
            std::cout << valor << " ";
        }
        std::cout << std::endl;
    }
}

// Matrix operations
Matriz Matriz::transposta() const {
    Matriz resultado(colunas, linhas);
    for (int i = 0; i < linhas; ++i) {
        for (int j = 0; j < colunas; ++j) {
            resultado.dados[j][i] = dados[i][j];
        }
    }
    return resultado;
}

double Matriz::determinante() const {
    if (linhas != colunas) {
        throw std::invalid_argument("A matriz deve ser quadrada para calcular o determinante.");
    }
    
    if (linhas == 1) return dados[0][0];
    if (linhas == 2) return dados[0][0] * dados[1][1] - dados[0][1] * dados[1][0];

    double det = 0.0;
    for (int p = 0; p < colunas; p++) {
        Matriz sub = submatriz(0, p);
        double cofator = dados[0][p] * ((p % 2 == 0) ? 1 : -1);
        det += cofator * sub.determinante();
    }
    return det;
}

Matriz Matriz::inversa() const {
    if (linhas != colunas) {
        throw std::invalid_argument("A matriz deve ser quadrada para ter inversa.");
    }

    double det = determinante();
    if (std::abs(det) < 1e-10) {
        throw std::invalid_argument("Matriz é singular (determinante zero), não tem inversa.");
    }

    Matriz adjunta(linhas, colunas);
    for (int i = 0; i < linhas; i++) {
        for (int j = 0; j < colunas; j++) {
            Matriz sub = submatriz(i, j);
            double cofator = sub.determinante() * (((i + j) % 2) ? -1 : 1);
            adjunta.dados[j][i] = cofator; // Transpose for adjugate
        }
    }

    return adjunta * (1.0 / det);
}

std::vector<double> Matriz::autovalores() const {
    if (linhas != colunas) {
        throw std::invalid_argument("A matriz deve ser quadrada para calcular autovalores.");
    }

    // Power iteration for dominant eigenvalue
    const double tolerance = calcularTolerancia();
    std::vector<double> b_k(colunas, 1.0);
    std::vector<double> b_k1(colunas);
    double eigenvalue = 0.0;

    for (int iter = 0; iter < 1000; iter++) {
        // Matrix-vector multiplication
        for (int i = 0; i < linhas; i++) {
            b_k1[i] = 0.0;
            for (int j = 0; j < colunas; j++) {
                b_k1[i] += dados[i][j] * b_k[j];
            }
        }

        // Normalize
        b_k1 = normalizarVetor(b_k1);

        // Rayleigh quotient for eigenvalue
        double new_eigenvalue = 0.0;
        for (int i = 0; i < linhas; i++) {
            for (int j = 0; j < colunas; j++) {
                new_eigenvalue += b_k1[i] * dados[i][j] * b_k1[j];
            }
        }

        if (std::abs(new_eigenvalue - eigenvalue) < tolerance) {
            break;
        }

        eigenvalue = new_eigenvalue;
        b_k = b_k1;
    }

    return {eigenvalue}; // Returns dominant eigenvalue
}

std::vector<std::vector<double>> Matriz::autovetores() const {
    if (linhas != colunas) {
        throw std::invalid_argument("A matriz deve ser quadrada para calcular autovetores.");
    }

    // Power iteration for dominant eigenvector
    const double tolerance = calcularTolerancia();
    std::vector<double> b_k(colunas, 1.0);
    std::vector<double> b_k1(colunas);

    for (int iter = 0; iter < 1000; iter++) {
        // Matrix-vector multiplication
        for (int i = 0; i < linhas; i++) {
            b_k1[i] = 0.0;
            for (int j = 0; j < colunas; j++) {
                b_k1[i] += dados[i][j] * b_k[j];
            }
        }

        // Normalize
        b_k1 = normalizarVetor(b_k1);

        // Check convergence
        if (isConverged(b_k, b_k1, tolerance)) {
            break;
        }

        b_k = b_k1;
    }

    return {b_k1}; // Returns dominant eigenvector as a matrix
}

// Helper methods
Matriz Matriz::submatriz(int excluir_linha, int excluir_coluna) const {
    Matriz sub(linhas - 1, colunas - 1);
    int sub_i = 0;
    for (int i = 0; i < linhas; i++) {
        if (i == excluir_linha) continue;
        int sub_j = 0;
        for (int j = 0; j < colunas; j++) {
            if (j == excluir_coluna) continue;
            sub.dados[sub_i][sub_j] = dados[i][j];
            sub_j++;
        }
        sub_i++;
    }
    return sub;
}

double Matriz::calcularTolerancia() {
    return 1e-10;
}

bool Matriz::isConverged(const std::vector<double>& prev, const std::vector<double>& curr, double tolerance) {
    double diff = 0.0;
    for (size_t i = 0; i < prev.size(); i++) {
        diff += std::abs(prev[i] - curr[i]);
    }
    return diff < tolerance;
}

std::vector<double> Matriz::normalizarVetor(const std::vector<double>& vetor) {
    double norm = 0.0;
    for (double val : vetor) norm += val * val;
    norm = std::sqrt(norm);

    std::vector<double> normalized = vetor;
    for (double& val : normalized) val /= norm;
    return normalized;
}

// Operator overloads
Matriz Matriz::operator+(const Matriz& outra) const {
    if (linhas != outra.linhas || colunas != outra.colunas) {
        throw std::invalid_argument("As matrizes devem ter as mesmas dimensões.");
    }

    Matriz resultado(linhas, colunas);
    for (int i = 0; i < linhas; ++i) {
        for (int j = 0; j < colunas; ++j) {
            resultado.dados[i][j] = dados[i][j] + outra.dados[i][j];
        }
    }
    return resultado;
}

Matriz Matriz::operator-(const Matriz& outra) const {
    if (linhas != outra.linhas || colunas != outra.colunas) {
        throw std::invalid_argument("As matrizes devem ter as mesmas dimensões.");
    }

    Matriz resultado(linhas, colunas);
    for (int i = 0; i < linhas; ++i) {
        for (int j = 0; j < colunas; ++j) {
            resultado.dados[i][j] = dados[i][j] - outra.dados[i][j];
        }
    }
    return resultado;
}

Matriz Matriz::operator*(const Matriz& outra) const {
    if (colunas != outra.linhas) {
        throw std::invalid_argument("Número de colunas da primeira matriz deve ser igual ao número de linhas da segunda.");
    }

    Matriz resultado(linhas, outra.colunas);
    for (int i = 0; i < linhas; ++i) {
        for (int j = 0; j < outra.colunas; ++j) {
            for (int k = 0; k < colunas; ++k) {
                resultado.dados[i][j] += dados[i][k] * outra.dados[k][j];
            }
        }
    }
    return resultado;
}

Matriz Matriz::operator*(double escalar) const {
    Matriz resultado(linhas, colunas);
    for (int i = 0; i < linhas; ++i) {
        for (int j = 0; j < colunas; ++j) {
            resultado.dados[i][j] = dados[i][j] * escalar;
        }
    }
    return resultado;
}

std::ostream& operator<<(std::ostream& os, const Matriz& matriz) {
    for (const auto& linha : matriz.dados) {
        for (double valor : linha) {
            os << valor << " ";
        }
        os << std::endl;
    }
    return os;
}