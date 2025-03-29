#include "RPN.hpp"
#include <iostream>
#include <cstdlib>

int run(char *exp);

int main(int argc, char *argv[]) {
    if (argc != 2) {
        std::cerr << "Usage example: RPN '8 9 * 9 - 9 - 9 - 4 - 1 +'" << std::endl;
        return EXIT_FAILURE;
    }
    return run(argv[1]);
}

int run(char *exp)
{
    RPN rpn;
    while (*exp) {
        if (*exp == ' ') {
            exp++;
            continue;
        }
        try {
            rpn.push(*exp);
        }
        catch (std::exception &e) {
            std::cerr << e.what() << std::endl;
            return EXIT_FAILURE;
        }
        exp++;
    }
    if (rpn.size() != 1) {
        std::cerr << "Error: final stack size is not 1." << std::endl;
        return EXIT_FAILURE;
    }
    std::cout << rpn.getTop() << std::endl;
    return EXIT_SUCCESS;
}
