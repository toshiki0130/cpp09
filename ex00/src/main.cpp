#include <iostream>
#include <fstream>
#include <cstdlib>
#include "BitcoinExchange.hpp"
#include "Utils.hpp"

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
   }
   // process input file
   BitcoinExchange bitcoinExchange("data.csv");
   run(bitcoinExchange, file);

   return EXIT_SUCCESS;
}

void parseLine(const std::string &line, std::string &date, double &value) {
   size_t pos = line.find('|');
   if (pos == std::string::npos) {
      std::cerr << "Error: Invalid line." << std::endl;
   }
   date = line.substr(0, pos);
   std::string valueStr = line.substr(pos + 1);
   value = stringToDouble(valueStr);
   if (value < 0 || value > 1000) {
      std::cerr << "Error: Invalid value." << std::endl;
   }
}


void run(const BitcoinExchange &bitcoinExchange, std::ifstream &file) {
   std::string line;
   if (!std::getline(file, line)) {
      std::cerr << "Error: Could not read header." << std::endl;
   }
   if (line != "date | value") {
      std::cerr << "Error: Invalid header." << std::endl;
   }
   // parse data
   while (std::getline(file, line)) {
      std::string date;
      double value;
      parseLine(line, date, value);
      double rate = bitcoinExchange.getRate(date);
      std::cout << "Date: " << date << " => " << value << " => " << value * rate << std::endl;
   }
}