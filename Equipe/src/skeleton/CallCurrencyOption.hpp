#ifndef CALL_CURRENCY_OPTION_HPP
#define CALL_CURRENCY_OPTION_HPP

#include "Option.hpp"
#include "pnl/pnl_matrix.h"

class CallCurrencyOption : public Option {
public:
    double strike;

    CallCurrencyOption(const std::vector<int>& assetCurrencyMapping,
                       const std::vector<InterestRateModel>& foreignInterestRates,
                       const InterestRateModel& domesticInterestRate,
                       ITimeGrid* monitoringTimeGrid, double strike);

    double payoff(PnlMat *path) const override;  // Calcul du payoff de l'option call currency
};

#endif //CALL_CURRENCY_OPTION_HPP