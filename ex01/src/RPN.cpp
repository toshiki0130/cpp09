#include "RPN.hpp"
#include <cctype>

// constructor
RPN::RPN() {}

RPN::RPN(const RPN &other) {
    _n_stack = other._n_stack;
}

RPN& RPN::operator=(const RPN &other) {
    if (this != &other) {
        _n_stack = other._n_stack;
    }
    return *this;
}

RPN::~RPN() {}

// member functions
void RPN::push(char c) {
    if (isdigit(c)) {
        _n_stack.push(c - '0');
        return ;
    }
    else if (_isOperator(c))
    {
        int rv = _n_stack.top();
        _n_stack.pop();
        int lv = _n_stack.top();
        _n_stack.pop();
        if (c == '+') {
            _n_stack.push(lv + rv);
        }
        else if (c == '-') {
            _n_stack.push(lv - rv);
        }
        else if (c == '*'){
            _n_stack.push(lv * rv);
        }
        else if (c == '/'){
            _n_stack.push(lv / rv);
        }
    }
    else {
        return; 
    }
}

int RPN::getTop() {
    return _n_stack.top();
}

// private functions
bool RPN::_isOperator(char c) {
    // + - / *
    switch (c) {
    case '+':
    case '-':
    case '/':
    case '*':
        return true;
    default:
        return false;
    }
}