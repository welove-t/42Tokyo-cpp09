#include "BitcoinExchange.hpp"

int main() {

	return 0;
}


__attribute((destructor))
static void destructor() {
	system("leaks -q main");
}
