#include <cmath>
#include <iostream>
#include "trigonometria.hpp"
#include "vetores.hpp"
#include "matrizes.hpp"

#define MAX_ERROR 0.001

using namespace std;

int main(void){
  Trigonometria a1, a2, a3;
  Vetor v1("v1.txt"), v2("v2.txt"), v3("v3.txt"), v4("v4.txt");
  Matriz m1("m1.txt"), m2("m2.txt"), m3("m3.txt"), m4("m4.txt");
  int anguloGraus1, anguloGraus2;
  float anguloRadianos;

  cout << "Ângulo 1 (em graus):";
  cin >> anguloGraus1;
  a1.definirAngulo(anguloGraus1);

  cout << "Ângulo 2 (em graus):";
  cin >> anguloGraus2;
  a2.definirAngulo(anguloGraus2);

  cout << "Ângulo 3 (em radianos):";
  cin >> anguloradianos
  a3.definirAngulo(anguloRadianos);

  float error = abs(a1.cos() - cos(a1.getRadianos());
  if(error < MAX_ERROR) cout << "cos(a1) is OK!" << endl;
  else cout << "cos(a1) has an error of " << error << endl;

  error = abs(a2.sin() - sin(a2.getRadianos());
  if(error < MAX_ERROR) cout << "sin(a2) is OK!" << endl;
  else cout << "sin(a2) has an error of " << error << endl;

  error = abs(a3.tan() - tan(a3.getRadianos());
  if(error < MAX_ERROR) cout << "tan(a3) is OK!" << endl;
  else cout << "tan(a3) has an error of " << error << endl;

  Vetor soma = v1 + v2;
  Vetor dif = v3 - v2;
  float prodEscT = v1 . v4; // produto escalar
  float prodEsc = v1 . v3; // produto escalar
  Vetor prodVet = v1 * v3; // produto vetorial
  float dist = v1.distancia(v2);
  float norma = v4.norma();

  soma.exibir();
  dif.exibir();
  cout << "Produto escalar entre v1 e v3 = " << prodEsc << endl;
  prodVet.exibir();
  cout << "Distância entre v1 e v2 = " << dist << endl;
  cout << "Norma de v4 = " << norma << endl;

  Matriz soma = m1 + m2;
  Matriz dif = m3 - m2;
  Matriz prodT = m1 * m4;
  Matriz prod = m1 * m3;
  Matriz inv = m4.inversa();
  Matriz transp = m1.transposta();
  float det = m4.determinante();

  soma.exibir();
  dif.exibir();
  prod.exibir();
  inv.exibir();
  transp.exibir();
  cout << "Determinante de m4 = " << det << endl;

  return 0;
}