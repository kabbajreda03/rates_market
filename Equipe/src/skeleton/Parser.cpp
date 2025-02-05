#include "Parser.hpp"
#include <fstream>
#include "RiskyAsset.hpp"
#include "FixedTime.hpp"
#include "GridTime.hpp"

Parser::Parser(nlohmann::json jsonParams) {

    auto jsonCurrencies = jsonParams.at("Currencies");
    // Récupérer la volatilité des devises étrangères (en excluant la première devise)
    int order = 0;
    int idx = 0;
    volatilityCurrencyVector = pnl_vect_create(jsonCurrencies.size()-1);
    foreignInterestRate = pnl_vect_create(jsonCurrencies.size()-1);
    domesticCurrencyId = jsonParams.at("DomesticCurrencyId").get<std::string>();
    for (auto jsonCurrency : jsonCurrencies) {
        std::string id = jsonCurrency.at("id");
        if (id == domesticCurrencyId) {
            domesticInterestRate = jsonCurrencies.at(0).at("InterestRate").get<double>();
            currenciesOrder[id] = -1;
        } else {
            double volatility = jsonCurrency.at("Volatility").get<double>();
            LET(volatilityCurrencyVector, idx) = volatility;
            double interestRate = jsonCurrency.at("InterestRate").get<double>();
            LET(foreignInterestRate, idx) = interestRate;
            currenciesOrder[id] = order;
            order++;
            idx++;
        }
    }


    // Récupérer la correspondance des actifs et leur volatilité
    auto jsonAssets = jsonParams.at("Assets");
    assetsVolatilityVector = pnl_vect_create(jsonAssets.size());
    for (int i = 0; i < jsonAssets.size(); i++) {
        std::string currencyId = jsonAssets.at(i).at("CurrencyId").get<std::string>();
        double assetVolatility = jsonAssets.at(i).at("Volatility").get<double>();
        LET(assetsVolatilityVector, i) = assetVolatility;
        assetsCurrencyMapping.push_back(currenciesOrder[currencyId]);
    }
    // Récupérer les informations liées à l'option
    maturityInDays = jsonParams.at("Option").at("MaturityInDays").get<int>();
    if (jsonParams.at("Option").contains("Strike")) {
        strike = jsonParams.at("Option").at("Strike").get<double>();
    } else {
        strike = 0.0;
    }

    // Récupérer la grille de temps de surveillance
    auto fixingDatesJson = jsonParams.at("Option").at("FixingDatesInDays");
    ITimeGrid* fixingDates = nullptr;
    if (fixingDatesJson.at("Type").get<std::string>() == "Grid") {
        std::vector<double> fixingDatesStdVector = fixingDatesJson.at("DatesInDays").get<std::vector<double>>();
        PnlVect* fixingDatesVector = pnl_vect_create_from_ptr(fixingDatesStdVector.size(), fixingDatesStdVector.data());
        fixingDates = new GridTime(fixingDatesVector);

    }
    else if (fixingDatesJson.at("Type").get<std::string>() == "Fixed") {
        int period = jsonParams.at("Option").at("FixingDatesInDays").at("Period").get<int>();
        fixingDates = new FixedTime(period, maturityInDays);
    }
    FixingDatesManager = fixingDates;

    // Récupérer la matrice de corrélation
    auto correlations = jsonParams.at("Correlations");
    correlationMatrix = pnl_mat_create(correlations.size(), correlations[0].size());
    for (int i = 0; i < correlations.size(); ++i) {
        for (int j = 0; j < correlations[i].size(); ++j) {
            MLET(correlationMatrix, i, j) = correlations[i][j].get<double>();
        }
    }
    // Autres paramètres
    numberOfDaysInOneYear = jsonParams.at("NumberOfDaysInOneYear").get<int>();
    sampleNb = jsonParams.at("SampleNb").get<int>();
    fdStep = jsonParams.at("RelativeFiniteDifferenceStep").get<double>();

    // Rebalancement Oracle
    auto oracleJson = jsonParams.at("PortfolioRebalancingOracleDescription");
    OracleManager = nullptr;
    if (oracleJson.at("Type").get<std::string>() == "Grid") {
        std::vector<double> oracleDatesStdVector = oracleJson.at("DatesInDays").get<std::vector<double>>();
        PnlVect* oracleDatesVector = pnl_vect_create_from_ptr(oracleDatesStdVector.size(), oracleDatesStdVector.data());
        OracleManager = new GridTime(oracleDatesVector);  // Supposons Grid est une classe dérivée d'ITimeGrid
    }
    else if (oracleJson.at("Type").get<std::string>() == "Fixed") {
        int period = oracleJson.at("Period").get<int>();
        OracleManager = new FixedTime(period, maturityInDays);  // Supposons Grid est une classe dérivée d'ITimeGrid
    }
}

Parser::~Parser() {
    // Libération des ressources allouées dynamiquement
    if (FixingDatesManager) {
        delete FixingDatesManager;
    }
    if (correlationMatrix) {
        pnl_mat_free(&correlationMatrix);
    }
}

void Parser::generateAssets(std::vector<RiskyAsset>& assetsVect) {
    InterestRateModel interestRate(domesticInterestRate);
    PnlVect* assetVolLine = pnl_vect_new();
    PnlVect* currencyVolLine = pnl_vect_new();
    int assetsSize = assetsVolatilityVector->size;
    for (int i = 0; i < assetsVolatilityVector->size; i++) {
        pnl_mat_get_row(assetVolLine, correlationMatrix, i);
        pnl_vect_mult_scalar(assetVolLine, GET(assetsVolatilityVector, i));
        if (assetsCurrencyMapping[i] != -1) {
            pnl_mat_get_row(currencyVolLine, correlationMatrix, assetsSize+assetsCurrencyMapping[i]);
            pnl_vect_mult_scalar(currencyVolLine, GET(volatilityCurrencyVector, assetsCurrencyMapping[i]));
            pnl_vect_plus_vect(assetVolLine, currencyVolLine);
        }
        RiskyAsset riskyAsset = RiskyAsset(assetVolLine, interestRate);
        assetsVect.push_back(riskyAsset);
    }
}
void Parser::generateCurrencies(std::vector<Currency>& currenciesVect) {
    InterestRateModel domesticRate(domesticInterestRate);
    int assetsSize = assetsVolatilityVector->size;
    PnlVect* currencyVolLine = pnl_vect_create(correlationMatrix->n);
    for (int i = 0; i < volatilityCurrencyVector->size; i++) {
        InterestRateModel foreignRate(GET(foreignInterestRate, i));
        pnl_mat_get_row(currencyVolLine, correlationMatrix, assetsSize + i);
        pnl_vect_mult_scalar(currencyVolLine, GET(volatilityCurrencyVector, i));
        Currency currency(currencyVolLine, domesticRate, foreignRate);
        currenciesVect.push_back(currency);
    }
    pnl_vect_free(&currencyVolLine);
}

void Parser::generatePastMatrix(PnlMat* past) {
    
}