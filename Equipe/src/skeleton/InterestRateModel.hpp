#ifndef INTEREST_RATE_MODEL_HPP
#define INTEREST_RATE_MODEL_HPP

#include <cmath>
#include <iostream>

class InterestRateModel {
public:
    double domesticInterestRate;
    double foreignInterestRate;

    // Constructeur
    InterestRateModel(double domesticRate, double foreignRate)
        : domesticInterestRate(domesticRate), foreignInterestRate(foreignRate) {}

    // Méthode pour obtenir le taux de discount entre deux dates
    double discount(double t1, double t2) const {
        return exp(-domesticInterestRate * (t2 - t1));
    }

    // Méthode pour obtenir la valeur d'un compte entre deux dates
    double account(double t1, double t2) const {
        return exp(foreignInterestRate * (t2 - t1));
    }
};

#endif
