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
   std::ifstream file(csvFileName); // CSVファイルを開く

	if (!isOpenFile(file, csvFileName))
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

bool	BitcoinExchange::isOpenFile(std::ifstream& input , const std::string& fileName) const
{
	if (!input.is_open()) {
		std::cerr << RED << "Failed to open " << RESET << std::endl;
		return false;
	}
	// ファイルサイズを取得
	std::ifstream bigFile(fileName, std::ifstream::ate | std::ifstream::binary);
    std::ifstream::pos_type fileSize = bigFile.tellg();

	// サイズが一定の閾値より大きい場合はエラーとする
    const std::ifstream::pos_type maxSize = 10000000; // 10MGとする
    if (fileSize > maxSize) {
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
   std::ifstream file(fileName); // TXTファイルを開く

	if (!isOpenFile(file, fileName))
		return ;
	std::string line;
	std::getline(file, line); // ヘッダ行をスキップ

	while (std::getline(file, line))
	{
		if (!isValidLine(line))
			continue;
		std::istringstream lineStream(line);
		std::string date;
		std::string rateStr;
		double rate;
		std::getline(lineStream, date, '|'); // 日付を読む
		std::getline(lineStream, rateStr);   // 為替レートを読む
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
	// upper_bound は指定したキーよりも大きい最初の要素を返します。
	// なので、その1つ前が指定された日付またはそれに最も近い日付です。
	if (it == _mapExchangeRates.begin()) {
		// 指定された日付より前のデータが一つもない場合はエラー（または適当な値）を返します。
		std::cout << RED << "Error: no available rate for the given date or earlier." << RESET << std::endl;
		return -1.0;  // ここで適当なエラー値を返しています。
	}
	--it;  // 直近の日付の要素を指すようにします。
	return it->second;  // その日付の為替レートを返します。
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

bool BitcoinExchange::isLeapYear(int year) const
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
		if (!(iss >> *rate))             // 為替レートをdoubleに変換
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


