#include "InterestRateModel.hpp"
#include <cmath>
#include <iostream>

// Constructeur
InterestRateModel::InterestRateModel(double domesticRate, double foreignRate)
    : domesticInterestRate(domesticRate), foreignInterestRate(foreignRate) {}

// Méthode pour obtenir le taux de discount entre deux dates
double InterestRateModel::discount(double t1, double t2) const {
    return exp(-domesticInterestRate * (t2 - t1));
}

// Méthode pour obtenir la valeur d'un compte entre deux dates
double InterestRateModel::account(double t1, double t2) const {
    return exp(foreignInterestRate * (t2 - t1));
}
