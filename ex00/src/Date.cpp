#include "Date.hpp"
#include "Utils.hpp"
#include <iostream>
#include <cstdlib>
#include <sstream>

// Orthodox canonical form
Date::Date() : year(1970), month(1), day(1) {}

Date::Date(const Date &other) : year(other.year), month(other.month), day(other.day) {}

Date& Date::operator=(const Date &other) {
    if (this != &other) {
        year = other.year;
        month = other.month;
        day = other.day;
    }
    return *this;
}

Date::~Date() throw() {}

// Constructor
Date::Date(const std::string &date_str) {
    // format is yyyy-mm-dd
    if (date_str.length() != 10) {
        std::cerr << "Invalid date format: " << date_str << std::endl;
        throw Date::Exception("Invalid date format: " + date_str);
    }
    if (date_str[4] != '-' || date_str[7] != '-') {
        std::cerr << "Invalid date format: " << date_str << std::endl;
        throw Date::Exception("Invalid date format: " + date_str);
    }
    std::string year_str = date_str.substr(0, 4);
    std::string month_str = date_str.substr(5, 2);
    std::string day_str = date_str.substr(8, 2);
    if (!isDigit(year_str) || !isDigit(month_str) || !isDigit(day_str)) {
        std::cerr << "Invalid format: " << date_str << std::endl;
        throw Date::Exception("Invalid date format: " + date_str);
    }
    year = std::atoi(year_str.c_str());
    month = std::atoi(month_str.c_str());
    day = std::atoi(day_str.c_str());
    _validate();
}

// private functions
bool Date::_isLeapYear() {
    if (year % 4 == 0) {
        if (year % 100 == 0 && year % 400 != 0) {
            return false;
        }
        return true;
    }
    return false;
}

int Date::_getDaysInMonth() {
    switch (month) {
        case 2:
            return _isLeapYear() ? 29: 28;
        case 4:
        case 6:
        case 9:
        case 11:
            return 30;
        default:
            return 31;
    }
}

void Date::_validate() {
    if (year < 0 || year > 3000) {
        std::ostringstream oss;
        oss << "This year is out of range: " << year;
        std::cerr << oss.str() << std::endl;
        throw Exception(oss.str());
    }
    if (month < 1 || month > 12) {
        std::ostringstream oss;
        oss << "This month is out of range: " << month;
        std::cerr << oss.str() << std::endl;
        throw Exception(oss.str());
    }
    if (day < 1 || day > 31) {
        std::ostringstream oss;
        oss << "This day is out of range: " << day;
        std::cerr << oss.str() << std::endl;
        throw Exception(oss.str());
    }
    if (day > _getDaysInMonth()) {
        std::ostringstream oss;
        oss << "This day is out of range: " << day;
        std::cerr << oss.str() << std::endl;
        throw Exception(oss.str());
    }
}

// Exception
Date::Exception::Exception(const std::string &msg): _msg(msg) {}

Date::Exception::Exception(const Exception &other): _msg(other._msg) {}

Date::Exception& Date::Exception::operator=(const Exception &other) {
    if (this != &other) {
        _msg = other._msg;
    }
    return *this;
}

Date::Exception::~Exception() throw() {}

const char* Date::Exception::what() const throw() {
    return _msg.c_str();
}
