#include "matrizes.hpp"
#include <fstream>

// Implementação dos métodos privados
void Matriz::alocar_memoria() {
    dados = new double*[linhas];
    for (int i = 0; i < linhas; ++i) {
        dados[i] = new double[colunas](); // Inicializa com zeros
    }
}

void Matriz::liberar_memoria() {
    for (int i = 0; i < linhas; ++i) {
        delete[] dados[i];
    }
    delete[] dados;
}

Matriz Matriz::criar_submatriz(int linha_remover, int coluna_remover) const {
    Matriz sub(linhas-1, colunas-1);
    int sub_i = 0;
    for (int i = 0; i < linhas; ++i) {
        if (i == linha_remover) continue;
        int sub_j = 0;
        for (int j = 0; j < colunas; ++j) {
            if (j == coluna_remover) continue;
            sub.dados[sub_i][sub_j] = dados[i][j];
            ++sub_j;
        }
        ++sub_i;
    }
    return sub;
}

double Matriz::calcular_raiz_quadrada(double x) const {
    if (x == 0) return 0;
    double raiz = x;
    for (int i = 0; i < 20; ++i) { // Método de Newton
        raiz = 0.5 * (raiz + x/raiz);
    }
    return raiz;
}

// Implementação dos construtores e destrutor
Matriz::Matriz(int l, int c) : linhas(l), colunas(c) {
    if (l <= 0 || c <= 0) {
        std::cerr << "Dimensões inválidas. Definindo para 1x1.\n";
        linhas = colunas = 1;
    }
    alocar_memoria();
}

Matriz::Matriz(int l, int c, double valores[]) : linhas(l), colunas(c) {
    if (l <= 0 || c <= 0) {
        std::cerr << "Dimensões inválidas. Definindo para 1x1.\n";
        linhas = colunas = 1;
    }
    alocar_memoria();
    for (int i = 0; i < linhas; ++i) {
        for (int j = 0; j < colunas; ++j) {
            dados[i][j] = valores[i*colunas + j];
        }
    }
}

Matriz::Matriz(const Matriz& m) : linhas(m.linhas), colunas(m.colunas) {
    alocar_memoria();
    for (int i = 0; i < linhas; ++i) {
        for (int j = 0; j < colunas; ++j) {
            dados[i][j] = m.dados[i][j];
        }
    }
}

Matriz::~Matriz() {
    liberar_memoria();
}

// Implementação dos métodos públicos
void Matriz::carregar(const std::string& arquivo) {
    std::ifstream file(arquivo);
    if (!file) {
        std::cerr << "Erro ao abrir arquivo.\n";
        return;
    }

    int l, c;
    file >> l >> c;
    if (l != linhas || c != colunas) {
        liberar_memoria();
        linhas = l;
        colunas = c;
        alocar_memoria();
    }

    for (int i = 0; i < linhas; ++i) {
        for (int j = 0; j < colunas; ++j) {
            file >> dados[i][j];
        }
    }
}

void Matriz::salvar(const std::string& arquivo) const {
    std::ofstream file(arquivo);
    if (!file) {
        std::cerr << "Erro ao criar arquivo.\n";
        return;
    }

    file << linhas << " " << colunas << "\n";
    for (int i = 0; i < linhas; ++i) {
        for (int j = 0; j < colunas; ++j) {
            file << dados[i][j] << " ";
        }
        file << "\n";
    }
}

void Matriz::imprimir() const {
    for (int i = 0; i < linhas; ++i) {
        for (int j = 0; j < colunas; ++j) {
            std::cout << dados[i][j] << "\t";
        }
        std::cout << "\n";
    }
}

Matriz Matriz::calcular_transposta() const {
    Matriz transposta(colunas, linhas);
    for (int i = 0; i < linhas; ++i) {
        for (int j = 0; j < colunas; ++j) {
            transposta.dados[j][i] = dados[i][j];
        }
    }
    return transposta;
}

double Matriz::calcular_determinante() const {
    if (linhas != colunas) {
        std::cerr << "Matriz não é quadrada.\n";
        return 0;
    }

    if (linhas == 1) return dados[0][0];
    if (linhas == 2) return dados[0][0]*dados[1][1] - dados[0][1]*dados[1][0];

    double det = 0;
    for (int j = 0; j < colunas; ++j) {
        Matriz sub = criar_submatriz(0, j);
        double cofator = (j % 2 == 0 ? 1 : -1) * dados[0][j];
        det += cofator * sub.calcular_determinante();
    }
    return det;
}

