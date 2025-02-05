#include "QuantoExchangeOption.hpp"

QuantoExchangeOption::QuantoExchangeOption(const std::vector<int>& assetCurrencyMapping,
                                           const std::vector<InterestRateModel>& foreignInterestRates,
                                           const InterestRateModel& domesticInterestRate,
                                           ITimeGrid* monitoringTimeGrid, double strike)
    : Option(assetCurrencyMapping, foreignInterestRates, domesticInterestRate, monitoringTimeGrid),
      strike(strike) {}


double QuantoExchangeOption::payoff(PnlMat *path) const {
    double domesticAsset = MGET(path, path->m-1, 0);
    double foreignAsset = MGET(path, path->m-1, 1);
    return std::max(domesticAsset - foreignAsset - strike, 0.0);
}