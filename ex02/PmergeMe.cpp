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
void PmergeMe::mergeInsertionSort(std::vector<int>& arr)
{
    size_t n = arr.size();
    if (n <= 1) return;
    #ifdef DEBUG
        comparisonCount ++;
    #endif

    std::vector<int> larger, smaller;

    // Step 1 and Step 2: Pairing and finding larger and smaller elements
    for (size_t i = 0; i < n; i += 2) {
        if (i + 1 < n)
        {
            #ifdef DEBUG
                comparisonCount++;
            #endif
            larger.push_back(std::max(arr[i], arr[i + 1]));
            smaller.push_back(std::min(arr[i], arr[i + 1]));
        } else {
            larger.push_back(arr[i]);
        }
    }

    // Step 3: Recursively sort the larger elements
    mergeInsertionSort(larger);

    // Step 4: Find the corresponding smaller element for the smallest larger element
    int smallest_larger = larger[0];
    int corresponding_smaller = -1;
    for (size_t i = 0; i < n; i += 2) {
        if (i + 1 < n) {
            if (arr[i] == smallest_larger || arr[i + 1] == smallest_larger) {
                corresponding_smaller = std::min(arr[i], arr[i + 1]);
                break;
            }
        }
    }

    // Clear the original array and populate it with sorted larger elements
    arr.clear();
    arr = larger;

    if (corresponding_smaller != -1) {
        arr.insert(arr.begin(), corresponding_smaller);
    }

    // Step 5: Insert the remaining smaller elements
    for (size_t i = 0; i < smaller.size(); ++i) {
        if (smaller[i] != corresponding_smaller) {
            std::vector<int>::iterator it = std::lower_bound(arr.begin(), arr.end(), smaller[i]);
        #ifdef DEBUG
            // comparisonCount += std::log2(arr.size());
            comparisonCount += static_cast<int>(std::log(static_cast<double>(arr.size())) / std::log(2.0));
        #endif
            arr.insert(it, smaller[i]);
        }
    }
}


	// std::cout << "------" << std::endl;
	// for (std::vector<int>::iterator it = arr.begin(); it != arr.end(); it++)
	// {
	// 	std::cout << GREEN << *it << RESET << std::endl;
	// }
	// std::cout << BLUE << corresponding_smaller << RESET << std::endl;
    // Insert the corresponding smaller element if it exists
//./PmergeMe 9 3 7 4 8 2 6 5
//./PmergeMe 8 1 6 3 7 2 5 4   (最悪ケース？)
