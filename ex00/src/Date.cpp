#include "Date.hpp"
#include <ctime>
#include <tuple>
#include <iomanip>
#include <sstream>
#include <stdexcept>


Date::Date()
{
    std::time_t t = std::time(nullptr);
    std::tm* now = std::localtime(&t);
    this->_saveDateFromTM(*now);
}

Date::Date(const std::string& dateStr) : rawDate(dateStr)
{
    std::tm dt = {};
    std::istringstream ss(dateStr);
    ss >> std::get_time(&dt, this->DATE_FORMAT);

    if (ss.fail()) {
        throw std::invalid_argument("Invalid date format");
    }
    char remaining;
    if (ss >> remaining) {
        throw std::invalid_argument("Invalid date format: extra characters at the end");
    }
    
    dt.tm_isdst = -1;
    if (std::mktime(&dt) == -1)
        throw std::invalid_argument("Date does not exist");

    char buf[11];
    std::strftime(buf, sizeof(buf), "%Y-%m-%d", &dt);
    
    if (dateStr != buf)
        throw std::invalid_argument("Date does not exist");

    this->_saveDateFromTM(dt);
}

bool Date::operator<(const Date& other) const
{
    return std::tie(this->year, this->month, this->day) 
        < std::tie(other.year, other.month, other.day);

}

std::string Date::toString() const
{
    std::ostringstream oss;

    oss << std::setfill('0')
        << std::setw(4) << year << '-'
        << std::setw(2) << month << '-'
        << std::setw(2) << day;

    return oss.str();
}

void Date::_saveDateFromTM(const std::tm& datetime)
{
    this->year = datetime.tm_year + 1900;
    this->month = datetime.tm_mon + 1;
    this->day = datetime.tm_mday;    
}
