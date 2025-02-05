#include <iostream>
#include <fstream>

#include "FixedTime.hpp"
#include "GridTime.hpp"
#include "json_reader.hpp"
#include "InterestRateModel.hpp"
#include "Parser.hpp"
#include "GlobalModel.hpp"
#include "MonteCarlo.hpp"

int main(int argc, char **argv) {
    if (argc != 3) {
        std::cerr << "Wrong number of arguments. Exactly one argument is required" << std::endl;
        std::exit(0);
    }
    std::ifstream ifs(argv[1]);
    nlohmann::json jsonParams = nlohmann::json::parse(ifs);

    /**PnlMat *correlation;
    jsonParams.at("Correlations").get_to(correlation);
    pnl_mat_print(correlation);

    std::string domesticCurrencyId;
    jsonParams.at("DomesticCurrencyId").get_to(domesticCurrencyId);
    int assetNb = jsonParams.at("Assets").size();
    std::cout << "Number of assets " << assetNb << std::endl;

    std::cout << "-- currencies" << std::endl;
    auto jsonCurrencies = jsonParams.at("Currencies");
    for (auto jsonCurrency : jsonCurrencies) {
        std::string currencyId(jsonCurrency.at("id").get<std::string>());
        double rf = jsonCurrency.at("InterestRate").get<double>();
        double realVolatility = jsonCurrency.at("Volatility").get<double>();
        if (currencyId == "eur") {
            InterestRateModel domestic(rf);
        }
        else {
            InterestRateModel foreign(rf);
        }
        std::cout << "interest rate " << rf << std::endl;
        std::cout << "real volatility " << realVolatility << std::endl;
    }

    std::cout << "-- assets" << std::endl;
    auto jsonAssets = jsonParams.at("Assets");
    for (auto jsonAsset : jsonAssets) {
        std::string currencyId(jsonAsset.at("CurrencyId").get<std::string>());
        double realVolatility = jsonAsset.at("Volatility").get<double>();
        std::cout << "currency " << currencyId << std::endl;
        std::cout << "real volatility " << realVolatility << std::endl;
    }

    int numberOfDaysPerYear = jsonParams.at("NumberOfDaysInOneYear").get<int>();
    double maturity = jsonParams.at("Option").at("MaturityInDays").get<int>() / double (numberOfDaysPerYear);
    std::string label = jsonParams.at("Option").at("Type").get<std::string>();
    PnlVect* datesInDays;
    jsonParams.at("Option").at("FixingDatesInDays").at("DatesInDays").get_to(datesInDays);

    pnl_mat_free(&correlation);
    std::exit(0);
    PnlMat* past = pnl_mat_create_from_scalar(1, 1, 100);
    GridTime* gridTime = new GridTime(datesInDays);**/

    Parser parser(argv[1], argv[2]);

    // Méthode pour imprimer les attributs de la classe
        /**std::cout << "Domestic Interest Rate: " << parser.domesticInterestRate << std::endl;
        std::cout << "Foreign Interest Rates: ";
        pnl_vect_print(parser.foreignInterestRate);

        std::cout << "Volatility Currency Vector: ";
        pnl_vect_print(parser.volatilityCurrencyVector);
        std::cout << std::endl;

        std::cout << "Assets Currency Mapping: ";
        for (const auto& asset : parser.assetsCurrencyMapping) {
            std::cout << asset << " ";
        }
        std::cout << std::endl;

        std::cout << "Assets Volatility Vector: ";
        pnl_vect_print(parser.assetsVolatilityVector);
        std::cout << std::endl;


        if (parser.FixingDatesManager->dates != nullptr) {
            std::cout << "FixingDatesInDays: ";
            pnl_vect_print(parser.FixingDatesManager->dates);
        }
        else {
            std::cout << "Period: ";
            std::cout << parser.FixingDatesManager->step << std::endl;
        }
        std::cout << "Option Type: ";
        std::cout << static_cast<int>(parser.FixingDatesManager->type) << std::endl;

        if (parser.OracleManager->dates != nullptr) {
            std::cout << "OracleDates: ";
            pnl_vect_print(parser.OracleManager->dates);
        }
        else {
            std::cout << "Period: ";
            std::cout << parser.OracleManager->step << std::endl;
        }

        std::cout << "Oracle Rebalancing Type: ";
        std::cout << static_cast<int>(parser.OracleManager->type) << std::endl;
        std::cout << "Number of Days in One Year: " << parser.numberOfDaysInOneYear << std::endl;
        std::cout << "Maturity in Days: " << parser.maturityInDays << std::endl;
        std::cout << "Strike: " << parser.strike << std::endl;
        std::cout << "Sample Number: " << parser.sampleNb << std::endl;
        std::cout << "Finite Difference Step: " << parser.fdStep << std::endl;
        std::cout << "Correlation Matrix: ";
        pnl_mat_print(parser.correlationMatrix);
**/
        std::vector<RiskyAsset> riskyAssets;
        std::vector<Currency> currencies;
        parser.generateCurrencies(currencies);
        parser.generateAssets(riskyAssets);
        InterestRateModel domesticRate(parser.domesticInterestRate);
        GlobalModel globalModel(riskyAssets, currencies, parser.FixingDatesManager, domesticRate);
        PnlMat* past = pnl_mat_create(1, 1);
        parser.generatePastMatrix(past, 0);
        Option* option = parser.getOption();
        MonteCarlo* mc = new MonteCarlo(option, globalModel, &parser);
        double price = 0.0;
        double priceStdDev = 0.0;
        mc->priceAndDelta(past, 0, price, priceStdDev, NULL, NULL);
        std::cout << "price: " << price << std::endl;
        std::cout << "Standard Deviation of price: " << priceStdDev << std::endl;
        std::cout << "THE END: " << std::endl;

}
