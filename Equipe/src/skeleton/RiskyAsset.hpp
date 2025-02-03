#ifndef RISKY_ASSET_HPP
#define RISKY_ASSET_HPP

#include "Currency.hpp"
#include <pnl/pnl_vector.h>
#include <pnl/pnl_matrix.h>

class RiskyAsset {
public:
    PnlVect* volatility;
    PnlMat* choleskyMatrix;
    Currency currency;

    // Constructeur
    RiskyAsset(PnlVect* vol, PnlMat* cholMatrix, const Currency& currency)
        : volatility(vol), choleskyMatrix(cholMatrix), currency(currency) {}

    // Méthode pour simuler la trajectoire d'un actif risqué
    void simulate(PnlMat* path, double t, const PnlMat* past, PnlRng* rng, double T, int N) const;
};

#endif
