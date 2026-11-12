#include "Laporan.h"
#include <iostream>
#include <iomanip>
#include <cctype>
#include "../database/Database.h"
#include "../utils/FormatRupiah.h"

// DIAGRAM: TampilkanDashboard()
void TampilkanDashboard() {
    // DIAGRAM: RiwayatTransaksi .empty()??
    if (RiwayatTransaksi.empty()) {
        // DIAGRAM: Belum ada transaksi
        std::cout << "Belum ada transaksi\n";
        return;
    }

    // DIAGRAM: Ambil LaporanKeuangan: total_pemasukan, total_pengeluaran, sisa_saldo
    // DIAGRAM: Tampilkan saldo dan ringkasan: total_pemasukan | total_pengeluaran | sisa_saldo
    std::cout << "\n================== DASHBOARD ==================\n";
    std::cout << "Total pemasukan   : " << formatRupiah(LaporanKeuangan.total_pemasukan) << "\n";
    std::cout << "Total pengeluaran : " << formatRupiah(LaporanKeuangan.total_pengeluaran) << "\n";
    std::cout << "Sisa saldo        : " << formatRupiah(LaporanKeuangan.sisa_saldo) << "\n";
    std::cout << "-----------------------------------------------\n";
    std::cout << "Anggaran per Kategori:\n";

    // DIAGRAM: for (const auto& a : PengaturanAnggaran)
    for (const auto& a : PengaturanAnggaran) {
        // DIAGRAM: a.kategori | a.batas_anggaran | a.total_pengeluaran | a.sisa_anggaran (grafik anggaran)
        int barWidth = 10;
        int filled = 0;
        if (a.batas_anggaran > 0) {
            filled = static_cast<int>((a.total_pengeluaran * barWidth) / a.batas_anggaran);
            if (filled > barWidth) filled = barWidth;
            if (filled < 0) filled = 0;
        }
        std::string bar = "[";
        for (int i = 0; i < filled; ++i) bar += '#';
        for (int i = filled; i < barWidth; ++i) bar += '-';
        bar += ']';

        std::cout << a.kategori << " | "
                  << formatRupiah(a.batas_anggaran) << " | "
                  << formatRupiah(a.total_pengeluaran) << " | "
                  << formatRupiah(a.sisa_anggaran) << " "
                  << bar << "\n";
    }

    // DIAGRAM: Dashboard selesai ditampilkan
    std::cout << "Dashboard selesai ditampilkan\n";
    std::cout << "===============================================\n";
}

// DIAGRAM: ValidasiPeriodeLaporanBulanan()
bool ValidasiPeriodeLaporanBulanan(const std::string& periode) {
    if (periode.size() != 7 || periode[2] != '-') return false;
    for (int i : {0, 1, 3, 4, 5, 6}) {
        if (!std::isdigit(static_cast<unsigned char>(periode[i]))) return false;
    }
    int bulan = 0;
    int tahun = 0;
    try {
        bulan = std::stoi(periode.substr(0, 2));
        tahun = std::stoi(periode.substr(3, 4));
    } catch (...) {
        return false;
    }
    // DIAGRAM: bulan 1 - 12 && tahun valid??
    return (bulan >= 1 && bulan <= 12 && tahun > 0);
}

// DIAGRAM: ValidasiPeriodeLaporan()
bool ValidasiPeriodeLaporan(const std::string& periode) {
    // DIAGRAM: periode kosong??
    if (periode.empty()) return false;
    return ValidasiPeriodeLaporanBulanan(periode);
}

