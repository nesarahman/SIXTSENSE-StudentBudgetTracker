#include "Database.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <filesystem>
#include "../models/Date.h"

// DIAGRAM: List RiwayatTransaksi;
std::vector<DataTransaksi> RiwayatTransaksi;

// DIAGRAM: List PengaturanAnggaran;
std::vector<DataAnggaran> PengaturanAnggaran;

// DIAGRAM: LaporanKeuangan
struct LaporanKeuangan LaporanKeuangan;

static const char* FILE_TRANSAKSI = "data/transaksi.txt";
static const char* FILE_ANGGARAN = "data/anggaran.txt";

static std::vector<std::string> pisah(const std::string& s) {
    std::vector<std::string> v;
    std::stringstream ss(s);
    std::string x;
    while (std::getline(ss, x, '|')) v.push_back(x);
    return v;
}

// DIAGRAM: BukaAplikasi
bool BukaAplikasi() {
    std::error_code ec;
    std::filesystem::create_directories("data", ec);

    PengaturanAnggaran.clear();
    RiwayatTransaksi.clear();
    LaporanKeuangan = {};

    std::ifstream fa(FILE_ANGGARAN);
    std::string baris;
    while (std::getline(fa, baris)) {
        auto f = pisah(baris);
        if (f.size() >= 2) {
            try {
                DataAnggaran a;
                a.kategori = f[0];
                a.batas_anggaran = std::stoll(f[1]);
                a.total_pengeluaran = 0;
                a.sisa_anggaran = a.batas_anggaran;
                PengaturanAnggaran.push_back(a);
            } catch (...) {}
        }
    }

    std::ifstream ft(FILE_TRANSAKSI);
    while (std::getline(ft, baris)) {
        auto f = pisah(baris);
        if (f.size() != 7) continue;
        try {
            DataTransaksi t;
            Date d;
            t.id_transaksi = std::stoi(f[0]);
            if (!parseTanggal(f[1], d)) continue;
            t.tanggal = d;
            t.jenis = f[2];
            t.kategori = f[3];
            t.sumber_dana = f[4];
            t.nominal = std::stoll(f[5]);
            t.catatan = f[6];
            RiwayatTransaksi.push_back(t);
        } catch (...) {}
    }

    // Hitung ulang total pemasukan, pengeluaran, saldo berjalan LaporanKeuangan dan anggaran
    LaporanKeuangan.total_pemasukan = 0;
    LaporanKeuangan.total_pengeluaran = 0;
    LaporanKeuangan.sisa_saldo = 0;

    for (const auto& t : RiwayatTransaksi) {
        if (t.jenis == "pemasukan") {
            LaporanKeuangan.total_pemasukan += t.nominal;
            LaporanKeuangan.sisa_saldo += t.nominal;
        } else if (t.jenis == "pengeluaran") {
            LaporanKeuangan.total_pengeluaran += t.nominal;
            LaporanKeuangan.sisa_saldo -= t.nominal;
        }
    }

    for (auto& a : PengaturanAnggaran) {
        a.total_pengeluaran = 0;
        for (const auto& t : RiwayatTransaksi) {
            if (t.jenis == "pengeluaran" && t.kategori == a.kategori) {
                a.total_pengeluaran += t.nominal;
            }
        }
        a.sisa_anggaran = a.batas_anggaran - a.total_pengeluaran;
    }

    return true;
}

// DIAGRAM: Simpan transaksi (t) ke basis data
bool SimpanTransaksiKeBasisData(const DataTransaksi& t) {
    if (t.id_transaksi <= 0) return true;
    std::ofstream ft(FILE_TRANSAKSI, std::ios::app);
    if (!ft) return false;
    ft << t.id_transaksi << '|'
       << formatTanggal(t.tanggal) << '|'
       << t.jenis << '|'
       << t.kategori << '|'
       << t.sumber_dana << '|'
       << t.nominal << '|'
       << t.catatan << '\n';
    return true;
}

// DIAGRAM: Simpan PengaturanAnggaran (anggaran) ke basis data
bool SimpanPengaturanAnggaranKeBasisData(const std::vector<DataAnggaran>& anggaran) {
    std::ofstream fa(FILE_ANGGARAN, std::ios::trunc);
    if (!fa) return false;
    for (const auto& a : anggaran) {
        fa << a.kategori << '|' << a.batas_anggaran << '\n';
    }
    return true;
}

// DIAGRAM: Simpan RiwayatTransaksi (riwayat) ke basis data
bool SimpanRiwayatTransaksiKeBasisData(const std::vector<DataTransaksi>& riwayat) {
    std::ofstream ft(FILE_TRANSAKSI, std::ios::trunc);
    if (!ft) return false;
    for (const auto& t : riwayat) {
        ft << t.id_transaksi << '|'
           << formatTanggal(t.tanggal) << '|'
           << t.jenis << '|'
           << t.kategori << '|'
           << t.sumber_dana << '|'
           << t.nominal << '|'
           << t.catatan << '\n';
    }
    return true;
}

// DIAGRAM: SinkronisasiBasisData (transaksi, anggaran, riwayat)
bool SinkronisasiBasisData(const DataTransaksi& transaksi,
                           const std::vector<DataAnggaran>& anggaran,
                           const std::vector<DataTransaksi>& riwayat) {
    // Tiga langkah sinkronisasi sesuai diagram:
    // 1. Simpan transaksi (t) ke basis data
    SimpanTransaksiKeBasisData(transaksi);
    // 2. Simpan PengaturanAnggaran (anggaran) ke basis data
    SimpanPengaturanAnggaranKeBasisData(anggaran);
    // 3. Simpan RiwayatTransaksi (riwayat) ke basis data
    SimpanRiwayatTransaksiKeBasisData(riwayat);
    return true;
}
