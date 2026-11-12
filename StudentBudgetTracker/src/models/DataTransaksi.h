#ifndef DATA_TRANSAKSI_H
#define DATA_TRANSAKSI_H

#include <string>
#include "Date.h"

// DIAGRAM: struct DataTransaksi(id_transaksi, tanggal, jenis, kategori, nominal, catatan)
struct DataTransaksi {
    int id_transaksi = 0;
    Date tanggal;
    std::string jenis;       // "pemasukan" / "pengeluaran"
    std::string kategori;
    std::string sumber_dana; // khusus pemasukan
    long long nominal = 0;   // rupiah disimpan sebagai bilangan bulat
    std::string catatan;
};

#endif
