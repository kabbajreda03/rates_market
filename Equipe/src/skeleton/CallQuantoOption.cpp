#include "CallQuantoOption.hpp"

CallQuantoOption::CallQuantoOption(const std::vector<int>& assetCurrencyMapping,
                                   const std::vector<InterestRateModel>& foreignInterestRates,
                                   const InterestRateModel& domesticInterestRate,
                                   ITimeGrid* monitoringTimeGrid, double strike)
    : Option(assetCurrencyMapping, foreignInterestRates, domesticInterestRate, monitoringTimeGrid),
      strike(strike) {}

double CallQuantoOption::payoff(PnlMat *path) const {
    PnlVect* assets = pnl_vect_new();
    pnl_mat_get_row(assets, path, 0);
    return std::max(GET(assets, 0) - strike, 0.0);
}