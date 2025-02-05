#include "Option.hpp"

Option::Option(const std::vector<int>& assetCurrencyMapping,
               const std::vector<InterestRateModel>& foreignInterestRates,
               const InterestRateModel& domesticInterestRate,
               ITimeGrid* monitoringTimeGrid)
    : assetCurrencyMapping(assetCurrencyMapping),
      foreignInterestRates(foreignInterestRates),
      domesticInterestRate(domesticInterestRate),
      monitoringTimeGrid(monitoringTimeGrid) {}