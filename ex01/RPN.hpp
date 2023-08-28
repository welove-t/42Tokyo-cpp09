#ifndef RPN_HPP
#define RPN_HPP

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <stdexcept>
#include <stack>

#define RED		"\e[0;31m" // Red
#define GREEN	"\e[0;32m" // Green
#define YELLOW	"\e[0;33m" // Yellow
#define BLUE	"\e[0;34m" // Blue
#define RESET 	"\e[0m"    // Reset

class RPN
{
	private:
		std::stack<int> _stk;

	public:
		RPN();
		~RPN();

		RPN(const RPN& rhs);
		RPN& operator=(const RPN& rhs);

};


#endif
