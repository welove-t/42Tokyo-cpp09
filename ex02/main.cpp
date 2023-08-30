#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdlib>

void mergeInsertionSort(std::vector<int>& arr);

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

    mergeInsertionSort(arr);

    std::cout << "After:  ";
    for (size_t i = 0; i < arr.size(); ++i) {
        std::cout << arr[i] << " ";
    }
    std::cout << std::endl;

    return 0;
}

void mergeInsertionSort(std::vector<int>& arr) {
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
