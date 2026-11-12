#ifndef DATE_H
#define DATE_H

#include <string>

struct Date {
    int hari = 1;
    int bulan = 1;
    int tahun = 2000;
};

std::string formatTanggal(const Date& tanggal);
bool parseTanggal(const std::string& teks, Date& tanggal);
bool validasiTanggal(const Date& tanggal);

#endif
