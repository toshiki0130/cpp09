#include "BitcoinExchange.hpp"
#include "Utils.hpp"
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

BitcoinExchange::~BitcoinExchange() {}

// constructor
BitcoinExchange::BitcoinExchange(const std::string &filename) {
    std::ifstream file(filename.c_str());
    if (!file.is_open()) {
        std::cerr << "Error: cannot open file '" << filename << "'." << std::endl;
    }
    std::string line;
    std::getline(file, line);
    if (line != "date,exchange_rate") {
        std::cerr << "Error: invalid header." << std::endl;
    }
    // parse data
    while (std::getline(file, line)) {
        size_t pos = line.find(',');
        if (pos == std::string::npos) {
            std::cerr << "Error: invalid line." << std::endl;
        }
        std::string date = line.substr(0, pos);
        std::string exchangeRate = line.substr(pos + 1);
        m_bitcoinPrices[date] = stringToDouble(exchangeRate);
    }
    file.close();
}

double BitcoinExchange::getRate(const std::string &date) const {
    std::map<std::string, double>::const_iterator it = m_bitcoinPrices.upper_bound(date);
    if (it == m_bitcoinPrices.begin()) {
        std::cerr << "Error: no data available for date '" << date << "'." << std::endl;
    } else {
        --it;
    }
    return it->second;
}