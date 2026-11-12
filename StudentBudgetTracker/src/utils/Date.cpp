#include "../models/Date.h"
#include <sstream>
#include <iomanip>
#include <cctype>

bool validasiTanggal(const Date& t) {
    return (t.hari >= 1 && t.hari <= 31 && t.bulan >= 1 && t.bulan <= 12 && t.tahun > 0);
}

std::string formatTanggal(const Date& t) {
    std::ostringstream ss;
    ss << std::setfill('0') << std::setw(2) << t.hari << "-"
       << std::setfill('0') << std::setw(2) << t.bulan << "-"
       << t.tahun;
    return ss.str();
}

bool parseTanggal(const std::string& teks, Date& t) {
    if (teks.size() != 10 || teks[2] != '-' || teks[5] != '-') return false;
    for (int i : {0,1,3,4,6,7,8,9}) {
        if (!std::isdigit(static_cast<unsigned char>(teks[i]))) return false;
    }
    try {
        t.hari = std::stoi(teks.substr(0, 2));
        t.bulan = std::stoi(teks.substr(3, 2));
        t.tahun = std::stoi(teks.substr(6, 4));
    } catch (...) {
        return false;
    }
    return validasiTanggal(t);
}
