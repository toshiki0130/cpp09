#include "RPN.hpp"
#include <cctype>
#include <iostream>

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
        if (_n_stack.size() < 2) {
            throw Exception("Error: invalid expression");
        }
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
        throw Exception("Error: Invalid char: " + std::string(1, c)); 
    }
}

int RPN::getTop() {
    return _n_stack.top();
}

size_t RPN::size() {
    return _n_stack.size();
}

// Exception
RPN::Exception::Exception(const std::string& msg) {
    _msg = msg;
}

RPN::Exception::~Exception() throw() {}

const char* RPN::Exception::what() const throw() {
    return _msg.c_str();
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