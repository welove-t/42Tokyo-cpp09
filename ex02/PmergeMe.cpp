#include "PmergeMe.hpp"

/* Orthodox Canonical Form */
PmergeMe::PmergeMe()
{
	// std::cout << "(PmergeMe) Default Constructor called" << std::endl;
}

PmergeMe::PmergeMe(const PmergeMe& rhs)
{
	(void)rhs;
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
	return *this;
}

/* Function */
void PmergeMe::mergeInsertionSort(std::vector<int>& arr) {
    size_t n = arr.size();
    if (n <= 1) return;

    std::vector<int> larger, smaller;

    // Step 1 and Step 2
    for (size_t i = 0; i < n; i += 2) {
        if (i + 1 < n) {
            larger.push_back(std::max(arr[i], arr[i + 1]));
            smaller.push_back(std::min(arr[i], arr[i + 1]));
        } else {
            larger.push_back(arr[i]);
        }
    }

    // Step 3
    mergeInsertionSort(larger);

    // Step 4
    arr.clear();
    arr = larger;

    for (size_t i = 0; i < smaller.size(); ++i) {
        std::vector<int>::iterator it = std::lower_bound(arr.begin(), arr.end(), smaller[i]);
        arr.insert(it, smaller[i]);
    }
}
