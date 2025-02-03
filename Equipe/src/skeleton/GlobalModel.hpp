#ifndef GLOBAL_MODEL_HPP
#define GLOBAL_MODEL_HPP

#include "RiskyAsset.hpp"
#include "Currency.hpp"
#include "ITimeGrid.hpp"
#include <vector>
#include <pnl/pnl_matrix.h>

class GlobalModel {
public:
    std::vector<RiskyAsset> assets;
    std::vector<Currency> currencies;
    InterestRateModel domesticInterestRate;
    ITimeGrid monitoringTimeGrid;

    // Constructeur
    GlobalModel(std::vector<RiskyAsset> assets, std::vector<Currency> currencies, InterestRateModel domesticInterestRate)
        : assets(assets), currencies(currencies), domesticInterestRate(domesticInterestRate) {}

    // Méthode pour simuler l'ensemble du marché et remplir le chemin des actifs
    void simulateMarket(PnlMat* path, double t, const PnlMat* past, PnlRng* rng, double T, int N) const;
};

#endif
