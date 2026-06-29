#pragma once

#include "CSVReader.hpp"
#include "Date.hpp"
#include <map>
#include <string>


class BitcoinExchange
{
    private:
        std::map<Date, double> priceMap;
        static constexpr const unsigned int DATA_PRICES_AMOUNT_COLUMNS = 2;
        static constexpr const unsigned int BALANCE_AMOUNT_COLUMNS = 2;
        static constexpr const unsigned int MAX_PRICE = 1000000;
        static constexpr const unsigned int MAX_AMOUNT = 1000;

    public:
        BitcoinExchange() = default;
        BitcoinExchange(const BitcoinExchange& other) = default;
        BitcoinExchange& operator=(const BitcoinExchange& other) = default;
        ~BitcoinExchange() = default;

        void loadPricesFromCSV(CSVReader& dbReader);
        void processBalanceFromCSV(CSVReader& balanceReader);
        double getHistoricalPrice(const Date& date) const;
};
