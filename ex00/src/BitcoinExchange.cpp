#include "BitcoinExchange.hpp"
#include "CSVReader.hpp"
#include "Date.hpp"
#include <iostream>
#include <sstream>
#include <iomanip>
#include <algorithm>
#include <list>
#include <cctype>


namespace {

std::string trim(const std::string& str) {
    auto notSpace = [](unsigned char c) { return !std::isspace(c); };

    auto start = std::find_if(str.begin(), str.end(), notSpace);
    auto end = std::find_if(str.rbegin(), str.rend(), notSpace).base();

    if (start >= end) return ""; 

    return std::string(start, end);
}

}


double BitcoinExchange::getHistoricalPrice(const Date& date) const
{
    auto  it = priceMap.upper_bound(date);
    if (it == priceMap.begin()) {
        throw std::runtime_error("No lower date");
    }
    --it;
    return it->second;
}

void BitcoinExchange::loadPricesFromCSV(CSVReader& dbReader)
{
    std::list<std::string> row;

    std::stringstream ss;
    size_t i = dbReader.hasCSVHeader() ? 1 : 0;
	while (dbReader.readRow(row))
	{
        i++;
        if (row.size() != DATA_PRICES_AMOUNT_COLUMNS)
        {
            std::cerr << "Price at " << i << " line has incorrect format" << std::endl;
            continue;
        }
        
        std::string dateStr = trim(row.front());
        row.pop_front();
        std::string priceStr = trim(row.front());
        
        ss.str(priceStr);
        ss.clear();

        double price;
        char remaining;
        
        if (!(ss >> price) || (ss >> remaining)) {
            std::cerr << "Price at " << i << " line has incorrect format." << std::endl;
            continue;
        }
        
        if (price < 0 || price > MAX_PRICE) {
            std::cerr << "Price at " << i << " line has incorrect value: ";
            std::cerr  << price << std::endl;
            continue; 
        }

        Date date(dateStr);
        auto [it, success] = priceMap.insert({date, price});
        
        if (!success) {
            std::cerr << "Error: duplicate date at " << i << " line found: ";
            std::cerr << dateStr << std::endl;
            continue; 
        }
	}
}

void BitcoinExchange::processBalanceFromCSV(CSVReader& balanceReader) {
    if (priceMap.size() == 0)
    {
        std::cout << "Need to load prices before processing" << std::endl;
        return;
    }
    std::cout << std::setprecision(8);
    std::list<std::string> row;

    std::stringstream ss;
    size_t i = balanceReader.hasCSVHeader() ? 1 : 0;
	while (balanceReader.readRow(row))
	{
        i++;
        if (row.size() != BALANCE_AMOUNT_COLUMNS)
        {
            std::cerr << "Error: bad input =>";
            while (!row.empty()) {
                std::cerr << " " << row.front();
                row.pop_front();
            }
            std::cerr << std::endl;
            continue;
        }
        
        std::string dateStr = trim(row.front());
        row.pop_front();
        std::string amountStr = trim(row.front());
        
        ss.str(amountStr);
        ss.clear();

        double amount;
        char remaining;
        
        if (!(ss >> amount) || (ss >> remaining)) {
            std::cerr << "Error: incorrect price string" << std::endl;
            continue;
        }
        
        if (amount > MAX_AMOUNT) {
            std::cerr << "Error: too large a number." << std::endl;
            continue; 
        }
        if (amount < 0) {
            std::cerr << "Error: not a positive number." << std::endl;
            continue; 
        }
        
        try {
            Date date(dateStr);
            double price = getHistoricalPrice(date);

            std::cout << date.toString() << " => ";
            std::cout << amountStr << " = ";
		    std::cout << amount*price << std::endl;
        }
        catch (const std::exception& e) {
            std::cerr << "Error: bad input => " << dateStr;
            // std::cerr << " (" << e.what() << ")";
            std::cerr << std::endl;
        }
	}
}
