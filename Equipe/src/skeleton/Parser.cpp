#include "Parser.hpp"
#include <fstream>
#include "CallCurrencyOption.hpp"
#include "CallQuantoOption.hpp"
#include "RiskyAsset.hpp"
#include "FixedTime.hpp"
#include "ForeignAsianOption.hpp"
#include "GridTime.hpp"
#include "QuantoExchangeOption.hpp"

Parser::Parser(char* jsonFile, char* csvFile) {

    std::ifstream ifs(jsonFile);
    nlohmann::json jsonParams = nlohmann::json::parse(ifs);
    domesticCurrencyId = jsonParams.at("DomesticCurrencyId").get<std::string>();
    // Récupérer la volatilité des devises étrangères (en excluant la première devise)

    auto jsonCurrencies = jsonParams.at("Currencies");
    int order = 0;
    int idx = 0;
    currenciesSize = jsonCurrencies.size()-1;
    if (currenciesSize != 0) {
        volatilityCurrencyVector = pnl_vect_create(currenciesSize);
        foreignInterestRate = pnl_vect_create(currenciesSize);
        for (auto jsonCurrency : jsonCurrencies) {
            std::string id = jsonCurrency.at("id");
            if (id == domesticCurrencyId) {
                domesticInterestRate = jsonCurrency.at("InterestRate").get<double>();
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
    } else {
        domesticInterestRate = jsonCurrencies.at(0).at("InterestRate").get<double>();
        currenciesOrder[jsonCurrencies.at(0).at("id")] = -1;
    }

    // Récupérer la correspondance des actifs et leur volatilité
    auto jsonAssets = jsonParams.at("Assets");
    assetsSize = jsonAssets.size();
    if (assetsSize != 0) {
        assetsVolatilityVector = pnl_vect_create(jsonAssets.size());
        for (int i = 0; i < jsonAssets.size(); i++) {
            std::string currencyId = jsonAssets.at(i).at("CurrencyId").get<std::string>();
            double assetVolatility = jsonAssets.at(i).at("Volatility").get<double>();
            LET(assetsVolatilityVector, i) = assetVolatility;
            assetsCurrencyMapping.push_back(currenciesOrder[currencyId]);
        }
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
    for (int i = 0; i < correlationMatrix->m; ++i) {
        for (int j = 0; j < correlationMatrix->n; ++j) {
            MLET(correlationMatrix, i, j) = correlations[i][j].get<double>();
        }
    }
    choleskyMatrix = pnl_mat_copy(correlationMatrix);
    pnl_mat_chol(choleskyMatrix);
    pnl_mat_print(choleskyMatrix);

    // Autres paramètres
    numberOfDaysInOneYear = jsonParams.at("NumberOfDaysInOneYear").get<int>();
    sampleNb = jsonParams.at("SampleNb").get<int>();
    fdStep = jsonParams.at("RelativeFiniteDifferenceStep").get<double>();
    optionType = jsonParams.at("Option").at("Type").get<std::string>();
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

    marketData = pnl_mat_create_from_file(csvFile);
}

Parser::~Parser() {
    // Libération des ressources allouées dynamiquement
}

void Parser::generateAssets(std::vector<RiskyAsset>& assetsVect) {
    if (assetsSize != 0) {
        InterestRateModel interestRate(domesticInterestRate);
        PnlVect* assetVolLine = pnl_vect_new();
        PnlVect* currencyVolLine = pnl_vect_new();
        for (int i = 0; i < assetsSize; i++) {
            pnl_mat_get_row(assetVolLine, choleskyMatrix, i);
            pnl_vect_mult_scalar(assetVolLine, GET(assetsVolatilityVector, i));
            if (assetsCurrencyMapping[i] != -1) {
                pnl_mat_get_row(currencyVolLine, choleskyMatrix, assetsSize+assetsCurrencyMapping[i]);
                pnl_vect_mult_scalar(currencyVolLine, GET(volatilityCurrencyVector, assetsCurrencyMapping[i]));
                pnl_vect_plus_vect(assetVolLine, currencyVolLine);
            }
            RiskyAsset riskyAsset = RiskyAsset(assetVolLine, interestRate);
            assetsVect.push_back(riskyAsset);
        }
    }
}
void Parser::generateCurrencies(std::vector<Currency>& currenciesVect) {
    if (currenciesSize != 0) {
        InterestRateModel domesticRate(domesticInterestRate);
        PnlVect* currencyVolLine = pnl_vect_create(choleskyMatrix->n);
        for (int i = 0; i < assetsSize; i++) {
            InterestRateModel foreignRate(GET(foreignInterestRate, i));
            pnl_mat_get_row(currencyVolLine, choleskyMatrix, assetsSize + i);
            pnl_vect_mult_scalar(currencyVolLine, GET(volatilityCurrencyVector, i));
            Currency currency(currencyVolLine, domesticRate, foreignRate);
            currenciesVect.push_back(currency);
        }
        pnl_vect_free(&currencyVolLine);
        }
}

void Parser::getPastPrices(PnlMat* past, int t) {
    int index = 0;
    PnlVect* pastLine = pnl_vect_new();
    PnlVect* dates = FixingDatesManager->dates;
    while (index < FixingDatesManager->len() and GET(dates, index) < t) {
        pnl_mat_get_row(pastLine, marketData, GET(dates, index));
        pnl_mat_set_row(past, pastLine, index);
        index++;
    }
    pnl_mat_get_row(pastLine, marketData, t);
    pnl_mat_set_row(past, pastLine, index);
}

void Parser::generatePastMatrix(PnlMat* past, int t) {
    getPastPrices(past, t);
    PnlVect* currencyCol = pnl_vect_new();
    PnlVect* assetCol = pnl_vect_new();
    for (int i = 0; i < assetsSize; i++) {
        if (assetsCurrencyMapping[i] != -1) {
            pnl_mat_get_col(assetCol, past, i);
            pnl_mat_get_col(currencyCol, past, assetsCurrencyMapping[i]+assetsSize);
            pnl_vect_mult_vect_term(assetCol, currencyCol);
            pnl_mat_set_col(past, assetCol, i);
        }
    }
    PnlVect* riskFreeAsset = pnl_vect_create_from_scalar(past->m, 0.0);
    for (int i = 0; i < currenciesSize; i++) {
        // On crée une liste des prix de l'actif sans risque dans les dates de constatation
        if (t != 0) {
            for (int j = 0; j < riskFreeAsset->size-1; j++) {
                LET(riskFreeAsset, j) = GET(FixingDatesManager->dates, j);
            }
            LET(riskFreeAsset, past->m-1) = t;
        }

        double foreignRate = GET(foreignInterestRate, i);
        for (int j = 0; j < riskFreeAsset->size; j++) {
            LET(riskFreeAsset, j) = std::exp(foreignRate * GET(riskFreeAsset, j)/252);
        }

        pnl_mat_get_col(currencyCol, past, i+assetsSize);
        pnl_vect_mult_vect_term(currencyCol, riskFreeAsset);
        pnl_mat_set_col(past, currencyCol, i+assetsSize);
    }
}

void Parser::generateInterestRateModels(std::vector<InterestRateModel>& interestRateModelsVect) {
    for (int i = 0; i < currenciesSize; i++) {
        InterestRateModel foreignRate(GET(foreignInterestRate, i));
        interestRateModelsVect.push_back(foreignRate);
    }
}

Option* Parser::getOption() {
    std::vector<InterestRateModel> interestRateModelsVect;
    generateInterestRateModels(interestRateModelsVect);
    InterestRateModel domesticRateModel(domesticInterestRate);
    if (optionType == "foreign_asian") {
        return new ForeignAsianOption(assetsCurrencyMapping, interestRateModelsVect, domesticRateModel,
            FixingDatesManager, strike);
    }
    if (optionType == "call_currency") {
        return new CallCurrencyOption(assetsCurrencyMapping, interestRateModelsVect, domesticRateModel,
            FixingDatesManager, strike);
    }
    if (optionType == "call_quanto") {
        return new CallQuantoOption(assetsCurrencyMapping, interestRateModelsVect, domesticRateModel,
            FixingDatesManager, strike);
    }
    if (optionType == "quanto_exchange") {
        return new QuantoExchangeOption(assetsCurrencyMapping, interestRateModelsVect, domesticRateModel,
            FixingDatesManager, strike);
    }
    return nullptr;
}
