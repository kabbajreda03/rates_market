#include "RiskyDynamics.hpp"
#include <cmath>

// Constructeur
RiskyDynamics::RiskyDynamics()
    : drift(0.0), volatilityVector(pnl_vect_new()) {}

RiskyDynamics::RiskyDynamics(double drift, PnlVect* volatility)
    : drift(drift), volatilityVector(pnl_vect_copy(volatility)) {}

// Destructeur
RiskyDynamics::~RiskyDynamics() {
    pnl_vect_free(&volatilityVector);  // Libère la mémoire allouée pour la volatilité
}

// Méthode pour échantillonner la prochaine date de l'actif risqué
void RiskyDynamics::sampleNextDate(double spot, PnlMat* path, int i, int j, int timestep, PnlVect* gaussianVector, PnlVect* choleskyLine) const {
  double volatility = pnl_vect_sum(volatilityVector);
  double volatilityTerm = volatility * pnl_vect_scalar_prod(choleskyLine, gaussianVector) * std::sqrt(timestep/252);
  double driftTerm = drift * timestep/252;
  MLET(path, i, j) = spot * std::exp(driftTerm + volatilityTerm);
}