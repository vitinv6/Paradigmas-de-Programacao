#include "base.hpp"
#include <iostream>
#include <vector>
#include <fstream>
#include <stdexcept>
#include <cmath>
#include <algorithm>

// Construtores
Matriz::Matriz(int linhas, int colunas) : linhas(linhas), colunas(colunas) {
    dados.resize(linhas, std::vector<double>(colunas, 0.0));
}

Matriz::Matriz(const std::string& arquivo) {
    carregarDeArquivo(arquivo);
}

// Métodos
void Matriz::carregarDeArquivo(const std::string& arquivo) {
    std::ifstream file(arquivo);
    if (!file.is_open()) {
        throw std::runtime_error("Não foi possível abrir o arquivo.");
    }

    file >> linhas >> colunas;
    dados.resize(linhas, std::vector<double>(colunas));

    for (int i = 0; i < linhas; ++i) {
        for (int j = 0; j < colunas; ++j) {
            file >> dados[i][j];
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

Matriz Matriz::transposta() const {
    Matriz resultado(colunas, linhas);
    for (int i = 0; i < linhas; ++i) {
        for (int j = 0; j < colunas; ++j) {
            resultado.dados[j][i] = dados[i][j];
        }
    }
    return resultado;
}

// Determinante (Método de Laplace - Recursivo)
double Matriz::determinante() const {
    if (linhas != colunas) {
        throw std::invalid_argument("A matriz deve ser quadrada para calcular o determinante.");
    }
    
    if (linhas == 1) return dados[0][0];
    if (linhas == 2) return dados[0][0] * dados[1][1] - dados[0][1] * dados[1][0];

    double det = 0.0;
    for (int p = 0; p < colunas; p++) {
        Matriz submatriz(linhas - 1, colunas - 1);
        for (int i = 1; i < linhas; i++) {
            int sub_j = 0;
            for (int j = 0; j < colunas; j++) {
                if (j == p) continue;
                submatriz.dados[i - 1][sub_j++] = dados[i][j];
            }
        }
        det += (p % 2 == 0 ? 1 : -1) * dados[0][p] * submatriz.determinante();
    }
    return det;
}

// Sobrecarga de operadores
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

std::ostream& operator<<(std::ostream& os, const Matriz& matriz) {
    for (const auto& linha : matriz.dados) {
        for (double valor : linha) {
            os << valor << " ";
        }
        os << std::endl;
    }
    return os;
}
