#include "CSVReader.hpp"
#include <fstream>
#include <utility>
#include <iostream>
#include <stdexcept>
#include <algorithm>
#include <cctype>


namespace {
    bool getIntValue(std::string& dateStr, std::size_t start, std::size_t end, int& value)
    {
        for (std::size_t i = start; i < end; ++i)
        {
            if (!std::isdigit(static_cast<unsigned int>( dateStr[i])))
                return false;
        }
        value = std::atoi(dateStr.substr(start, end).c_str());
        return true;
    }

    bool getDoubleValue(std::string& priceStr, double& price)
    {
        std::size_t pos = 0;
        price = std::stod(priceStr, &pos);
        if (pos != priceStr.size())
            return false;
        return true;
    }
}

bool CSVReader::validateDate(std::string& dateStr)
{
    if (dateStr[4] != '-')
        return false;
    int year, month, day;
    if (getIntValue(dateStr, 0, 4, year) == false)
        return false;
    std::size_t delimiterPos = dateStr.find('-', 5);
    if (delimiterPos == std::string::npos || getIntValue(dateStr, 5, delimiterPos, month) == false)
        return false;
    int dayPartLenth = dateStr.size() - (delimiterPos + 1);
    if ((dayPartLenth < 1 || dayPartLenth > 2)
        || dateStr.find('-', delimiterPos + 1) != std::string::npos
        || getIntValue(dateStr, delimiterPos + 1, dateStr.size(), day) == false)
        return false;

    if (month < 1 || month > 12)
        return false;

    int daysInMonth[] = { 0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };

    bool leapYear = (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
    if (month == 2 && leapYear)
        daysInMonth[2] = 29;

    return (day >= 1 && day <= daysInMonth[month]);
}

std::string CSVReader::trim(std::string str)
{
    auto notSpace = [](unsigned char c) { return !std::isspace(c); };

    str.erase(str.begin(), std::find_if(str.begin(), str.end(), notSpace));
    str.erase(std::find_if(str.rbegin(), str.rend(), notSpace).base(), str.end());

    return str;
}

std::pair<std::string, double> CSVReader::splitLine(std::string& line)
{
    std::size_t commaPos = line.find(',');
    if (commaPos == std::string::npos || line.find(commaPos+1, ',') != std::string::npos)
        throw std::invalid_argument("invalid data in line");
    std::string date = trim(line.substr(0, commaPos));
    std::string priceStr  = trim(line.substr(commaPos+1));
    if (!validateDate(date))
        throw std::invalid_argument("invalid date in line");
    double price;
    if (!getDoubleValue(priceStr, price))
        throw std::invalid_argument("invalid price in line");

    return std::make_pair(date, price);
}

std::map<std::string, double> CSVReader::loadPricesCSV(const std::string& fileName)
{
	std::ifstream file(fileName);
	if (!file.is_open())
	{
		throw std::runtime_error("cannot open file");
	}

	std::map<std::string, double> prices;
	std::string line;
    std::size_t lineCount = 1;
	std::getline(file, line);
	while (std::getline(file, line))
	{
        try {
            ++lineCount;
		    std::pair<std::string, double> date_price = splitLine(line);
            prices[date_price.first] = date_price.second;
        }
        catch (const std::invalid_argument& ex) {
            std::cerr << "Error: " << ex.what() << ". Line "
                << lineCount << ": " << line << std::endl;
        }
	}
	
	return prices;
}

