#ifndef BITCOINEXCHANGE_HPP
#define BITCOINEXCHANGE_HPP

#include <map>
#include <string>

class BitcoinExchange {
private:
    std::map <std::string, double> m_bitcoinPrices;
    
public:
    // Orthodox Canonical Form
    BitcoinExchange();
    BitcoinExchange(const BitcoinExchange &other);
    BitcoinExchange &operator=(const BitcoinExchange &other);
    ~BitcoinExchange();
    // constructor
    explicit BitcoinExchange(const std::string &filename);
    double getRate(const std::string &date) const;
};

#endif // BITCOINEXCHANGE_HPP