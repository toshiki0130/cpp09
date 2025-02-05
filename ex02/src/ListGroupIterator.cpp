#include "ListGroupIterator.hpp"

ListGroupIterator::ListGroupIterator() {}

ListGroupIterator::ListGroupIterator(const ListGroupIterator&) {}

ListGroupIterator& ListGroupIterator::operator=(const ListGroupIterator&) {
    return *this;
}

ListGroupIterator::~ListGroupIterator() {}

ListGroupIterator::ListGroupIterator(std::list<int>::iterator it, int group_size) {
    _it = it;
    _group_size = group_size;
}
