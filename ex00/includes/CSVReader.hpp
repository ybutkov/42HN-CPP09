#pragma once

#include <fstream>
#include <string>
#include <map>
#include <initializer_list>
#include <list>


class CSVReader
{
    std::ifstream file;
    std::string   separator;
    bool          hasHeader;
    std::list<std::string> header_fields;

    bool _checkHeader();
public:
    CSVReader() = delete;

    CSVReader(const std::string& fileName,
                std::string_view separator = ",",
                bool hasHeader=false,
                std::initializer_list<std::string> header_fields={});

    CSVReader(const CSVReader& other) = delete;
    CSVReader& operator=(const CSVReader& other) = delete;

    ~CSVReader() = default;

    bool isOpen() const;
    bool readRow(std::list<std::string>& row);
    bool hasCSVHeader() const;
};
