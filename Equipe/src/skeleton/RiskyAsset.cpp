#include "RiskyAsset.hpp"
#include "Currency.hpp"
#include <cmath>
#include <pnl/pnl_vector.h>
#include <pnl/pnl_matrix.h>

// Constructeur
RiskyAsset::RiskyAsset(PnlVect* vol, PnlMat* cholMatrix, const Currency& currency)
    : volatility(vol), choleskyMatrix(cholMatrix), currency(currency) {}

// Méthode pour simuler la trajectoire d'un actif risqué
void RiskyAsset::simulate(PnlMat* path, double t, const PnlMat* past, PnlRng* rng, double T, int N) const {
    double dt = (T - t) / N; 
    PnlVect* G_i = pnl_vect_create(volatility->size); 
    pnl_vect_rng_normal(G_i, volatility->size, rng);
    PnlVect* prev_s = pnl_vect_create(volatility->size);
    pnl_mat_get_row(prev_s, past, past->m - 1);

    for (int i = 0; i < N; ++i) {
        double sigma_d = 0.0;
        for (int j = 0; j < volatility->size; ++j) {
            sigma_d += GET(volatility, j) * GET(volatility, j); 
        }
        double drift = (currency.domesticInterestRate.domesticInterestRate - 0.5 * sigma_d) * dt;
        double diffusion = sqrt(dt) * pnl_vect_scalar_prod(choleskyMatrix, G_i); 
        for (int j = 0; j < volatility->size; ++j) {
            double newSpot = GET(prev_s, j) * exp(drift + diffusion);
            pnl_mat_set(path, i, j, newSpot);
        }
        pnl_mat_get_row(prev_s, path, i);
    }

    pnl_vect_free(&G_i);
    pnl_vect_free(&prev_s);
}
