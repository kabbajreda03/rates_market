#ifndef FOREIGN_PERF_BASKET_OPTION_HPP
#define FOREIGN_PERF_BASKET_OPTION_HPP

#include "Option.hpp"
#include "pnl/pnl_matrix.h"

class ForeignPerfBasketOption : public Option {
public:
    double strike;

    ForeignPerfBasketOption(const std::vector<int>& assetCurrencyMapping,
                            const std::vector<InterestRateModel>& foreignInterestRates,
                            const InterestRateModel& domesticInterestRate,
                            ITimeGrid* monitoringTimeGrid, double strike);

    double payoff(PnlMat *path) const override;  // Calcul du payoff de l'option performance sur paniers étrangers
};

#endif //FOREIGN_PERF_BASKET_OPTION_HPP