#ifndef LAPORAN_KEUANGAN_H
#define LAPORAN_KEUANGAN_H

#include <string>

// CATATAN-DIAGRAM: Menggunakan sisa_saldo (bukan sisa_waktu pada Dekomposisi) sesuai alur algoritma.
// DIAGRAM: struct LaporanKeuangan: periode, total_pemasukan, total_pengeluaran, sisa_saldo
struct LaporanKeuangan {
    std::string periode; // MM-YYYY
    long long total_pemasukan = 0;
    long long total_pengeluaran = 0;
    long long sisa_saldo = 0;
};

#endif
