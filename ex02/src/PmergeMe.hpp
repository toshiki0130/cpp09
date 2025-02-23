#ifndef PMERGE_ME_HPP
#define PMERGE_ME_HPP

#include <vector>
#include <deque>
#include <list>
#include <cmath>
#include <algorithm>

typedef std::vector<int>::iterator VecIt;
class PmergeMe {
public:
    // Orthodx Canonical Form
    PmergeMe();
    PmergeMe(const PmergeMe&);
    PmergeMe& operator=(const PmergeMe&);
    ~PmergeMe();

    //  Class Methods
    static void merge_insert_sort(std::vector<int> &v);
    static void merge_insert_sort(std::deque<int> &d);
    // Private Methods
private:
    template <typename T> static void sort_impl(T &container, int pair_level);
    template <typename T> static void swap_pair(T &it, int pair_level);
};

long jacobsthal_number(long n);


#endif
