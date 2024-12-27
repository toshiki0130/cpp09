#include <string>
#include <sstream>

double stringToDouble(const std::string& str) {
    std::istringstream iss(str);
    double value;

    // 文字列を double に変換
    iss >> value;

    // 変換が成功したかチェック
    if (iss.fail()) {
        throw std::invalid_argument("Invalid string for conversion: " + str);
    }

    return value;
}

bool isDigit(const std::string& number) {
    if (number.empty()) {
        return false;
    }
    for (std::string::size_type i=0; i < number.size(); i++) {
        if (!std::isdigit(number[i])) {
            return false;
        }
    }
    return true;
}