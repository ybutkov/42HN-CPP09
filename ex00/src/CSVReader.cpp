#include "CSVReader.hpp"
#include <fstream>
#include <iostream>
#include <stdexcept>


CSVReader::CSVReader(const std::string& fileName,
        std::string_view separator,
        bool hasHeader,
        std::initializer_list<std::string> header_fields)
    :   file(fileName),
        separator(separator),
        hasHeader(hasHeader),
        header_fields(header_fields)
{
    if (!this->file.is_open()) {
        throw std::runtime_error("could not open file " + fileName + ".");
    }
    if (!this->_checkHeader())
    {
        throw std::runtime_error("header is wrong for " + fileName + ".");
    }
}

bool CSVReader::isOpen() const
{
    return file.is_open();
}

bool CSVReader::readRow(std::list<std::string>& row)
{
    row.clear();
    
    std::string line;
    if (!std::getline(this->file, line)) {
        return false;
    }

    std::string::size_type start = 0;
    std::string::size_type end = line.find(separator);

    while (end != std::string::npos) {
        row.push_back(line.substr(start, end - start));
        start = end + separator.length();
        end = line.find(separator, start);
    }
    row.push_back(line.substr(start));

    return true;
}

bool CSVReader::_checkHeader()
{
    if (!this->hasHeader)
        return true;

    std::list<std::string> actualHeader;
    if (!this->readRow(actualHeader))
        return false;

    return (actualHeader == this->header_fields);
}

bool CSVReader::hasCSVHeader() const
{
    return this->hasHeader;
}
