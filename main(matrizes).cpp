#include <iostream>
#include <vector>
#include <fstream>
#include <stdexcept>
#include <cmath>
#include <algorithm>

// Classe base Vetor
class Vetor {
protected:
    std::vector<double> elementos;
    int dimensao;

public:
    Vetor(int dim) : dimensao(dim), elementos(dim, 0.0) {}
    Vetor(int dim, const std::vector<double>& vals) : dimensao(dim), elementos(vals) {
        if (vals.size() != dim) {
            throw std::invalid_argument("Dimensão não corresponde aos valores fornecidos");
        }
    }
    
    virtual ~Vetor() = default;
    
    int getDimensao() const { return dimensao; }
    double& operator[](int i) { return elementos[i]; }
    const double& operator[](int i) const { return elementos[i]; }
    
    virtual void exibir() const {
        for (double elem : elementos) {
            std::cout << elem << " ";
        }
        std::cout << std::endl;
    }
};

// Classe Matriz derivada de Vetor
class Matriz : public Vetor {
private:
    int linhas;
    int colunas;
    std::vector<std::vector<double>> dados;

    // Métodos auxiliares
    Matriz submatriz(int excluir_linha, int excluir_coluna) const;
    static double calcularTolerancia();
    static bool isConverged(const std::vector<double>& prev, const std::vector<double>& curr, double tolerance);
    static std::vector<double> normalizarVetor(const std::vector<double>& vetor);
    void decomposicaoLU(Matriz& L, Matriz& U) const;

public:
    // Construtores
    Matriz(int linhas, int colunas);
    Matriz(int linhas, int colunas, const std::vector<std::vector<double>>& valores);
    Matriz(const std::string& arquivo);
    
    // Métodos da interface
    void carregarDeArquivo(const std::string& arquivo);
    void exibir() const override;
    
    // Operações básicas
    Matriz transposta() const;
    double determinante() const;
    Matriz inversa() const;
    
    // Autovalores e autovetores
    std::vector<double> autovalores(int max_iter = 1000) const;
    std::vector<Vetor> autovetores(int max_iter = 1000) const;
    
    // Sobrecarga de operadores
    Matriz operator+(const Matriz& outra) const;
    Matriz operator-(const Matriz& outra) const;
    Matriz operator*(const Matriz& outra) const;
    Matriz operator*(double escalar) const;
    
    // Getters
    int getLinhas() const { return linhas; }
    int getColunas() const { return colunas; }
    const std::vector<std::vector<double>>& getDados() const { return dados; }
    
    friend std::ostream& operator<<(std::ostream& os, const Matriz& matriz);
};

// Implementação dos construtores
Matriz::Matriz(int linhas, int colunas) 
    : Vetor(linhas * colunas), linhas(linhas), colunas(colunas), 
      dados(linhas, std::vector<double>(colunas, 0.0)) {
    if (linhas <= 0 || colunas <= 0) {
        throw std::invalid_argument("Dimensões da matriz devem ser positivas.");
    }
}

Matriz::Matriz(int linhas, int colunas, const std::vector<std::vector<double>>& valores)
    : Vetor(linhas * colunas), linhas(linhas), colunas(colunas), dados(valores) {
    if (linhas <= 0 || colunas <= 0) {
        throw std::invalid_argument("Dimensões da matriz devem ser positivas.");
    }
    if (valores.size() != linhas || (linhas > 0 && valores[0].size() != colunas)) {
        throw std::invalid_argument("Dimensões não correspondem aos dados fornecidos.");
    }
    
    // Preenche o vetor da classe base
    elementos.clear();
    for (const auto& linha : dados) {
        for (double val : linha) {
            elementos.push_back(val);
        }
    }
}

Matriz::Matriz(const std::string& arquivo) : Vetor(0) {
    carregarDeArquivo(arquivo);
}

// Implementação dos métodos
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
    elementos.resize(linhas * colunas);

    for (int i = 0; i < linhas; ++i) {
        for (int j = 0; j < colunas; ++j) {
            if (!(file >> dados[i][j])) {
                throw std::runtime_error("Erro ao ler os dados da matriz do arquivo.");
            }
            elementos[i * colunas + j] = dados[i][j];
        }
    }
}

