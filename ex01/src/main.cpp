#include "RPN.hpp"
#include <iostream>
#include <cstdlib>

int run(char *exp);

int main(int argc, char *argv[]) {
    if (argc != 2) {
        std::cerr << "Usage example: RPN '8 9 * 9 - 9 - 9 - 4 - 1 +'" << std::endl;
        return EXIT_FAILURE;
    }
    std::cout << run(argv[1]) << std::endl;
}

int run(char *exp)
{
    RPN rpn;
    while (*exp) {
        if (*exp == ' ') {
            exp++;
            continue;
        }
        rpn.push(*exp);
        exp++;
    }
    return rpn.getTop();
}