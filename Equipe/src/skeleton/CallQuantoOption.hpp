#ifndef CALL_QUANTO_OPTION_HPP
#define CALL_QUANTO_OPTION_HPP

#include "Option.hpp"
#include "pnl/pnl_matrix.h"

class CallQuantoOption : public Option {
public:
    double strike;

    CallQuantoOption(const std::vector<int>& assetCurrencyMapping,
                     const std::vector<InterestRateModel>& foreignInterestRates,
                     const InterestRateModel& domesticInterestRate,
                     ITimeGrid* monitoringTimeGrid, double strike);

    double payoff(PnlMat *path) const override;  // Calcul du payoff de l'option call quanto
};

#endif