#include "RPN.hpp"

int main(int argc, char *argv[])
{
	if (argc != 2)
	{
		std::cerr << RED << "Usage: " << argv[0] << " < RPN >" << RESET << std::endl;
		return 1;
	}

	RPN r;
	std::cout << r.calcRPN(argv[1]) << std::endl;
	return 0;
}

__attribute((destructor))
static void destructor() {
	system("leaks -q RPN");
}
