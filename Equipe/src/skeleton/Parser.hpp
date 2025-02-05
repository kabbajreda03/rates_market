//
// Created by ensimag on 04/02/25.
//

#ifndef PARSER_HPP
#define PARSER_HPP
#include <string>
#include <vector>
#include <nlohmann/json_fwd.hpp>

#include "ITimeGrid.hpp"
#include "pnl/pnl_matrix.h"
#include <nlohmann/json.hpp>
#include "Currency.hpp"
#include "RiskyAsset.hpp"

class Parser {

    public:
        std::string domesticCurrencyId;
        double domesticInterestRate;
        PnlVect* foreignInterestRate;
        PnlVect* volatilityCurrencyVector;
        std::vector<int> assetsCurrencyMapping;
        std::unordered_map<std::string, int> currenciesOrder;
        PnlVect* assetsVolatilityVector;
        ITimeGrid* OracleManager;
        ITimeGrid* FixingDatesManager;
        int numberOfDaysInOneYear;
        int maturityInDays;
        double strike;
        PnlMat* correlationMatrix;
        int sampleNb;
        double fdStep;

        Parser(nlohmann::json jsonParams);

        ~Parser();

        void generateAssets(std::vector<RiskyAsset>& assetsVect);
        void generateCurrencies(std::vector<Currency>& currenciesVect);
        void generatePastMatrix(PnlMat* past);


};



#endif //PARSER_HPP
