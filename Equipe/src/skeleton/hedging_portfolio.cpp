#include "MonteCarlo.hpp"
#include "GlobalModel.hpp"
#include "json_reader.hpp"
#include <iostream>
#include <vector>
#include "InterestRateModel.hpp"
#include "RiskyAsset.hpp"
#include "Currency.hpp"
#include "ITimeGrid.hpp"

int main() {
    // Charger les paramètres du modèle depuis un fichier JSON
    nlohmann::json jsonParams = read_json("params.json");

    // Créer des objets nécessaires comme MonteCarlo, GlobalModel, etc.
    InterestRateModel domesticInterestRate(0.05, 0.03);
    std::vector<RiskyAsset> riskyAssets;  // à remplir selon jsonParams
    std::vector<Currency> currencies;  // à remplir selon jsonParams
    GlobalModel globalModel(riskyAssets, currencies, domesticInterestRate);

    // Créer l'objet MonteCarlo avec l'option à évaluer
    Option* option = new Option();
    MonteCarlo monteCarlo(option, globalModel);

    // Créer un portefeuille
    Portfolio portfolio(monteCarlo, globalModel.monitoringTimeGrid);

    // Calculer les positions du portefeuille
    portfolio.calculatePositions();

    // Sauvegarder les résultats dans un fichier JSON
    save_json("portfolio.json", portfolio);

    delete option;  // Libérer la mémoire
    return 0;
}
