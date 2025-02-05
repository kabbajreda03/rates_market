#include "RiskyDynamics.hpp"
#include <cmath>

// Constructeur
RiskyDynamics::RiskyDynamics()
    : drift(0.0), volatilityVector(pnl_vect_new()) {}

RiskyDynamics::RiskyDynamics(double drift, PnlVect* volatility)
    : drift(drift), volatilityVector(pnl_vect_copy(volatility)) {}

// Destructeur
RiskyDynamics::~RiskyDynamics() {

}

// Méthode pour échantillonner la prochaine date de l'actif risqué
void RiskyDynamics::sampleNextDate(double spot, PnlMat* path, int i, int j, int timestep, PnlVect* gaussianVector) const {
  double volatilityTerm = pnl_vect_scalar_prod(volatilityVector, gaussianVector) * std::sqrt((double) timestep/252);
  double driftTerm = ( drift - pnl_vect_scalar_prod(volatilityVector , volatilityVector)/2) * (double) timestep/252;
  MLET(path, i, j) = spot * std::exp(driftTerm + volatilityTerm);
}