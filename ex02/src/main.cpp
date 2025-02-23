#include <algorithm>
#include <vector>
#include <deque>
#include <list>
#include <string>
#include <stdexcept>
#include <iostream>
#include <sstream>
#include <iomanip>
#include "PmergeMe.hpp"

void run_sort(std::vector<int> &orig) {
    std::vector<int> v(orig.begin(), orig.end());
    std::deque<int> d(orig.begin(), orig.end());
    std::cout << "Before: ";
    for (std::vector<int>::const_iterator it = v.begin(); it != v.end(); ++it) {
        std::cout << *it << " ";
    }
    double elapsed_v, elapsed_d;
    // Sort Vector with Ford-Johnson Algorithm
    // std::list
    {
        clock_t start = clock();
        // Ford-Johnson Algorithm
        PmergeMe::merge_insert_sort(v);
        clock_t end = clock();
        elapsed_v = static_cast<double>(end - start) / CLOCKS_PER_SEC;
    }
    {
        clock_t start = clock();
        // Ford-Johnson Algorithm
        PmergeMe::merge_insert_sort(d);
        clock_t end = clock();
        elapsed_d = static_cast<double>(end - start) / CLOCKS_PER_SEC;

    }
    std::cout << std::endl << "After: ";
    for (std::vector<int>::const_iterator it = v.begin(); it != v.end(); it++) {
        std::cout << *it << " ";
    }
    std::cout << std::endl;
    std::cout << "Time to process a range of " << v.size() 
        << "elements with std::vector: " << std::fixed << std::setprecision(6) << elapsed_v << "s\n" << std::endl;
    std::cout << std::endl;
    std::cout << "Time to process a range of " << d.size() 
        << "elements with std::deque: " << std::fixed << std::setprecision(6) << elapsed_d << "s\n" << std::endl;
}

int stringToDouble(const std::string &str) throw(std::invalid_argument) {
    if (str.empty()) {
        throw std::invalid_argument("empty string");
    }
    char *end;
    int result = std::strtol(str.c_str(), &end, 10);
    if (*end != '\0') {
        throw std::invalid_argument("invalid string");
    }
    return result;
}

int main(int argc, char *argv[]) {
    std::vector<int> orig;
    for (int i=1; i < argc; i++) {
        orig.push_back(stringToDouble(argv[i]));
    }
    run_sort(orig);
    return 0;
}