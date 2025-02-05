#include "GlobalModel.hpp"
#include "pnl/pnl_vector.h"
#include "pnl/pnl_matrix.h"
#include "RiskyDynamics.hpp"

// Constructeur
GlobalModel::GlobalModel(
    const std::vector<RiskyAsset>& assets,
    const std::vector<Currency>& currencies,
    ITimeGrid* monitoringTimeGrid,
    const InterestRateModel& domesticInterestRate
)
    : assets(assets),
      currencies(currencies),
      monitoringTimeGrid(monitoringTimeGrid),
      domesticInterestRate(domesticInterestRate) {}

// Destructeur
GlobalModel::~GlobalModel() {
    // Si nécessaire, libérer les ressources allouées dynamiquement (ici monitoringTimeGrid)
    // Par exemple, si monitoringTimeGrid a été alloué dynamiquement (via new), libérer la mémoire ici
    // delete monitoringTimeGrid; // si monitoringTimeGrid est alloué dynamiquement
}

void GlobalModel::simulate_paths(PnlMat* past, PnlMat* path, int t, PnlRng* rng) {
    pnl_mat_set_subblock(path, past, 0, 0);
    bool isMonitoringDate = monitoringTimeGrid->has(t);
    int timestep = 0;
    int assetsSize = assets.size();
    int currenciesSize = currencies.size();
    int index = monitoringTimeGrid->getNextFirstIndex(t);
    if (!isMonitoringDate) {
        PnlVect* gaussianVector = pnl_vect_create(path->n);
        pnl_vect_rng_normal(gaussianVector, path->n, rng);
        PnlVect* St = pnl_vect_create(path->n);
        pnl_mat_get_row(St, past, past->m-1);
        timestep = monitoringTimeGrid->at(index) - t;
        for (int j = 0; j < assetsSize; j++) {
          assets[j].sampleNextDate(GET(St, j) ,path, past->m-1, j, timestep, gaussianVector);
        }
        for (int j = 0; j < currenciesSize; j++) {
            currencies[j].sampleNextDate(GET(St, assetsSize+j), path, past->m-1, assetsSize+j, timestep, gaussianVector);
        }
    }
    // t is a monitoring date
    for (int i = past->m; i < path->m; i++) {
      PnlVect* gaussianVector = pnl_vect_create(path->n);
      pnl_vect_rng_normal(gaussianVector, path->n, rng);
      // On respecte l'ordre des actifs comme dans le fichier .csv
      PnlVect* spots = pnl_vect_create(path->n);
      pnl_mat_get_row(spots, path, i-1);
      timestep = monitoringTimeGrid->at(index + 1) - monitoringTimeGrid->at(index);
      index++;
        for (int j = 0; j < assetsSize; j++) {
            assets[j].sampleNextDate(GET(spots, j), path, i, j, timestep, gaussianVector);
        }

        for (int j = 0; j < currenciesSize; j++) {
            currencies[j].sampleNextDate(GET(spots, assetsSize+j), path, i, assetsSize+j, timestep, gaussianVector);
        }
    }


}