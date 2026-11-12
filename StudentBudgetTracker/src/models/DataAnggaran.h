#ifndef DATA_ANGGARAN_H
#define DATA_ANGGARAN_H

#include <string>

enum StatusAnggaran { AMAN, HAMPIR_HABIS, TERLAMPAUI };

// DIAGRAM: struct DataAnggaran(kategori, batas_anggaran, total_pengeluaran, sisa_anggaran)
struct DataAnggaran {
    std::string kategori;
    long long batas_anggaran = 0;
    long long total_pengeluaran = 0;
    long long sisa_anggaran = 0;

    DataAnggaran() = default;
    DataAnggaran(const std::string& kat, long long batas, long long pengeluaran, long long sisa)
        : kategori(kat), batas_anggaran(batas), total_pengeluaran(pengeluaran), sisa_anggaran(sisa) {}
};

#endif
