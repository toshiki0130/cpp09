#ifndef RPN_HPP
#define RPN_HPP

#include <stack>

class RPN {
private:
    std::stack<int> _n_stack;
    bool _isOperator(char c);
public:
    // constructor
    RPN();
    RPN(const RPN &other);
    RPN& operator=(const RPN &other);
    ~RPN();
    // member functions
    void push(char c);
    int getTop();
};

#endif