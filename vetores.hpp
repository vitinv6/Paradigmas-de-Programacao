#ifndef VETORES_HPP
#define VETORES_HPP

class Vetores{
    private:
        double* array;
        int tamanho;

    public:
        Vetores(const char* arquivo);
        Vetores(const double* arr, int tamanho);
        ~Vetores();
        void setArray(const double* numeros);
        void setArray(const double* numeros, int tamanho);
        double* getArray();
        double getValor(int indice) const;
        int getTamanho() const;
        void mostrarVetor() const;

        double* carregarValores(const char*& arquivo);
        double norma();
        void debugCarregarValores(const char*& arquivo);
        friend Vetores operator+(const Vetores& v1, const Vetores& v2);
        friend Vetores operator-(const Vetores& v1, const Vetores& v2);
        friend double operator*(const Vetores& v1, const Vetores& v2);
        friend Vetores operator^(const Vetores& v1, const Vetores& v2);
};

Vetores soma(const Vetores& v1, const Vetores& v2);
Vetores diferenca(const Vetores& v1, const Vetores& v2);
double prodEsc(const Vetores& v1, const Vetores& v2);
Vetores prodVet(const Vetores& v1, const Vetores& v2);
double raizQuadrada(double N, double precisao);
bool dependente(const Vetores& v1, const Vetores& v2);
double distancia(const Vetores& v1, const Vetores& v2);

#endif