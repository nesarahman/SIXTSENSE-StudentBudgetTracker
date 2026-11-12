#include "Validasi.h"
#include <iostream>

bool validasiNominal(long long nominal) {
    return nominal > 0;
}

std::string inputTeks(const std::string& prompt) {
    std::string s;
    std::cout << prompt;
    std::getline(std::cin, s);
    for (char& c : s) if (c == '|') c = '/';
    return s;
}
