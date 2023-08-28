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

    if (!checkOpenFile(file))
        return ;
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
}

bool	BitcoinExchange::checkOpenFile(std::ifstream& input) const
{
    if (!input.is_open()) {
        std::cerr << RED << "Failed to open " << RESET << std::endl;
        return false;
    }
	return true;
}

void	BitcoinExchange::readDataTXT(const std::string& fileName)
{
   std::ifstream file(fileName); // TXTファイルを開く

    if (!checkOpenFile(file))
        return ;
    std::string line;
    std::getline(file, line); // ヘッダ行をスキップ

    while (std::getline(file, line))
    {
        std::istringstream lineStream(line);
        std::string date;
        std::string rateStr;
        double rate;

        std::getline(lineStream, date, '|'); // 日付を読む
        std::getline(lineStream, rateStr);   // 為替レートを読む
        std::istringstream(rateStr) >> rate; // 為替レートをdoubleに変換
        printBitcoin(date, rate);
    }
    file.close();
}

void	BitcoinExchange::printBitcoin(std::string date, double rate)
{

    std::cout << date << " => " << rate << std::endl;
}
