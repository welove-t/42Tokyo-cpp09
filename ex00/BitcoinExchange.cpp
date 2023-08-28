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
    double anserRate = rate * getRate(date);
    std::cout << date << " => " << anserRate << std::endl;
}

double	BitcoinExchange::getRate(std::string date)
{
    std::map<std::string, double>::const_iterator it = _mapExchangeRates.upper_bound(date);
    // upper_bound は指定したキーよりも大きい最初の要素を返します。
    // なので、その1つ前が指定された日付またはそれに最も近い日付です。
    if (it == _mapExchangeRates.begin()) {
        // 指定された日付より前のデータが一つもない場合はエラー（または適当な値）を返します。
        std::cout << "No available rate for the given date or earlier.\n";
        return -1.0;  // ここで適当なエラー値を返しています。
    }

    --it;  // 直近の日付の要素を指すようにします。
    return it->second;  // その日付の為替レートを返します。
}
