#include "trig_classe.hpp"

int main() {
    Trigonometria angulo1(30.0);
    Trigonometria angulo2(45.0);

    std::cout << "Seno de 30 graus: " << angulo1.seno() << std::endl;
    std::cout << "Cosseno de 30 graus: " << angulo1.cosseno() << std::endl;
    std::cout << "Tangente de 30 graus: " << angulo1.tangente() << std::endl;

    std::cout << "Seno da soma (30 + 45 graus): " << (angulo1 + angulo2) << std::endl;
    std::cout << "Seno da diferença (30 - 45 graus): " << (angulo1 - angulo2) << std::endl;
    std::cout << "Cosseno da soma (30 + 45 graus): " << (angulo1 * angulo2) << std::endl;
    std::cout << "Cosseno da diferença (30 - 45 graus): " << (angulo1 / angulo2) << std::endl;

    return 0;
}