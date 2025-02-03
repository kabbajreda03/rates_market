#ifndef POSITION_HPP
#define POSITION_HPP

#include <pnl/pnl_vector.h>

class Position {
public:
    int date;                // Date de la position
    double portfolioValue;   // Valeur du portefeuille à cette date
    double price;            // Prix de la position
    double priceStdDev;      // Écart type du prix
    PnlVect* deltas;         // Sensibilité de la position
    PnlVect* deltasStdDev;   // Écart type des sensibilités

    // Constructeur
    Position(int d, double value, double prc, double stdDev, PnlVect* deltasVect)
        : date(d), portfolioValue(value), price(prc), priceStdDev(stdDev), deltas(deltasVect), deltasStdDev(pnl_vect_create(deltasVect->size)) {}

    // Destructeur
    ~Position() {
        pnl_vect_free(&deltas);
        pnl_vect_free(&deltasStdDev);
    }

    // Méthode pour calculer le prix de la position
    void calculatePrice() {
        // Implémentation pour calculer le prix de la position
    }
};

#endif
