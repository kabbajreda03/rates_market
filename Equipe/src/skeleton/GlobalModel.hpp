#ifndef GLOBALMODEL_HPP
#define GLOBALMODEL_HPP

#include <vector>
#include "RiskyAsset.hpp"  // Inclure pour RiskyAssets
#include "Currency.hpp"    // Inclure pour Currency
#include "ITimeGrid.hpp"   // Inclure pour ITimeGrid
#include "InterestRateModel.hpp"  // Inclure pour InterestRateModel

class GlobalModel {
public:
    // Vecteur d'actifs risqués
    std::vector<RiskyAsset> assets;

    // Vecteur de devises
    std::vector<Currency> currencies;

    // Grille de temps pour la surveillance
    ITimeGrid* monitoringTimeGrid;

    // Modèle de taux d'intérêt domestique
    InterestRateModel domesticInterestRate;

    const PnlMat* correlationMatrix;

    PnlMat* choleskyMatrix;

    // Constructeur
    GlobalModel(
        const std::vector<RiskyAsset>& assets,
        const std::vector<Currency>& currencies,
        ITimeGrid* monitoringTimeGrid,
        const InterestRateModel& domesticInterestRate,
        const PnlMat* correlationMatrix
    );

    // Destructeur
    ~GlobalModel();

    void simulate_paths(PnlMat* past, PnlMat* path, int t, PnlRng* rng);
};

#endif