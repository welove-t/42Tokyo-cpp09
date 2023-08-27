#include "BitcoinExchange.hpp"

int main() {

	BitcoinExchange b;

	b.readDataCSV();

	std::map<std::string, double> myMap = b.getMapExchangeRates();
	for (std::map<std::string, double>::iterator it = myMap.begin();
			it !=  myMap.end(); it++)
	{
		std::cout << "Key: " << it->first << ", Value: " << it->second << std::endl;
	}
	return 0;
}


__attribute((destructor))
static void destructor() {
	system("leaks -q btc");
}
