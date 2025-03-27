# Projeto - Paradigmas de Programação

Este projeto envolve a manipulação de vetores e matrizes, além de operações trigonométricas. O código contém três classes principais: `Trigonometria`, `Vetores` e `Matrizes`, que são utilizadas para realizar cálculos como soma, subtração, multiplicação, produto escalar, e outras operações matemáticas.

## **Classes**

### 1. **Trigonometria**
   A classe `Trigonometria` é responsável pela conversão de ângulos de graus para radianos e fornece métodos para calcular o seno, cosseno e tangente de um ângulo. Ela garante a precisão dos cálculos, comparando o valor calculado com a função da biblioteca padrão `cmath`.

   - **Métodos principais**:
     - `definirAngulo`: Define o ângulo em graus ou radianos.
     - `cos`, `sin`, `tan`: Calcula o cosseno, seno e tangente do ângulo.
     - `getRadianos`: Converte o ângulo de graus para radianos.

### 2. **Vetores**
   A classe `Vetores` permite a manipulação de vetores em um espaço tridimensional. Ela oferece operações como soma, subtração, produto escalar, produto vetorial, cálculo da norma, e a distância entre dois vetores.

   - **Métodos principais**:
     - `soma`, `diferenca`: Soma e subtração de vetores.
     - `prodEsc`: Calcula o produto escalar entre dois vetores.
     - `prodVet`: Calcula o produto vetorial.
     - `norma`: Retorna a norma (magnitude) do vetor.
     - `distancia`: Calcula a distância entre dois vetores.

### 3. **Matrizes**
   A classe `Matrizes` permite a manipulação de matrizes quadradas e operações como soma, subtração, multiplicação, transposição, inversão e cálculo de determinante.

   - **Métodos principais**:
     - `soma`, `diferenca`: Soma e subtração de matrizes.
     - `prodEsc`: Multiplicação de matrizes.
     - `inversa`: Retorna a inversa da matriz.
     - `transposta`: Retorna a matriz transposta.
     - `determinante`: Calcula o determinante da matriz.

## **Membros do Projeto**

| Nome                   | Matrícula  |
|------------------------|------------|
| **Bryan Belum**         | 2301194    |
| **Guilherme Marinho**   | 2300543    |
| **Jhoysell Chavarria**  | 2203226    |
| **Vitor Venturi**       | 2301330    |

## **Dependências**

- Compilador C++ moderno (C++11 ou superior).
- Biblioteca `cmath` para cálculos trigonométricos e operações matemáticas.
