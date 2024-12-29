#include "RPN.hpp"

// constructor
RPN::RPN() {}

RPN::RPN(const RPN &other) {
    n_stack = other.n_stack;
}

RPN& RPN::operator=(const RPN &other) {
    if (this != &other) {
        n_stack = other.n_stack;
    }
    return *this;
}

RPN::~RPN() {}
