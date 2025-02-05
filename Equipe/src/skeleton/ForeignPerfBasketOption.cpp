#include "ForeignPerfBasketOption.hpp"

ForeignPerfBasketOption::ForeignPerfBasketOption(const std::vector<int>& assetCurrencyMapping,
                                                 const std::vector<InterestRateModel>& foreignInterestRates,
                                                 const InterestRateModel& domesticInterestRate,
                                                 ITimeGrid* monitoringTimeGrid, double strike)
    : Option(assetCurrencyMapping, foreignInterestRates, domesticInterestRate, monitoringTimeGrid),
      strike(strike) {}

double ForeignPerfBasketOption::payoff(PnlMat *path) const {
    return 0.0;
}