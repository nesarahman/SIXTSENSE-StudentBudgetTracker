#include "Anggaran.h"
#include <iostream>
#include <algorithm>
#include <cctype>
#include "../database/Database.h"
#include "../utils/FormatRupiah.h"

// DIAGRAM: AturAnggaranBulananBatasKategori()
void AturAnggaranBulananBatasKategori() {
    std::string kategori;
    long long batas_anggaran = 0;
    bool pertama = true;

    while (true) {
        if (pertama) {
            std::cout << "Input kategori: ";
            std::getline(std::cin, kategori);
            // Trim spasi
            while (!kategori.empty() && std::isspace(static_cast<unsigned char>(kategori.front()))) kategori.erase(kategori.begin());
            while (!kategori.empty() && std::isspace(static_cast<unsigned char>(kategori.back()))) kategori.pop_back();

            std::string teks_nominal;
            std::cout << "Input batas_anggaran: ";
            std::getline(std::cin, teks_nominal);
            if (!parseNominalRupiah(teks_nominal, batas_anggaran)) {
                batas_anggaran = 0;
            }
            pertama = false;
        } else {
            // DIAGRAM: CekUlang PerbaikiData()
            if (kategori.empty()) {
                std::cout << "Perbaiki kategori: ";
                std::getline(std::cin, kategori);
                while (!kategori.empty() && std::isspace(static_cast<unsigned char>(kategori.front()))) kategori.erase(kategori.begin());
                while (!kategori.empty() && std::isspace(static_cast<unsigned char>(kategori.back()))) kategori.pop_back();
            }
            if (batas_anggaran <= 0) {
                std::string teks_nominal;
                std::cout << "Perbaiki batas_anggaran: ";
                std::getline(std::cin, teks_nominal);
                if (!parseNominalRupiah(teks_nominal, batas_anggaran)) {
                    batas_anggaran = 0;
                }
            }
        }

        // DIAGRAM: input valid??
        if (kategori.empty() || batas_anggaran <= 0) {
            std::cout << "Data tidak lengkap atau nominal tidak valid\n";
            continue;
        }
        break; // input valid
    }

    // DIAGRAM: kategori sudah ada di PengaturanAnggaran??
    auto it = std::find_if(PengaturanAnggaran.begin(), PengaturanAnggaran.end(),
                           [&](const DataAnggaran& a) { return a.kategori == kategori; });
    if (it != PengaturanAnggaran.end()) {
        // DIAGRAM: Update a.batas_anggaran a.sisa_anggaran = a.batas_anggaran - a.total_pengeluaran
        it->batas_anggaran = batas_anggaran;
        it->sisa_anggaran = it->batas_anggaran - it->total_pengeluaran;
    } else {
        // DIAGRAM: DataAnggaran a(kategori, batas_anggaran, 0, batas_anggaran) PengaturanAnggaran.push_back(a)
        DataAnggaran a(kategori, batas_anggaran, 0, batas_anggaran);
        PengaturanAnggaran.push_back(a);
    }

    // DIAGRAM: Pengaturan anggaran disimpan
    std::cout << "Pengaturan anggaran disimpan\n";

    // Semua perubahan data disimpan ke basis data
    SinkronisasiBasisData(DataTransaksi{}, PengaturanAnggaran, RiwayatTransaksi);
}

// CATATAN-DIAGRAM: Hitung ganda nominal dihindari dengan memeriksa a.total_pengeluaran > a.batas_anggaran karena nominal sudah ditambahkan pada PerbaruiSaldoTotal(). Parameter nominal tetap dipertahankan.
// DIAGRAM: CekKecukupanAnggaran() (kategori, nominal)
StatusAnggaran CekKecukupanAnggaran(const std::string& kategori, long long nominal) {
    (void)nominal; // Mencegah warning kompilator
    // DIAGRAM: for (const auto& a : PengaturanAnggaran)
    for (const auto& a : PengaturanAnggaran) {
        // DIAGRAM: a.kategori == kategori??
        if (a.kategori == kategori) {
            // DIAGRAM: a.total_pengeluaran + nominal > a.batas_anggaran ?? (menggunakan total_pengeluaran berjalan)
            if (a.total_pengeluaran > a.batas_anggaran) {
                return TERLAMPAUI;
            } else if (a.sisa_anggaran <= 0.20 * a.batas_anggaran) {
                // DIAGRAM: a.sisa_anggaran <= 20% a.batas_anggaran ??
                return HAMPIR_HABIS;
            } else {
                // DIAGRAM: status = aman (masih mencukupi)
                return AMAN;
            }
        }
    }
    // DIAGRAM: Anggaran kategori belum diatur (status = aman)
    return AMAN;
}

// DIAGRAM: TampilkanPeringatanAnggaranHampirHabisAtauTerlampaui()
void TampilkanPeringatanAnggaranHampirHabisAtauTerlampaui(StatusAnggaran status) {
    // DIAGRAM: status == terlampaui??
    if (status == TERLAMPAUI) {
        // DIAGRAM: Peringatan: anggaran kategori terlampaui
        std::cout << "Peringatan: anggaran kategori terlampaui\n";
    } else if (status == HAMPIR_HABIS) {
        // DIAGRAM: Peringatan: anggaran kategori hampir habis
        std::cout << "Peringatan: anggaran kategori hampir habis\n";
    }
}
