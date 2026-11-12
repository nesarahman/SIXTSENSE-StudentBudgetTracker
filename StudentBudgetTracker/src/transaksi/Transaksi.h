#ifndef TRANSAKSI_H
#define TRANSAKSI_H

#include <string>
#include "../models/DataTransaksi.h"

// DIAGRAM: PilihMenuTransaksi()
void PilihMenuTransaksi();

// DIAGRAM: InputDataPemasukan()
void InputDataPemasukan();

// DIAGRAM: InputDataPengeluaran()
void InputDataPengeluaran();

// DIAGRAM: ValidasiDataTransaksi()
bool ValidasiDataTransaksi(std::string& kategori, long long& nominal, std::string& teks_tanggal, Date& tanggal, const std::string& jenis);

// DIAGRAM: PerbaikiData()
void PerbaikiData(std::string& kategori, long long& nominal, std::string& teks_tanggal, Date& tanggal, const std::string& jenis);

// DIAGRAM: SimpanKeBasisData()
void SimpanKeBasisData(DataTransaksi& t);

// DIAGRAM: PerbaruiSaldoTotal()
void PerbaruiSaldoTotal(const DataTransaksi& t);

// Alur Simpan Transaksi sesuai diagram
void AlurSimpanTransaksi(DataTransaksi& t);

#endif
