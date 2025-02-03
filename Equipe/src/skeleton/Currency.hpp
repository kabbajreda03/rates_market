#ifndef CURRENCY_HPP
#define CURRENCY_HPP

#include "InterestRateModel.hpp"

class Currency {
public:
    InterestRateModel domesticInterestRate;
    InterestRateModel foreignInterestRate;

    // Constructeur
    Currency(double domesticRate, double foreignRate)
        : domesticInterestRate(domesticRate, foreignRate) {}

    // Méthode pour obtenir le taux de change
    double getExchangeRate(double t) const {
        return domesticInterestRate.discount(0, t) * foreignInterestRate.discount(0, t);
    }
};

#endif
