#ifndef RPN_HPP
#define RPN_HPP

#include <stack>
#include <string>

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
    size_t size();
    
    class Exception : public std::exception {
        public:
            explicit Exception(const std::string& msg);
            ~Exception() throw();
            const char* what() const throw();
        private:
            std::string _msg;
    };
};

#endif
