#include "ForeignAsianOption.hpp"

ForeignAsianOption::ForeignAsianOption(const std::vector<int>& assetCurrencyMapping,
                                       const std::vector<InterestRateModel>& foreignInterestRates,
                                       const InterestRateModel& domesticInterestRate,
                                       ITimeGrid* monitoringTimeGrid, double strike)
    : Option(assetCurrencyMapping, foreignInterestRates, domesticInterestRate, monitoringTimeGrid),
      strike(strike) {}

double ForeignAsianOption::payoff(PnlMat *path) const {
    // Calcul du payoff : (1/N * Σ(X^1_t_j * S^1_t_j) - S^0_T)_+
    double domesticAsset = MGET(path, path->m-1, 0);
    PnlVect* foreignAsset = pnl_vect_new();
    pnl_mat_get_col(foreignAsset, path, 1);
    double meanForeignAsset = pnl_vect_sum(foreignAsset) / foreignAsset->size;
    return std::max(meanForeignAsset - domesticAsset, 0.0);
}