#include "Position.hpp"

// Constructeur
Position::Position(int d, double value, double prc, double stdDev, PnlVect* deltasVect)
    : date(d), portfolioValue(value), price(prc), priceStdDev(stdDev), deltas(deltasVect), deltasStdDev(pnl_vect_create(deltasVect->size)) {}

// Méthode pour calculer le prix de la position
void Position::calculatePrice() {
    // Implémentation pour calculer le prix de la position
    // Cette méthode pourrait être complétée pour calculer le prix basé sur un modèle
    std::cout << "Calcul du prix de la position pour la date " << date << std::endl;
}
