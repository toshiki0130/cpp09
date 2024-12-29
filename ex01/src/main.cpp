#include "RPN.hpp"
#include <iostream>

void run(char *exp);

int main(int argc, char *argv[]) {
    run(argv[1]);
}

void run(char *exp)
{
    while (*exp) {
        std::cout << *exp << std::endl;
        exp++;
    }
}