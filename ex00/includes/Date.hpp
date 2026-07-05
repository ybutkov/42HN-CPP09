#pragma once

#include <string>
#include <ctime>


class Date {
private:
    int year;
    int month;
    int day;
    std::string rawDate;
    static constexpr const char* DATE_FORMAT = "%Y-%m-%d";

    void _saveDateFromTM(const std::tm& datetime);

public:
    Date();
    Date(const std::string& dateStr);
    Date(const Date& other) = default;
    Date& operator=(const Date& other) = default;
    ~Date() = default;

    std::string toString() const;
    bool operator<(const Date& other) const;

};
