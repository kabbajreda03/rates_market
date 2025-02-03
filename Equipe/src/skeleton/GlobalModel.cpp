#include "GlobalModel.hpp"
#include <pnl/pnl_matrix.h>
#include <vector>

// Constructeur
GlobalModel::GlobalModel(std::vector<RiskyAsset> assets, std::vector<Currency> currencies, InterestRateModel domesticInterestRate)
    : assets(assets), currencies(currencies), domesticInterestRate(domesticInterestRate) {}

// Méthode pour simuler l'ensemble du marché et remplir le chemin des actifs
void GlobalModel::simulateMarket(PnlMat* path, double t, const PnlMat* past, PnlRng* rng, double T, int N) const {
    pnl_mat_set_subblock(path, past, 0, 0);
    for (const auto& asset : assets) {
        asset.simulate(path, t, past, rng, T, N);
    }
}