// CATATAN-DIAGRAM: Alur periode laporan tidak valid mengikuti Pola Penanganan Error (pilih ulang kembali ke input periode) bukan langsung ke TampilkanLaporanKeuangan().
// DIAGRAM: BuatLaporanKeuangan (pilih_periode)
void BuatLaporanKeuangan() {
    std::string pilih_periode;
    while (true) {
        // DIAGRAM: Input pilih_periode (bulan dan tahun)
        std::cout << "Input pilih_periode (bulan dan tahun, format MM-YYYY): ";
        std::getline(std::cin, pilih_periode);

        // Trim spasi
        while (!pilih_periode.empty() && std::isspace(static_cast<unsigned char>(pilih_periode.front()))) pilih_periode.erase(pilih_periode.begin());
        while (!pilih_periode.empty() && std::isspace(static_cast<unsigned char>(pilih_periode.back()))) pilih_periode.pop_back();

        // DIAGRAM: ValidasiPeriodeLaporan()
        // DIAGRAM: periode valid??
        if (!ValidasiPeriodeLaporan(pilih_periode)) {
            // DIAGRAM: Perbaiki data input (periode laporan tidak valid, pilih ulang)
            std::cout << "Perbaiki data input (periode laporan tidak valid, pilih ulang)\n";
            continue;
        }
        break;
    }

    // DIAGRAM: TampilkanLaporanKeuangan()
    TampilkanLaporanKeuangan(pilih_periode);

    // DIAGRAM: SelesaiAturanKembaliKeMenuUtama()
    SelesaiAturanKembaliKeMenuUtama();
}

// DIAGRAM: TampilkanLaporanKeuangan()
void TampilkanLaporanKeuangan(const std::string& periode) {
    // DIAGRAM: LaporanKeuangan lap: lap.periode, total_pemasukan = 0, total_pengeluaran = 0
    struct LaporanKeuangan lap;
    lap.periode = periode;
    lap.total_pemasukan = 0;
    lap.total_pengeluaran = 0;
    lap.sisa_saldo = 0;

    std::cout << "\n================ LAPORAN KEUANGAN ================\n";
    std::cout << "Periode: " << lap.periode << "\n";
    std::cout << "--------------------------------------------------\n";
    std::cout << "ID | Tanggal    | Jenis        | Kategori   | Nominal       | Catatan\n";
    std::cout << "--------------------------------------------------\n";

    // DIAGRAM: for (const auto& t : RiwayatTransaksi)
    for (const auto& t : RiwayatTransaksi) {
        // DIAGRAM: t.tanggal sesuai lap.periode??
        std::string t_periode = formatTanggal(t.tanggal).substr(3); // MM-YYYY
        if (t_periode == lap.periode) {
            // DIAGRAM: Tampilkan t
            // DIAGRAM: t.jenis == "pemasukan" ? total_pemasukan += t.nominal : total_pengeluaran += t.nominal
            std::cout << t.id_transaksi << " | "
                      << formatTanggal(t.tanggal) << " | "
                      << t.jenis << " | "
                      << t.kategori << " | "
                      << formatRupiah(t.nominal) << " | "
                      << t.catatan << "\n";
            if (t.jenis == "pemasukan") {
                lap.total_pemasukan += t.nominal;
            } else {
                lap.total_pengeluaran += t.nominal;
            }
        }
    }

    // DIAGRAM: lap.sisa_saldo = lap.total_pemasukan - lap.total_pengeluaran
    lap.sisa_saldo = lap.total_pemasukan - lap.total_pengeluaran;

    // DIAGRAM: Tampilkan laporan keuangan: periode, total_pemasukan, total_pengeluaran, sisa_saldo
    std::cout << "--------------------------------------------------\n";
    std::cout << "Periode           : " << lap.periode << "\n";
    std::cout << "Total pemasukan   : " << formatRupiah(lap.total_pemasukan) << "\n";
    std::cout << "Total pengeluaran : " << formatRupiah(lap.total_pengeluaran) << "\n";
    std::cout << "Sisa saldo        : " << formatRupiah(lap.sisa_saldo) << "\n";
    std::cout << "==================================================\n";
}

// DIAGRAM: SelesaiAturanKembaliKeMenuUtama()
void SelesaiAturanKembaliKeMenuUtama() {
    // Kembali ke menu utama
}
