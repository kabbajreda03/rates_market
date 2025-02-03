#include "Currency.hpp"
#include "InterestRateModel.hpp"

// Constructeur
Currency::Currency(double domesticRate, double foreignRate)
    : domesticInterestRate(domesticRate, foreignRate) {}

// Méthode pour obtenir le taux de change
double Currency::getExchangeRate(double t) const {
    return domesticInterestRate.discount(0, t) * foreignInterestRate.discount(0, t);
}
