#ifndef PMERGE_ME_HPP
#define PMERGE_ME_HPP

#include <vector>
#include <list>
#include "ListGroupIterator.hpp"

class PmergeMe {
public:
    // Orthodx Canonical Form
    PmergeMe();
    PmergeMe(const PmergeMe&);
    PmergeMe& operator=(const PmergeMe&);
    ~PmergeMe();

    //  Class Methods
    static void merge_insert_sort(std::vector<int> &v);
    static void merge_insert_sort(std::list<int> &l);
    // Private Methods
private:
    static void sort_impl(std::vector<int> &vec, int pair_level);
    static std::vector<int>::iterator next(std::vector<int>::iterator it, int step);
    static void swap_pair(std::vector<int>::iterator &it, int pair_level);
};

#endif
