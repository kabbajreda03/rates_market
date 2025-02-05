#ifndef QUANTO_EXCHANGE_OPTION_HPP
#define QUANTO_EXCHANGE_OPTION_HPP

#include "Option.hpp"
#include "pnl/pnl_matrix.h"

class QuantoExchangeOption : public Option {
public:
    double strike;

    QuantoExchangeOption(const std::vector<int>& assetCurrencyMapping,
                         const std::vector<InterestRateModel>& foreignInterestRates,
                         const InterestRateModel& domesticInterestRate,
                         ITimeGrid* monitoringTimeGrid, double strike);

    double payoff(PnlMat *path) const override;  // Calcul du payoff de l'option quanto exchange
};

#endif //QUANTO_EXCHANGE_OPTION_HPP