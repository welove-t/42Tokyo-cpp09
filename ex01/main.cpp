#include "RPN.hpp"

int main(int argc, char *argv[])
{

	return 0;
}


__attribute((destructor))
static void destructor() {
	system("leaks -q btc");
}
