#include "BitcoinExchange.hpp"

int main(int argc, char *argv[]) {

	BitcoinExchange b;

	if (argc != 2)
	{
		std::cerr << RED << "Usage: " << argv[0] << " <filename>" << RESET << std::endl;
		return 1;
	}
	b.readDataCSV();
	std::map<std::string, double> myCsv = b.getMapExchangeRates();
	for (std::map<std::string, double>::iterator it = myCsv.begin();
			it !=  myCsv.end(); it++)
	{
		std::cout << "Key: " << it->first << ", Value: " << it->second << std::endl;
	}

	b.readDataTXT(argv[1]);
	return 0;
}


__attribute((destructor))
static void destructor() {
	system("leaks -q btc");
}
