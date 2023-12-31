#include "BitcoinExchange.hpp"

/* Orthodox Canonical Form */
BitcoinExchange::BitcoinExchange()
{
	// std::cout << "(BitcoinExchange) Default Constructor called" << std::endl;
}

BitcoinExchange::BitcoinExchange(const BitcoinExchange& rhs)
: _mapExchangeRates(rhs._mapExchangeRates)
{
	// std::cout << "(BitcoinExchange) Copy Constructor called"  << std::endl;
}

BitcoinExchange::~BitcoinExchange()
{
	// std::cout << "(BitcoinExchange) Destructor called" << std::endl;
}

BitcoinExchange& BitcoinExchange::operator=(const BitcoinExchange& rhs)
{
	// std::cout << "(BitcoinExchange) Copy assignment operator called" << std::endl;
	if (this == &rhs)
		return *this;
	_mapExchangeRates = rhs._mapExchangeRates;
	return *this;
}

std::map<std::string, double> BitcoinExchange::getMapExchangeRates(void) const
{
	return _mapExchangeRates;
}

/* Function */
void	BitcoinExchange::readDataCSV(void)
{
   std::ifstream file(csvFileName);

	if (!isOpenFile(file, csvFileName))
		return ;
	std::string line;
	std::getline(file, line); // header skip

	while (std::getline(file, line))
	{
		std::istringstream lineStream(line);
		std::string date;
		std::string rateStr;
		double rate;

		std::getline(lineStream, date, ','); // date
		std::getline(lineStream, rateStr);   // rate

		std::istringstream(rateStr) >> rate; //

		_mapExchangeRates[date] = rate; // set map[date] = rate
	}
	file.close();
}

bool	BitcoinExchange::isOpenFile(std::ifstream& input , const std::string& fileName) const
{
	if (!input.is_open())
	{
		std::cerr << RED << "Failed to open " << RESET << std::endl;
		return false;
	}

	std::ifstream bigFile(fileName, std::ifstream::ate | std::ifstream::binary);
	std::ifstream::pos_type fileSize = bigFile.tellg();
	const std::ifstream::pos_type maxSize = 10000000; // 10MG
	if (fileSize > maxSize)
	{
		std::cerr << RED << fileName << " is too large!" << RESET << std::endl;
		input.close();
		bigFile.close();
		return false;
	}
	bigFile.close();
	return true;
}

void	BitcoinExchange::readDataTXT(const std::string& fileName)
{
	std::ifstream file(fileName);

	if (!isOpenFile(file, fileName))
		return ;
	std::string line;
	std::getline(file, line); // header skip

	while (std::getline(file, line))
	{
		if (!isValidLine(line))
			continue;
		std::istringstream lineStream(line);
		std::string date;
		std::string rateStr;
		double rate;
		std::getline(lineStream, date, '|');	// date
		std::getline(lineStream, rateStr);		// rate
		if (!isValidDate(date))
			continue;
		if (!isValidRate(rateStr, &rate))
			continue;
		printBitcoin(date, rateStr, rate);
	}
	file.close();
}

void	BitcoinExchange::printBitcoin(const std::string& date, const std::string& rateStr, double rate)
{
	double dbRate = getRate(date);

	if (dbRate < 0)
		return ;
	dbRate *= rate;
	std::cout << date << " => " << rateStr << " = " << dbRate << std::endl;
}

double	BitcoinExchange::getRate(std::string date)
{
	std::map<std::string, double>::const_iterator it = _mapExchangeRates.upper_bound(date);
	if (it == _mapExchangeRates.begin()) {
		std::cout << RED << "Error: no available rate for the given date or earlier." << RESET << std::endl;
		return -1.0;
	}
	--it;
	return it->second;
}

bool	BitcoinExchange::isValidLine(const std::string& line) const
{
	try
	{
		if (line.empty())
			return false;
		if (line.find('|') == std::string::npos)
			throw std::logic_error("bad input => " + line);
	}
	catch (std::logic_error &e)
	{
		std::cerr << RED <<"Error: " << e.what() << RESET << std::endl;
		return false;
	}
	return true;
}

bool	BitcoinExchange::isLeapYear(int year) const
{
	return (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
}

bool	BitcoinExchange::isValidDate(const std::string& date) const
{
	try
	{
		if (date.size() != 11)
			throw std::logic_error("bad input => " + date);
		for (int i = 0; i < 10; i++)
		{
			if (i == 4 || i == 7)
			{
				if (date[i] != '-' || date[i] != '-')
					throw std::logic_error("bad input => " + date);
			}
			else
			{
				if (!std::isdigit(date[i]))
					throw std::logic_error("bad input => " + date);
			}
		}
		int year, month, day;
		std::istringstream issYear(date.substr(0, 4));
		std::istringstream issMonth(date.substr(5, 2));
		std::istringstream issDay(date.substr(8, 2));

		issYear >> year;
		issMonth >> month;
		issDay >> day;

		int daysInMonth[] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
		if (isLeapYear(year))
			daysInMonth[2] = 29;
		if (day > daysInMonth[month])
			throw std::logic_error("bad input => " + date);
	}
	catch (std::logic_error &e)
	{
		std::cerr << RED <<"Error: " << e.what() << RESET << std::endl;
		return false;
	}
	return true;
}

bool	BitcoinExchange::isValidRate(const std::string& rateStr, double *rate) const
{
	std::istringstream iss(rateStr);

	try
	{
		if (!(iss >> *rate))
			throw std::logic_error("not a number");
		if (*rate < 0)
			throw std::logic_error("not a positive number.");
		if (*rate > 1000)
			throw std::logic_error("too large a number.");
	}
	catch (std::logic_error &e)
	{
		std::cerr << RED <<"Error: " << e.what() << RESET << std::endl;
		return false;
	}
	return true;
}