void Matriz::exibir() const {
    for (const auto& linha : dados) {
        for (double valor : linha) {
            std::cout << valor << "\t";
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

double Matriz::determinante() const {
    if (linhas != colunas) {
        throw std::invalid_argument("A matriz deve ser quadrada para calcular o determinante.");
    }
    
    if (linhas == 1) return dados[0][0];
    if (linhas == 2) return dados[0][0] * dados[1][1] - dados[0][1] * dados[1][0];

    double det = 0.0;
    for (int p = 0; p < colunas; p++) {
        Matriz sub = submatriz(0, p);
        det += ((p % 2 == 0) ? 1 : -1) * dados[0][p] * sub.determinante();
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
            adjunta.dados[j][i] = cofator;
        }
    }

    return adjunta * (1.0 / det);
}

std::vector<double> Matriz::autovalores(int max_iter) const {
    if (linhas != colunas) {
        throw std::invalid_argument("A matriz deve ser quadrada para calcular autovalores.");
    }

    const double tolerance = calcularTolerancia();
    std::vector<double> b_k(colunas, 1.0);
    double eigenvalue = 0.0;

    for (int iter = 0; iter < max_iter; iter++) {
        std::vector<double> b_k1(colunas, 0.0);
        
        for (int i = 0; i < linhas; i++) {
            for (int j = 0; j < colunas; j++) {
                b_k1[i] += dados[i][j] * b_k[j];
            }
        }

        b_k1 = normalizarVetor(b_k1);

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

    return {eigenvalue};
}

std::vector<Vetor> Matriz::autovetores(int max_iter) const {
    if (linhas != colunas) {
        throw std::invalid_argument("A matriz deve ser quadrada para calcular autovetores.");
    }

    const double tolerance = calcularTolerancia();
    std::vector<double> b_k(colunas, 1.0);

    for (int iter = 0; iter < max_iter; iter++) {
        std::vector<double> b_k1(colunas, 0.0);
        
        for (int i = 0; i < linhas; i++) {
            for (int j = 0; j < colunas; j++) {
                b_k1[i] += dados[i][j] * b_k[j];
            }
        }

        b_k1 = normalizarVetor(b_k1);

        if (isConverged(b_k, b_k1, tolerance)) {
            break;
        }

        b_k = b_k1;
    }

    return {Vetor(colunas, b_k)};
}

// Implementação dos operadores
Matriz Matriz::operator+(const Matriz& outra) const {
    if (linhas != outra.linhas || colunas != outra.colunas) {
        throw std::invalid_argument("Dimensões incompatíveis para soma.");
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
        throw std::invalid_argument("Dimensões incompatíveis para subtração.");
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
        throw std::invalid_argument("Dimensões incompatíveis para multiplicação.");
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
            os << valor << "\t";
        }
        os << "\n";
    }
    return os;
}

// Implementação dos métodos auxiliares
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

void Matriz::decomposicaoLU(Matriz& L, Matriz& U) const {
    if (linhas != colunas) {
        throw std::invalid_argument("A matriz deve ser quadrada para decomposição LU.");
    }

    for (int i = 0; i < linhas; i++) {
        for (int k = i; k < colunas; k++) {
            double sum = 0.0;
            for (int j = 0; j < i; j++) {
                sum += L.dados[i][j] * U.dados[j][k];
            }
            U.dados[i][k] = dados[i][k] - sum;
        }

        for (int k = i; k < linhas; k++) {
            if (i == k) {
                L.dados[i][i] = 1.0;
            } else {
                double sum = 0.0;
                for (int j = 0; j < i; j++) {
                    sum += L.dados[k][j] * U.dados[j][i];
                }
                L.dados[k][i] = (dados[k][i] - sum) / U.dados[i][i];
            }
        }
    }
}

// Função principal para teste
int main() {
    try {
        // Exemplo de uso com o novo construtor
        Matriz A(2, 2, {{4, 3}, {6, 3}});
        Matriz B(2, 2, {{1, 0}, {0, 1}});
        
        std::cout << "Matriz A:\n" << A;
        std::cout << "\nMatriz B (Identidade):\n" << B;
        
        Matriz C = A + B;
        std::cout << "\nA + B:\n" << C;
        
        Matriz D = A * B;
        std::cout << "\nA * B:\n" << D;
        
        Matriz At = A.transposta();
        std::cout << "\nTransposta de A:\n" << At;
        
        std::cout << "\nDeterminante de A: " << A.determinante() << "\n";
        
        Matriz invA = A.inversa();
        std::cout << "\nInversa de A:\n" << invA;
        
        auto autovalores = A.autovalores();
        std::cout << "\nAutovalor dominante de A: " << autovalores[0] << "\n";
        
        auto autovetores = A.autovetores();
        std::cout << "Autovetor correspondente:\n";
        autovetores[0].exibir();
        
    } catch (const std::exception& e) {
        std::cerr << "Erro: " << e.what() << std::endl;
    }

    return 0;
}
