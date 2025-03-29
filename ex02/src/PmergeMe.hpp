#ifndef PMERGE_ME_HPP
#define PMERGE_ME_HPP

#include <vector>
#include <deque>
#include <list>
#include <cmath>
#include <algorithm>

class PmergeMe {
public:
    // Orthodx Canonical Form
    PmergeMe();
    PmergeMe(const PmergeMe&);
    PmergeMe& operator=(const PmergeMe&);
    ~PmergeMe();

    //  Class Methods
    template <typename T> static void merge_insert_sort(T &container);
private:
    // Private Methods
    template <typename T> static void sort_impl(T &container, int pair_size);
    template <typename T> static void swap_pair(T &it, int pair_size);
};

long jacobsthal_number(long n);

template <typename T>
T next(T it, int step) {
    std::advance(it, step);
    return it;
}

template <typename T>
bool _comp(T l_v, T r_v) {
    return *l_v < *r_v;
}

template <typename T>
void PmergeMe::merge_insert_sort(T &container) {
    sort_impl(container, 1);
}

template <typename T>
void PmergeMe::swap_pair(T &it, int pair_size) {
    T start = next(it, -pair_size + 1);
    T end = next(start, pair_size);
    while (start != end)
    {
        std::iter_swap(start, next(start, pair_size));
        start++;
    }
}


template <typename T>
void PmergeMe::sort_impl(T &container, int pair_size) {

    typedef typename T::iterator Iterator;
    int pair_unit_num= container.size() / pair_size;
    if (pair_unit_num < 2)
        return;
    bool is_odd = pair_unit_num % 2 == 1;
    Iterator start = container.begin();
    Iterator last = next(container.begin(), pair_size * pair_unit_num);
    Iterator end = next(last, -(is_odd * pair_size));

    int jump = pair_size * 2;
    for (Iterator it = start; it != end; std::advance(it, jump)) {
        Iterator this_pair = next(it, pair_size - 1);
        Iterator next_pair = next(it, pair_size * 2 -1);
        if (*this_pair > *next_pair) {
            swap_pair(this_pair, pair_size);
        }
    }
    sort_impl(container, pair_size * 2);
    std::vector<Iterator> main;
    std::vector<Iterator> pend;
    main.insert(main.end(), next(container.begin(), pair_size - 1));
    main.insert(main.end(), next(container.begin(), pair_size * 2 - 1));
    for (int i = 4; i <= pair_unit_num; i += 2) {
        main.insert(main.end(), next(container.begin(), pair_size * i - 1));
        pend.insert(pend.end(), next(container.begin(), pair_size * (i - 1) - 1));
    }
    int prev_jacobsthal = jacobsthal_number(1);
    int inserted_numbers = 0;
    for (int k = 2;; k++){
        int curr_jacobsthal = jacobsthal_number(k);
        int  jacobsthal_diff = curr_jacobsthal - prev_jacobsthal;
        if (jacobsthal_diff > static_cast<int>(pend.size())) {
            break;
        }
        int nbr_of_times = jacobsthal_diff;
        typename std::vector<Iterator>::iterator pend_it = next(pend.begin(), jacobsthal_diff - 1);
        typename std::vector<Iterator>::iterator bound_it = next(main.begin(), curr_jacobsthal + inserted_numbers);
        while (nbr_of_times) {
            typename std::vector<Iterator>::iterator idx =
                std::upper_bound(main.begin(), bound_it, *pend_it, _comp<Iterator>);
            main.insert(idx, *pend_it);
            nbr_of_times--;
            pend_it = pend.erase(pend_it);
            std::advance(pend_it, -1);
            bound_it = next(main.begin(), curr_jacobsthal + inserted_numbers);
        }
        prev_jacobsthal = curr_jacobsthal;
        inserted_numbers += jacobsthal_diff;
    }
    for (size_t i = 0; i < pend.size(); i++) {
        typename std::vector<Iterator>::iterator curr_pend = next(pend.begin(), i);
        typename std::vector<Iterator>::iterator curr_bound = next(main.begin(), main.size() - pend.size() + i);
        typename std::vector<Iterator>::iterator idx = 
            std::upper_bound(main.begin(), curr_bound, *curr_pend, _comp<Iterator>);
        main.insert(idx, *curr_pend);
    }
    if (is_odd) {
        Iterator odd_pair = next(end, pair_size - 1);
        typename std::vector<Iterator>::iterator idx = 
            std::upper_bound(main.begin(), main.end(), odd_pair, _comp<Iterator>);
        main.insert(idx, odd_pair);
    }
    std::vector<int> copy;
    for (typename std::vector<Iterator>::iterator it = main.begin(); it != main.end(); it++) {
        for (int j = 0; j < pair_size; j++) {
            Iterator curr = *it;
            std::advance(curr, - pair_size + 1 + j);
            copy.insert(copy.end(), *curr);
        }
    }
    // copy to original vector
    for (size_t i = 0; i < copy.size(); i++) {
        container[i] = copy[i];
    }
    return;
}

#endif
