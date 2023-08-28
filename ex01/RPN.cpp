#include "RPN.hpp"

/* Orthodox Canonical Form */
RPN::RPN()
{
	std::cout << "(RPN) Default Constructor called" << std::endl;
}

RPN::RPN(const RPN& rhs) : _stk(rhs._stk)
{
	std::cout << "(RPN) Copy Constructor called"  << std::endl;
}

RPN::~RPN()
{
	std::cout << "(RPN) Destructor called" << std::endl;
}

RPN& RPN::operator=(const RPN& rhs)
{
	std::cout << "(RPN) Copy assignment operator called" << std::endl;
	if (this == &rhs)
		return *this;
	_stk = rhs._stk;
	return *this;
}

/* Function */
