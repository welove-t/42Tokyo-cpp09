#include "PmergeMe.hpp"

#ifdef DEBUG
int comparisonCount = 0;
#endif

int main(int argc, char* argv[])
{
	PmergeMe p;

	if (p.isValid(argc, argv))
		return 1;

	std::vector<int> vec;
	for (int i = 1; i < argc; ++i) {
		vec.push_back(std::atoi(argv[i]));
	}

	std::cout << "Before:\t";
	for (size_t i = 0; i < vec.size(); ++i) {
		std::cout << vec[i] << " ";
	}
	std::cout << std::endl;

	std::clock_t start = std::clock();
	p.mergeInsertionSort(vec);
	std::clock_t end = std::clock();
	double elapsed_time = static_cast<double>(end - start) / CLOCKS_PER_SEC;


	std::cout << "After:\t";
	for (size_t i = 0; i < vec.size(); ++i) {
		std::cout << vec[i] << " ";
	}
	std::cout << std::endl;

	std::cout << "Time to process a range of " << vec.size() << " elements with std::vector : "  <<
	std::fixed << std::setprecision(6) << elapsed_time << " sec"
	#ifdef DEBUG
		<< " | comparisonCount: " <<  comparisonCount
	#endif
	<< std::endl;

	// list
	std::list<int> lst;
	for (int i = 1; i < argc; ++i) {
		lst.push_back(std::atoi(argv[i]));
	}
	start = std::clock();
	p.mergeInsertionSort(lst);
	end = std::clock();
	elapsed_time = static_cast<double>(end - start) / CLOCKS_PER_SEC;

	std::cout << "After:\t";
	// for (size_t i = 0; i < lst.size(); ++i) {
	// 	std::cout << lst[i] << " ";
	// }
	for (std::list<int>::iterator it = lst.begin(); it != lst.end(); ++it)
	{
		std::cout << *it << " ";
	}
	std::cout << std::endl;

	std::cout << "Time to process a range of " << lst.size() << " elements with std::list : "  <<
	std::fixed << std::setprecision(6) << elapsed_time << " sec"
	#ifdef DEBUG
		<< " | comparisonCount: " <<  comparisonCount
	#endif
	<< std::endl;

	return 0;
}
