#pragma once

#include <string>
#include <map>

class CSVReader
{
    CSVReader() = delete;
    CSVReader(const CSVReader& other) = delete;
    CSVReader& operator=(const CSVReader& other) = delete;
    ~CSVReader() = delete;

    static std::pair<std::string, double> splitLine(std::string& line);
    static std::string trim(std::string str);
    static bool validateDate(std::string& dateStr);

    public:
        static std::map<std::string, double> loadPricesCSV(const std::string& fileName);
        
};
