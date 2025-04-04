#include <algorithm>
#include <vector>
#include <deque>
#include <list>
#include <string>
#include <stdexcept>
#include <iostream>
#include <sstream>
#include <iomanip>
#include <cerrno>
#include <climits>
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
        << " elements with std::vector : " << std::fixed << std::setprecision(6) << elapsed_v << "s" << std::endl;
    std::cout << "Time to process a range of " << d.size() 
        << " elements with std::deque : " << std::fixed << std::setprecision(6) << elapsed_d << "s" << std::endl;
}

int stringToInt(const std::string &str) throw(std::invalid_argument, std::out_of_range) {
    if (str.empty()) {
        throw std::invalid_argument("empty string");
    }
    char *end;
    long result = std::strtol(str.c_str(), &end, 10);
    if (*end != '\0') {
        throw std::invalid_argument("invalid string");
    }
    if (result < INT_MIN || result > INT_MAX) {
        throw std::out_of_range("Integer out of range");      
    }
    return result;
}

bool is_positive_int(const std::string& arg){
    if (arg.empty()) {
        return false;
    } 
    if (arg[0] == '-') {
        return false;
    }
    char *end;
    errno = 0;
    long nbr = std::strtol(arg.c_str(), &end, 10);
    if (*end != '\0') {
        // 文字列が混ざってる
        return false;
    }
    if (nbr == 0) {
        return false;
    }
    if (errno == ERANGE || nbr > INT_MAX) {
        // INTの範囲外
        return false;
    }
    return true;
}

void validateArgs(int argc, char *argv[]) throw(std::invalid_argument) {
    if (argc < 2) {
        throw std::invalid_argument("No arguments were provided");
    }
    for (int i = 1; i < argc; i++) {
        bool result = is_positive_int(argv[i]);
        if (!result) {
            throw std::invalid_argument("Not positive integer or Not invalid range");
        }
    }
}

int main(int argc, char *argv[]) {
    try {
        validateArgs(argc, argv);
    }
    catch (const std::invalid_argument& e) {
        std::cerr << "Error: invalid arguments -> " << e.what() << std::endl;
        return EXIT_FAILURE;
    }
    catch (const std::exception& e) {
        std::cerr << "Error: Unexpected Error -> " << e.what() << std::endl;
        return EXIT_FAILURE;
    }
    std::vector<int> orig;
    for (int i=1; i < argc; i++) {
        orig.push_back(stringToInt(argv[i]));
    }
    run_sort(orig);
    return 0;
}
