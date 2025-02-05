
#ifndef LISTGROUPITERATOR_HPP
#define LISTGROUPITERATOR_HPP

#include <list>
class ListGroupIterator {
    // Iterator for list groups
    private:
        std::list<int>::iterator _it;
        int _group_size;
    // constructor
    public:
        // Orthodx Canonical Form
        ListGroupIterator();
        ListGroupIterator(const ListGroupIterator&);
        ListGroupIterator& operator=(const ListGroupIterator&);
        ~ListGroupIterator();

        ListGroupIterator(std::list<int>::iterator it, int group_size);

        // Define the subtraction operator
        int operator-(const ListGroupIterator &rhs) const {
            return std::distance(_it, rhs._it) / _group_size;
        }
};

#endif