#include "PmergeMe.hpp"

/* Orthodox Canonical Form */
PmergeMe::PmergeMe()
{
	// std::cout << "(PmergeMe) Default Constructor called" << std::endl;
}

PmergeMe::PmergeMe(const PmergeMe& rhs) : _stk(rhs._stk)
{
	// std::cout << "(PmergeMe) Copy Constructor called"  << std::endl;
}

PmergeMe::~PmergeMe()
{
	// std::cout << "(PmergeMe) Destructor called" << std::endl;
}

PmergeMe& PmergeMe::operator=(const PmergeMe& rhs)
{
	// std::cout << "(PmergeMe) Copy assignment operator called" << std::endl;
	if (this == &rhs)
		return *this;
	_stk = rhs._stk;
	return *this;
}

/* Function */
