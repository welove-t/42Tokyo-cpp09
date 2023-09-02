#include "PmergeMe.hpp"

#ifdef DEBUG
int comparisonCount = 0;
#endif

int main(int argc, char* argv[]) {

    PmergeMe p;

    if (p.isValid(argc, argv))
        return 1;
    std::vector<int> arr;

    for (int i = 1; i < argc; ++i) {
        arr.push_back(std::atoi(argv[i]));
    }

    std::cout << "Before:\t";
    for (size_t i = 0; i < arr.size(); ++i) {
        std::cout << arr[i] << " ";
    }
    std::cout << std::endl;

    std::clock_t start = std::clock();
    p.mergeInsertionSort(arr);
    std::clock_t end = std::clock();
    double elapsed_time = static_cast<double>(end - start) / CLOCKS_PER_SEC;


    std::cout << "After:\t";
    for (size_t i = 0; i < arr.size(); ++i) {
        std::cout << arr[i] << " ";
    }
    std::cout << std::endl;

    std::cout << "Time to process a range of 5 elements with std::vector : "  <<
    std::fixed << std::setprecision(6) << elapsed_time << " sec"
    #ifdef DEBUG
        << " | comparisonCount: " <<  comparisonCount
    #endif
    << std::endl;

    return 0;
}