Matriz Matriz::calcular_inversa() const {
    double det = calcular_determinante();
    if (det == 0) {
        std::cerr << "Matriz singular, não possui inversa.\n";
        return Matriz(0, 0);
    }

    Matriz adjunta(linhas, colunas);
    for (int i = 0; i < linhas; ++i) {
        for (int j = 0; j < colunas; ++j) {
            Matriz sub = criar_submatriz(i, j);
            double cofator = ((i+j) % 2 == 0 ? 1 : -1) * sub.calcular_determinante();
            adjunta.dados[j][i] = cofator; // Transposta dos cofatores
        }
    }

    return adjunta * (1.0/det);
}

void Matriz::calcular_autovalor_autovetor(double& autovalor, double* autovetor) const {
    const int max_iter = 100;
    const double tol = 1e-10;
    
    // Inicializa vetor com valores 1
    for (int i = 0; i < linhas; ++i) {
        autovetor[i] = 1.0;
    }

    for (int iter = 0; iter < max_iter; ++iter) {
        double novo_autovetor[linhas] = {0};
        double norma = 0;
        
        // Multiplica matriz por vetor
        for (int i = 0; i < linhas; ++i) {
            for (int j = 0; j < colunas; ++j) {
                novo_autovetor[i] += dados[i][j] * autovetor[j];
            }
            norma += novo_autovetor[i] * novo_autovetor[i];
        }
        
        // Normaliza
        norma = calcular_raiz_quadrada(norma);
        for (int i = 0; i < linhas; ++i) {
            novo_autovetor[i] /= norma;
        }
        
        // Verifica convergência
        double diff = 0;
        for (int i = 0; i < linhas; ++i) {
            diff += std::abs(novo_autovetor[i] - autovetor[i]);
        }
        
        // Atualiza autovetor
        for (int i = 0; i < linhas; ++i) {
            autovetor[i] = novo_autovetor[i];
        }
        
        if (diff < tol) break;
    }
    
    // Calcula autovalor (quociente de Rayleigh)
    autovalor = 0;
    double temp[linhas] = {0};
    for (int i = 0; i < linhas; ++i) {
        for (int j = 0; j < colunas; ++j) {
            temp[i] += dados[i][j] * autovetor[j];
        }
        autovalor += autovetor[i] * temp[i];
    }
}

// Implementação dos operadores
Matriz Matriz::operator+(const Matriz& m) const {
    if (linhas != m.linhas || colunas != m.colunas) {
        std::cerr << "Dimensões incompatíveis para soma.\n";
        return Matriz(0, 0);
    }

    Matriz resultado(linhas, colunas);
    for (int i = 0; i < linhas; ++i) {
        for (int j = 0; j < colunas; ++j) {
            resultado.dados[i][j] = dados[i][j] + m.dados[i][j];
        }
    }
    return resultado;
}

Matriz Matriz::operator-(const Matriz& m) const {
    if (linhas != m.linhas || colunas != m.colunas) {
        std::cerr << "Dimensões incompatíveis para subtração.\n";
        return Matriz(0, 0);
    }

    Matriz resultado(linhas, colunas);
    for (int i = 0; i < linhas; ++i) {
        for (int j = 0; j < colunas; ++j) {
            resultado.dados[i][j] = dados[i][j] - m.dados[i][j];
        }
    }
    return resultado;
}

Matriz Matriz::operator*(const Matriz& m) const {
    if (colunas != m.linhas) {
        std::cerr << "Dimensões incompatíveis para multiplicação.\n";
        return Matriz(0, 0);
    }

    Matriz resultado(linhas, m.colunas);
    for (int i = 0; i < linhas; ++i) {
        for (int j = 0; j < m.colunas; ++j) {
            for (int k = 0; k < colunas; ++k) {
                resultado.dados[i][j] += dados[i][k] * m.dados[k][j];
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

double Matriz::get_elemento(int i, int j) const {
    if (i < 0 || i >= linhas || j < 0 || j >= colunas) {
        std::cerr << "Índices inválidos.\n";
        return 0;
    }
    return dados[i][j];
}

std::ostream& operator<<(std::ostream& os, const Matriz& m) {
    for (int i = 0; i < m.linhas; ++i) {
        for (int j = 0; j < m.colunas; ++j) {
            os << m.dados[i][j] << "\t";
        }
        os << "\n";
    }
    return os;
}