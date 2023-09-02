#ifndef PMERGEME_HPP
#define PMERGEME_HPP

#include <iostream>
#include <iomanip>
#include <vector>
#include <algorithm>
#include <cstdlib>
#include <ctime>
#include <cmath>

#define RED		"\e[0;31m" // Red
#define GREEN	"\e[0;32m" // Green
#define YELLOW	"\e[0;33m" // Yellow
#define BLUE	"\e[0;34m" // Blue
#define RESET 	"\e[0m"    // Reset

#ifdef DEBUG
extern int comparisonCount;
#endif
class PmergeMe
{
	private:
		// std::stack<int> _stk;

	public:
		PmergeMe();
		~PmergeMe();

		PmergeMe(const PmergeMe& rhs);
		PmergeMe& operator=(const PmergeMe& rhs);

		bool	isValid(int argc, char *argv[]);
		void	mergeInsertionSort(std::vector<int>& arr);

};


#endif
