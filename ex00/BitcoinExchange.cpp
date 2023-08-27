#include "BitcoinExchange.hpp"

/* Orthodox Canonical Form */
BitcoinExchange::BitcoinExchange()
{
	std::cout << "(BitcoinExchange) Default Constructor called" << std::endl;
}

BitcoinExchange::BitcoinExchange()
{
	std::cout << "(BitcoinExchange) Constructor called" << std::endl;
}

BitcoinExchange::BitcoinExchange(const BitcoinExchange& rhs)
{
	std::cout << "(BitcoinExchange) Copy Constructor called"  << std::endl;
}

BitcoinExchange::~BitcoinExchange()
{
	std::cout << "(BitcoinExchange) Destructor called" << std::endl;
}

BitcoinExchange& BitcoinExchange::operator=(const BitcoinExchange& rhs)
{
	std::cout << "(BitcoinExchange) Copy assignment operator called" << std::endl;
	if (this == &rhs)
		return *this;

	return *this;
}

/* Function */
