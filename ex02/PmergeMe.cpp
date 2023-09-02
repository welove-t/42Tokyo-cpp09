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
bool isDuplicate(int num, int arr[], int size)
{
    for (int i = 0; i < size; ++i)
	{
        if (arr[i] == num)
            return true;
    }
    return false;
}

bool	isNumber(char *arg)
{
	for (size_t j = 0; j < std::strlen(arg); ++j)
	{
		if (!std::isdigit(arg[j]))
			return true;
	}
	return false;
}

bool	PmergeMe::isValid(int argc, char *argv[])
{
	if (argc < 2)
	{
		std::cerr << RED << "Usage: " << argv[0] << " [num...]" << RESET << std::endl;
        return true;
	}
	int numbers[argc - 1]; // 重複チェック用
    int count = 0; // 配列内の有効な要素数

    for (int i = 1; i < argc; ++i)
	{
        char *arg = argv[i];

		if (isNumber(arg))
		{
			std::cerr << RED << "Error: Characters include." << RESET << std::endl;
			return true;
		}

        // 数値に変換
        long num = std::atol(arg);

		// 整数(正のint)チェック
		if (num > INT_MAX || num < 0)
		{
			std::cerr << RED << "only positive integer sequence as argument." << RESET << std::endl;
			return true;
		}

        // 重複チェック
        if (isDuplicate(num, numbers, count))
		{
            std::cerr << RED << "Error: There are duplicate numbers." << RESET << std::endl;
            return true;
        }

        numbers[count] = static_cast<int>(num);
        ++count;
	}
	return false;
}

void	PmergeMe::mergeInsertionSort(std::vector<int>& arr)
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

void	PmergeMe::mergeInsertionSort(std::list<int>& arr)
{
	size_t n = arr.size();
	if (n <= 1) return;
	#ifdef DEBUG
		comparisonCount ++;
	#endif

	std::list<int> larger, smaller;

	// Step 1 and Step 2: Pairing and finding larger and smaller elements
    std::list<int>::iterator it = arr.begin();
    for (size_t i = 0; i < n; i += 2) {
        if (i + 1 < n)
        {
            int first = *it++;
            int second = *it++;
            #ifdef DEBUG
                comparisonCount++;
            #endif
            larger.push_back(std::max(first, second));
            smaller.push_back(std::min(first, second));
        } else {
            larger.push_back(*it++);
        }
    }

	// Step 3: Recursively sort the larger elements
	mergeInsertionSort(larger);

	// Step 4: Find the corresponding smaller element for the smallest larger element
    int smallest_larger = larger.front();
    int corresponding_smaller = -1;
    it = arr.begin();
    for (size_t i = 0; i < n; i += 2) {
        if (i + 1 < n) {
            int first = *it++;
            int second = *it++;
            if (first == smallest_larger || second == smallest_larger) {
                corresponding_smaller = std::min(first, second);
                break;
            }
        }
    }

	// Clear the original array and populate it with sorted larger elements
	arr.clear();
	arr = larger;

	if (corresponding_smaller != -1) {
		arr.push_front(corresponding_smaller);
	}

	// Step 5: Insert the remaining smaller elements
    for (std::list<int>::iterator it = smaller.begin(); it != smaller.end(); ++it) {
        if (*it != corresponding_smaller) {
            std::list<int>::iterator pos = std::lower_bound(arr.begin(), arr.end(), *it);
            #ifdef DEBUG
                comparisonCount += static_cast<int>(std::log(static_cast<double>(arr.size())) / std::log(2.0));
            #endif
            arr.insert(pos, *it);
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

/*
test case
./PmergeMe 9 3 7 4 8 2 6 5
./PmergeMe 8 1 6 3 7 2 5 4
./PmergeMe `jot -r 3000 1 100000 | sort -n | uniq | tr '\n' ' '` > out

*/

