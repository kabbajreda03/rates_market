#ifndef OPTION_HPP
#define OPTION_HPP

#include <vector>
#include "InterestRateModel.hpp"
#include "ITimeGrid.hpp"

class Option {
public:
    int* assetCurrencyMapping;  // Cartographie des actifs aux devises
    std::vector<InterestRateModel> foreignInterestRates;  // Taux d'intérêt pour chaque devise étrangère
    InterestRateModel domesticInterestRate;  // Taux d'intérêt domestique
    ITimeGrid monitoringTimeGrid;  // Grille de temps pour le suivi des données

    // Constructeur
    Option(int* assetMapping, std::vector<InterestRateModel> foreignRates, InterestRateModel domesticRate, ITimeGrid timeGrid)
        : assetCurrencyMapping(assetMapping), foreignInterestRates(foreignRates), domesticInterestRate(domesticRate), monitoringTimeGrid(timeGrid) {}

    // Méthode virtuelle pour le calcul du payoff
    virtual double payoff() = 0;  // À implémenter dans les classes dérivées

    // Destructeur
    virtual ~Option() {}
};

#endif
