#ifndef MONTE_CARLO_HPP
#define MONTE_CARLO_HPP

#include "Option.hpp"
#include "GlobalModel.hpp"
#include "Parser.hpp"

class MonteCarlo {
public:
    Option* option;
    GlobalModel model;
    Parser* parser;
    PnlRng* rng;

    // Constructeur
    MonteCarlo(Option* option, GlobalModel model, Parser* parser);

    // Méthode pour calculer le prix et les deltas
    void priceAndDelta(PnlMat* past, int t, double& price, double& priceStdDev, PnlVect* deltas, PnlVect* deltasStdDev);
};

#endif
