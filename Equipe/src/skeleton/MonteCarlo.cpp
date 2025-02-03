#include "MonteCarlo.hpp"
#include <iostream>

// Constructeur
MonteCarlo::MonteCarlo(Option* option, GlobalModel model)
    : option(option), model(model) {}

// Méthode pour calculer le prix et les deltas
void MonteCarlo::priceAndDelta() {
    // Implémenter la logique pour la simulation Monte Carlo
    std::cout << "Simulation en cours..." << std::endl;
    // Code de simulation
}
