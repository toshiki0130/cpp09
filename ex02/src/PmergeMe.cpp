#include <iostream>
#include "PmergeMe.hpp"
#include "ListGroupIterator.hpp"

typedef std::vector<int>::iterator VecIt;

ListGroupIterator make_list_group_iterator(
    std::list<int>::iterator it, 
    int group_size) {
    return ListGroupIterator(it, group_size);
}

PmergeMe::PmergeMe() {}

PmergeMe::PmergeMe(const PmergeMe&) {}

PmergeMe& PmergeMe::operator=(const PmergeMe&) {
    return *this;
}

PmergeMe::~PmergeMe() {}

std::vector<int>::iterator PmergeMe::next(std::vector<int>::iterator it, int step) {
    std::advance(it, step);
    return it;
}

void PmergeMe::swap_pair(std::vector<int>::iterator &it, int pair_level) {
    std::vector<int>::iterator start = next(it, -pair_level + 1);
    std::vector<int>::iterator end = next(start, pair_level);
    while (start != end)
    {
        std::iter_swap(start, next(start, pair_level));
        start++;
    }
}

void PmergeMe::merge_insert_sort(std::vector<int> &v) {
    sort_impl(v, 1);
}

void PmergeMe::merge_insert_sort(std::list<int> &l_orig) {
    std::list<int>::iterator test = l_orig.end();
    
}

void PmergeMe::sort_impl(std::vector<int> &vec, int pair_level) {

    std::vector<int>::iterator it;
    int pair_unit_size= vec.size() / pair_level;
    if (pair_unit_size < 2)
        return;
    bool is_odd = pair_unit_size % 2 == 1;
    std::vector<int>::iterator start = vec.begin();
    std::vector<int>::iterator temp = vec.begin();
    std::vector<int>::iterator last = next(vec.begin(), pair_level * pair_unit_size);
    std::vector<int>::iterator end = next(last, -(is_odd * pair_level));

    int jump = pair_level * 2;
    for (std::vector<int>::iterator it = start; it != end; std::advance(it, jump)) {
        std::vector<int>::iterator this_pair = next(it, pair_level - 1);
        std::vector<int>::iterator next_pair = next(it, pair_level * 2 -1);
        if (*this_pair > *next_pair) {
            swap_pair(this_pair, pair_level);
        }
    }
    sort_impl(vec, pair_level * 2);
    std::vector<VecIt> main;
    std::vector<VecIt> pend;
    return;
}
