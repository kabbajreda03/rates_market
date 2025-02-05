//
// Created by ensimag on 04/02/25.
//

#ifndef PARSER_HPP
#define PARSER_HPP
#include <string>
#include <vector>
#include "Option.hpp"
#include "ITimeGrid.hpp"
#include <nlohmann/json.hpp>
#include "Currency.hpp"
#include "RiskyAsset.hpp"

class Parser {

    public:
        std::string domesticCurrencyId;
        std::string optionType;
        double domesticInterestRate;
        PnlVect* foreignInterestRate = nullptr;
        PnlVect* volatilityCurrencyVector = nullptr;
        std::vector<int> assetsCurrencyMapping;
        std::unordered_map<std::string, int> currenciesOrder;
        PnlVect* assetsVolatilityVector = nullptr;
        ITimeGrid* OracleManager;
        ITimeGrid* FixingDatesManager;
        int numberOfDaysInOneYear;
        int maturityInDays;
        double strike;
        PnlMat* correlationMatrix;
        PnlMat* choleskyMatrix;
        int sampleNb;
        double fdStep;
        PnlMat* marketData;
        int assetsSize;
        int currenciesSize;

        Parser(char* jsonFile, char* csvFile);

        ~Parser();

        void generateAssets(std::vector<RiskyAsset>& assetsVect);
        void generateCurrencies(std::vector<Currency>& currenciesVect);
        void generateInterestRateModels(std::vector<InterestRateModel>& interestRateModelsVect);
        void getPastPrices(PnlMat* past, int t);
        void generatePastMatrix(PnlMat* past, int t);
        Option* getOption();
};



#endif //PARSER_HPP
