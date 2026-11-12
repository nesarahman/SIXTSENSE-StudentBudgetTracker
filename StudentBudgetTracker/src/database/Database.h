#ifndef DATABASE_H
#define DATABASE_H

#include <vector>
#include "../models/DataTransaksi.h"
#include "../models/DataAnggaran.h"
#include "../models/LaporanKeuangan.h"

// DIAGRAM: List RiwayatTransaksi;
extern std::vector<DataTransaksi> RiwayatTransaksi;

// DIAGRAM: List PengaturanAnggaran;
extern std::vector<DataAnggaran> PengaturanAnggaran;

// DIAGRAM: LaporanKeuangan
extern struct LaporanKeuangan LaporanKeuangan;

// DIAGRAM: BukaAplikasi
bool BukaAplikasi();

// DIAGRAM: Simpan transaksi (t) ke basis data
bool SimpanTransaksiKeBasisData(const DataTransaksi& t);

// DIAGRAM: Simpan PengaturanAnggaran (anggaran) ke basis data
bool SimpanPengaturanAnggaranKeBasisData(const std::vector<DataAnggaran>& anggaran);

// DIAGRAM: Simpan RiwayatTransaksi (riwayat) ke basis data
bool SimpanRiwayatTransaksiKeBasisData(const std::vector<DataTransaksi>& riwayat);

// DIAGRAM: SinkronisasiBasisData (transaksi, anggaran, riwayat)
bool SinkronisasiBasisData(const DataTransaksi& transaksi,
                           const std::vector<DataAnggaran>& anggaran,
                           const std::vector<DataTransaksi>& riwayat);

#endif
