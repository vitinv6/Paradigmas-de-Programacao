#ifndef VETORES_HPP
#define VETORES_HPP

class Vetores{
    private:
        double* array;
        int tamanho;

    public:
        explicit Vetores(const char*& arquivo);
        ~Vetores();
        void setArray(double* numeros);
        double* getArray();
        double getValor(int indice) const;
        int getTamanho() const;
        void mostrarVetor();

        double* carregarValores(const char*& arquivo);
        double norma();
        void debugCarregarValores(const char*& arquivo);
        friend double* operator+(const Vetores& v1, const Vetores& v2);
        friend double* operator-(const Vetores& v1, const Vetores& v2);
        friend double operator*(const Vetores& v1, const Vetores& v2);
        friend double* operator^(const Vetores& v1, const Vetores& v2);
};

double* soma(const Vetores& v1, const Vetores& v2);
double* diferenca(const Vetores& v1, const Vetores& v2);
double prodEsc(const Vetores& v1, const Vetores& v2);
double* prodVet(const Vetores& v1, const Vetores& v2);
double raizQuadrada(double N, double precisao);
bool dependente(const Vetores& v1, const Vetores& v2);
double distancia(const Vetores& v1, const Vetores& v2);

#endif