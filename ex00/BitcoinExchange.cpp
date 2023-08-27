#include "BitcoinExchange.hpp"

/* Orthodox Canonical Form */
BitcoinExchange::BitcoinExchange()
{
	std::cout << "(BitcoinExchange) Default Constructor called" << std::endl;
}

// BitcoinExchange::BitcoinExchange(const BitcoinExchange& rhs)
// {
// 	std::cout << "(BitcoinExchange) Copy Constructor called"  << std::endl;
// }

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

std::map<std::string, double> BitcoinExchange::getMapExchangeRates(void) const
{
    return _mapExchangeRates;
}



/* Function */
void	BitcoinExchange::readDataCSV(void)
{
   std::ifstream file("data.csv"); // CSVファイルを開く

    if (file.is_open())
	{
        std::string line;
        std::getline(file, line); // ヘッダ行をスキップ

        while (std::getline(file, line))
		{
            std::istringstream lineStream(line);
            std::string date;
            std::string rateStr;
            double rate;

            std::getline(lineStream, date, ','); // 日付を読む
            std::getline(lineStream, rateStr);   // 為替レートを読む

            std::istringstream(rateStr) >> rate; // 為替レートをdoubleに変換

            _mapExchangeRates[date] = rate; // mapに格納
        }

        file.close();
    } else {
        std::cout << "Cannot open the file!" << std::endl;
    }
}

