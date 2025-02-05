#include "MonteCarlo.hpp"
#include <iostream>

// Constructeur
MonteCarlo::MonteCarlo(Option* option, GlobalModel model, Parser* parser)
    : option(option), model(model), parser(parser) {
          rng = pnl_rng_create(PNL_RNG_MERSENNE);
          pnl_rng_sseed(rng, time(NULL));
    }

// Méthode pour calculer le prix et les deltas
void MonteCarlo::priceAndDelta(PnlMat* past, int t, double& price, double& priceStdDev, PnlVect* deltas, PnlVect* deltasStdDev) {
    // Implémenter la logique pour la simulation Monte Carlo
    std::cout << "Simulation en cours..." << std::endl;
    // Code de simulation
    PnlMat* path = pnl_mat_create(option->monitoringTimeGrid->dates->size, past->n);
    for (int i = 0; i < parser->sampleNb; i++) {
        model.simulate_paths(past, path, t, rng);
        price += option->payoff(path);
		priceStdDev += option->payoff(path) * option->payoff(path);
    }
    double discountFactor = model.domesticInterestRate.discount((double) t, (double)parser->maturityInDays);
    price = price * discountFactor / parser->sampleNb;
	priceStdDev = abs(discountFactor * discountFactor * (priceStdDev/parser->sampleNb) - price * price);
    priceStdDev = std::sqrt(priceStdDev / parser->sampleNb);
}
