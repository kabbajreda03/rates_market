#ifndef MONTE_CARLO_HPP
#define MONTE_CARLO_HPP

#include "Option.hpp"
#include "GlobalModel.hpp"

class MonteCarlo {
public:
    Option* option;
    GlobalModel model;

    // Constructeur
    MonteCarlo(Option* option, GlobalModel model)
        : option(option), model(model) {}

    // Méthode pour calculer le prix et les deltas
    void priceAndDelta();
};

#endif
