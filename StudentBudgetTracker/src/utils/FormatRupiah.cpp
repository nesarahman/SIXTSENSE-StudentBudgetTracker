#include "FormatRupiah.h"
#include <algorithm>
#include <cctype>
#include <string>

bool parseNominalRupiah(const std::string& teks, long long& hasil) {
    std::string angka;
    for (char c : teks) {
        if (std::isdigit(static_cast<unsigned char>(c))) angka += c;
        else if (c == '.' || c == ',' || c == ' ' || c == 'R' || c == 'r' || c == 'P' || c == 'p') continue;
        else return false;
    }
    if (angka.empty()) return false;
    try {
        hasil = std::stoll(angka);
    } catch (...) {
        return false;
    }
    return hasil > 0;
}

std::string formatRupiah(long long nominal) {
    bool negatif = nominal < 0;
    std::string angka = std::to_string(negatif ? -nominal : nominal);
    for (int i = static_cast<int>(angka.size()) - 3; i > 0; i -= 3)
        angka.insert(static_cast<std::size_t>(i), ".");
    return std::string(negatif ? "-Rp " : "Rp ") + angka;
}
