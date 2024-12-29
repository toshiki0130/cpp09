#ifndef RPN_HPP
#define RPN_HPP

#include <stack>

class RPN {
private:
    std::stack<int> n_stack;
public:
    // constructor
    RPN();
    RPN(const RPN &other);
    RPN& operator=(const RPN &other);
    ~RPN();
    // 
};

#endif