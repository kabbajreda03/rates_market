#include "Option.hpp"
#include <iostream>

// Exemple de surcharge de la méthode payoff
double Option::payoff() {
    // Implémentation simple, à remplacer selon le type d'option
    std::cout << "Calcul du payoff non défini pour cette option." << std::endl;
    return 0.0;
}
