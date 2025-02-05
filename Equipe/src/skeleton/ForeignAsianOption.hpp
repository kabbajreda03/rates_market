#ifndef FOREIGN_ASIAN_OPTION_HPP
#define FOREIGN_ASIAN_OPTION_HPP

#include "Option.hpp"
#include "pnl/pnl_matrix.h"

class ForeignAsianOption : public Option {
public:
    double strike;

    ForeignAsianOption(const std::vector<int>& assetCurrencyMapping,
                       const std::vector<InterestRateModel>& foreignInterestRates,
                       const InterestRateModel& domesticInterestRate,
                       ITimeGrid* monitoringTimeGrid, double strike);

    double payoff(PnlMat *path) const override;  // Calcul du payoff de l'option asiatique sur devise étrangère
};

#endif //FOREIGN_ASIAN_OPTION_HPP