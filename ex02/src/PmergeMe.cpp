#include <iostream>
#include "PmergeMe.hpp"

long jacobsthal_number(long n) {
 return round((pow(2, n + 1) + pow(-1, n)) / 3);
}

PmergeMe::PmergeMe() {}

PmergeMe::PmergeMe(const PmergeMe&) {}

PmergeMe& PmergeMe::operator=(const PmergeMe&) {
    return *this;
}

PmergeMe::~PmergeMe() {}
