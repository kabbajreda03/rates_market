#ifndef OPTION_HPP
#define OPTION_HPP

#include "ITimeGrid.hpp"
#include "InterestRateModel.hpp"
#include <vector>
#include <string>
#include "pnl/pnl_vector.h"

class Option {
public:
    // Attributs
    std::vector<int> assetCurrencyMapping;
    std::vector<InterestRateModel> foreignInterestRates;
    InterestRateModel domesticInterestRate;
    ITimeGrid* monitoringTimeGrid;

    // Constructeur
    Option(const std::vector<int>& assetCurrencyMapping,
           const std::vector<InterestRateModel>& foreignInterestRates,
           const InterestRateModel& domesticInterestRate,
           ITimeGrid* monitoringTimeGrid);

    // Méthode virtuelle pure pour calculer le payoff
    virtual double payoff(PnlMat *path) const = 0;

    virtual ~Option() {}
};

#endif //OPTION_HPP