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
    ~BitcoinExchange() throw();
    // constructor
    explicit BitcoinExchange(const std::string &filename);
    // member functions
    double getRate(const std::string &date) const;
    
    class  Exception : public std::exception {
    public:
        explicit Exception(const std::string &msg);
        Exception(const Exception &other);
        Exception &operator=(const Exception &other);
        ~Exception() throw();
        const char* what() const throw();
    private:
        std::string _msg;
    };
};

#endif
