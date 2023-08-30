#include "PmergeMe.hpp"

int main(int argc, char* argv[]) {
    std::vector<int> arr;

    for (int i = 1; i < argc; ++i) {
        arr.push_back(std::atoi(argv[i]));
    }

    std::cout << "Before: ";
    for (size_t i = 0; i < arr.size(); ++i) {
        std::cout << arr[i] << " ";
    }
    std::cout << std::endl;

	PmergeMe p;
    p.mergeInsertionSort(arr);

    std::cout << "After:  ";
    for (size_t i = 0; i < arr.size(); ++i) {
        std::cout << arr[i] << " ";
    }
    std::cout << std::endl;

    return 0;
}
