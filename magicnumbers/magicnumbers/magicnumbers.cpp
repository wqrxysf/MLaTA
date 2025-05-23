#include <iostream>
#include <cstdint>
#include <string>
#include <cctype>

bool is_valid_uint64(const std::string& str, uint64_t& num) {
    if (str.empty() || (str.size() > 1 && str[0] == '0')) return false;

    num = 0;
    for (char ch : str) {
        if (!std::isdigit(ch)) return false;
        uint64_t digit = ch - '0';
        if (num > (UINT64_MAX - digit) / 10) return false; 
        num = num * 10 + digit;
    }
    return true;
}

bool is_magic_number(uint64_t num) {
    uint64_t sum_digits = 0, temp = num;
    while (temp > 0) {
        sum_digits += temp % 10;
        temp /= 10;
    }
    return (num - sum_digits) % 9 != 0;
}

int main() {
    std::string input;
    std::cin >> input;

    uint64_t num;
    if (!is_valid_uint64(input, num)) {
        std::cout << "Error" << std::endl;
        return 0;
    }

    if (is_magic_number(num)) {
        std::cout << "Magic" << std::endl;
    }
    else {
        std::cout << "Non-magic" << std::endl;
    }

    return 0;
}

//int tests() {
//    if (!is_magic_number(10)) {
//        std::cout << "Non-magic" << std::endl;
//    }
//    if (!is_magic_number(100)) {
//        std::cout << "Non-magic" << std::endl;
//    }
//    if (!is_magic_number(1234)) {
//        std::cout << "Non-magic" << std::endl;
//    }
//    if (is_magic_number(2)) {
//        std::cout << "Magic" << std::endl;
//    }
//    return 0;
//}
//
//int main() {
//    return tests();
//}