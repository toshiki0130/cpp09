#include "BitcoinExchange.hpp"
#include "Utils.hpp"
#include "Date.hpp"
#include <fstream>
#include <iostream>

// Orthodox canonical form
BitcoinExchange::BitcoinExchange() {}

BitcoinExchange::BitcoinExchange(const BitcoinExchange &other) : m_bitcoinPrices(other.m_bitcoinPrices){}

BitcoinExchange &BitcoinExchange::operator=(const BitcoinExchange &other) {
    if (this != &other) {
        m_bitcoinPrices = other.m_bitcoinPrices;
    }
    return *this;
}

BitcoinExchange::~BitcoinExchange() throw() {}

// constructor
BitcoinExchange::BitcoinExchange(const std::string &filename) {
    std::ifstream file(filename.c_str());
    if (!file.is_open()) {
        std::cerr << "Error: cannot open file '" << filename << "'." << std::endl;
        throw Exception("Cannot open file" + filename);
    }
    std::string line;
    if (!std::getline(file, line)) {
        std::cerr << "Error: Cannot read header. File name: " << filename << "." << std::endl;
        throw Exception("Cannot read header. File name is " + filename);
    }
    if (line != "date,exchange_rate") {
        std::cerr << "Error: invalid header." << std::endl;
        throw Exception("Invalid header. File name is " + filename);
    }
    // parse data
    while (std::getline(file, line)) {
        size_t pos = line.find(',');
        if (pos == std::string::npos) {
            std::cerr << "Error: invalid line." << std::endl;
            throw Exception("Invalid format. File name is " + filename);
        }
        std::string date = line.substr(0, pos);
        std::string exchangeRate = line.substr(pos + 1);
        // dateの中身を確認する。
        try {
            Date d(date);
        }
        catch (Date::Exception &e) {
            std::cerr << "Invalid date: " << date << std::endl;
            throw Exception("Invalid date: " + date);
        }
        m_bitcoinPrices[date] = stringToDouble(exchangeRate);
    }
    file.close();
}

double BitcoinExchange::getRate(const std::string &date) const {
    std::map<std::string, double>::const_iterator it = m_bitcoinPrices.upper_bound(date);
    if (it == m_bitcoinPrices.begin()) {
        throw BitcoinExchange::Exception("Error: This date is not available: " + date + ".");
    } else {
        --it;
    }
    return it->second;
}

BitcoinExchange::Exception::Exception(const std::string &msg): _msg(msg) {}

BitcoinExchange::Exception::Exception(const BitcoinExchange::Exception &other): _msg(other._msg) {}

BitcoinExchange::Exception& BitcoinExchange::Exception::operator=(const BitcoinExchange::Exception &other) {
    if (this != &other) {
        _msg = other._msg;
    }
    return *this;
}

BitcoinExchange::Exception::~Exception() throw () {}
const char* BitcoinExchange::Exception::what() const throw() {
    return _msg.c_str();
}