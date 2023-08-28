#ifndef BITCOINEXCHANGE_HPP
#define BITCOINEXCHANGE_HPP

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <stdexcept>
#include <map>

#define RED		"\e[0;31m" // Red
#define GREEN	"\e[0;32m" // Green
#define YELLOW	"\e[0;33m" // Yellow
#define BLUE	"\e[0;34m" // Blue
#define RESET 	"\e[0m"    // Reset

class BitcoinExchange
{
	private:
		std::map<std::string, double> _mapExchangeRates;

	public:
		BitcoinExchange();
		~BitcoinExchange();

		BitcoinExchange(const BitcoinExchange& rhs);
		BitcoinExchange& operator=(const BitcoinExchange& rhs);

		std::map<std::string, double> getMapExchangeRates(void) const;
		std::map<std::string, double> getMapInputData(void) const;

		void	readDataCSV(void);
		void	readDataTXT(const std::string& fileName);
		bool	checkOpenFile(std::ifstream& input) const;
		void	printBitcoin(std::string date, double rate);
		double	getRate(std::string date);

		bool	isValidDate(const std::string& date);
		bool	isLeapYear(int year);
		bool	is_validate_rate(const std::string& rateStr, double *rate);
};


#endif
