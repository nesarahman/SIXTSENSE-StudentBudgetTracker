#include <iostream>
#include <string>
#include <algorithm>
#include <cctype>
#include "database/Database.h"
#include "transaksi/Transaksi.h"
#include "anggaran/Anggaran.h"
#include "laporan/Laporan.h"

// DIAGRAM: MenuUtama(): 1. menu Transaksi 2. Atur Anggaran 3. Laporan Keuangan
void MenuUtama() {
    std::cout << "\n====================================\n"
              << " STUDENT BUDGET TRACKER - SIXTH SENSE\n"
              << "====================================\n"
              << "1. Transaksi\n"
              << "2. Atur Anggaran\n"
              << "3. Laporan Keuangan\n"
              << "Ketik 'Keluar' untuk keluar dari program\n";
}

// DIAGRAM: Algoritma Menu Utama
int main() {
    // DIAGRAM: Mulai
    // DIAGRAM: BukaAplikasi
    BukaAplikasi();

    std::string pilihan;
    // DIAGRAM: Do
    do {
        MenuUtama();
        // DIAGRAM: Input Pilihan (1 / 2 / 3 / Keluar)
        std::cout << "Input Pilihan (1 / 2 / 3 / Keluar): ";
        if (!std::getline(std::cin, pilihan)) break;

        // Trim spasi
        while (!pilihan.empty() && std::isspace(static_cast<unsigned char>(pilihan.front()))) pilihan.erase(pilihan.begin());
        while (!pilihan.empty() && std::isspace(static_cast<unsigned char>(pilihan.back()))) pilihan.pop_back();

        std::string pilihan_lower = pilihan;
        for (char& c : pilihan_lower) c = static_cast<char>(std::tolower(static_cast<unsigned char>(c)));

        // DIAGRAM: input valid??
        if (pilihan != "1" && pilihan != "2" && pilihan != "3" && pilihan_lower != "keluar") {
            // DIAGRAM: Inputan tidak valid
            std::cout << "Inputan tidak valid\n";
            continue;
        }

        // DIAGRAM: switch
        if (pilihan == "1") {
            // DIAGRAM: Pilihan = 1 -> PilihMenuTransaksi()
            PilihMenuTransaksi();
        } else if (pilihan == "2") {
            // DIAGRAM: Pilihan = 2 -> Pilih atur anggaran -> AturAnggaranBulananBatasKategori()
            AturAnggaranBulananBatasKategori();
        } else if (pilihan == "3") {
            // DIAGRAM: Pilihan = 3 -> BuatLaporanKeuangan (pilih_periode)
            BuatLaporanKeuangan();
        } else if (pilihan_lower == "keluar") {
            // DIAGRAM: Pilihan = Keluar -> Selesai (pengguna keluar, program berhenti)
            std::cout << "Selesai (pengguna keluar, program berhenti)\n";
            break;
        }
        // Selesai satu fitur, kembali ke menu utama (perulangan sampai pengguna keluar)
    } while (true);

    return 0;
}
