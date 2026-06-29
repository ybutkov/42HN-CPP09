#include "Date.hpp"
#include <ctime>


Date::Date()
{
    std::time_t t = std::time(nullptr);
    std::tm* now = std::localtime(&t);
    this->_saveDateFromTM(*now);
}

Date::Date(const std::string& dateStr) : rawDate(dateStr)
{
    if (dateStr.size() != 10 || dateStr[4] != '-' || dateStr[7] != '-')
        throw std::invalid_argument("Invalid date format");
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
    
    int beforeDay = dt.tm_mday;
    int beforeMon = dt.tm_mon;
    int beforeYear = dt.tm_year;

    dt.tm_hour = 0;
    dt.tm_min = 0;
    dt.tm_sec = 0;
    dt.tm_isdst = -1;

    if (std::mktime(&dt) == -1 ||
        dt.tm_mday != beforeDay ||
        dt.tm_mon != beforeMon ||
        dt.tm_year != beforeYear) {
        throw std::invalid_argument("Date does not exist");
    }
    this->_saveDateFromTM(dt);
}

bool Date::operator<(const Date& other) const
{
    return std::tie(this->year, this->month, this->day) 
        < std::tie(other.year, other.month, other.day);

}

std::string Date::toString() const
{
    char buf[11];
    
    std::snprintf(buf, sizeof(buf), this->DATE_FORMAT_PRINT, year, month, day);
    
    return std::string(buf);
}

void Date::_saveDateFromTM(std::tm& datetime)
{
    this->year = datetime.tm_year + 1900;
    this->month = datetime.tm_mon + 1;
    this->day = datetime.tm_mday;    
}
