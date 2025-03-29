#include <iostream>
#include <fstream>
#include <cstdlib>
#include "BitcoinExchange.hpp"
#include "Utils.hpp"
#include "Date.hpp"

#define BITCOIN_CHART_FILE "./src/data.csv"

void run(const BitcoinExchange &bitcoinExchange, std::ifstream &file);

int main(int argc, char **argv)
{
   if (argc != 2) {
	   std::cerr << "Usage: " << argv[0] << " <file>" << std::endl;
	return EXIT_FAILURE;
   }
   // read input file
   std::ifstream file;
   file.open(argv[1]);
   if (!file) {
	   std::cerr << "Error: cannot open file '" << argv[1] << "'." << std::endl;
      return EXIT_FAILURE;
   }
   // process input file
   try {
      BitcoinExchange bitcoinExchange(BITCOIN_CHART_FILE);
      run(bitcoinExchange, file);
   }
   catch (const BitcoinExchange::Exception &e) {
      std::cerr << "Error: " << e.what() << std::endl;
      return EXIT_FAILURE;
   }

   return EXIT_SUCCESS;
}

void parseLine(const std::string &line, std::string &date, float &value) {
   size_t pos = line.find(" | ");
   if (pos == std::string::npos) {
      throw BitcoinExchange::Exception("Error: Invalid line: " + line);
   }
   date = line.substr(0, pos);
   try {
      Date d(date);
   }
   catch (Date::Exception &e) {
      throw BitcoinExchange::Exception(e.what());
   }
   std::string value_str = line.substr(pos + 3);
   value = stringToDouble(value_str);
   if (value < 0 || value > 1000) {
      throw BitcoinExchange::Exception("Error: value must be between 1 and 1000: " + value_str + ".");
   }
}


void run(const BitcoinExchange &bitcoinExchange, std::ifstream &file) {
   std::string line;
   if (!std::getline(file, line)) {
      std::cerr << "Error: Could not read header." << std::endl;
      throw BitcoinExchange::Exception("Could not read header.");
   }
   if (line != "date | value") {
      std::cerr << "Error: Invalid header." << std::endl;
      throw BitcoinExchange::Exception("Invalid header");
   }
   // parse data
   while (std::getline(file, line)) {
      std::string date;
      float value;
      try {
         parseLine(line, date, value);
         double rate = bitcoinExchange.getRate(date);
         std::cout << "Date: " << date << " => " << value << " => " << value * rate << std::endl;
      }
      catch (BitcoinExchange::Exception &e) {
         std::cerr << e.what() << std::endl;
      }
   }
}
