#ifndef DATE_HPP
#define DATE_HPP
#include <string>

class Date {
public:
    // orthidix canonical form
    Date();
    Date(const Date &other);
    Date &operator=(const Date &other);
    ~Date();
    // Exception
    class Exception : public std::exception {
    public:
        explicit Exception(const std::string &msg);
        Exception(const Exception &other);
        Exception &operator=(const Exception &other);
        ~Exception();
        const char* what() const throw();
    private:
        std::string _msg;
    };
    Date(const std::string &date_str);
    int year;
    int month;
    int day;
private:
    void _validate();
    int _getDaysInMonth();
    bool _isLeapYear();
};

#endif