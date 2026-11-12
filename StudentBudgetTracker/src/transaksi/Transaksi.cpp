#include "Transaksi.h"
#include <iostream>
#include <algorithm>
#include <cctype>
#include "../database/Database.h"
#include "../anggaran/Anggaran.h"
#include "../laporan/Laporan.h"
#include "../utils/FormatRupiah.h"

// CATATAN-DIAGRAM: Typo jenis pada diagram (pengeluaran/pengeluaran) diputuskan menjadi (pemasukan / pengeluaran).
// DIAGRAM: PilihMenuTransaksi()
void PilihMenuTransaksi() {
    std::string jenis;
    while (true) {
        // DIAGRAM: Input jenis transaksi (pemasukan / pengeluaran)
        std::cout << "Input jenis transaksi (pemasukan / pengeluaran): ";
        if (!std::getline(std::cin, jenis)) return;

        // Trim spasi
        while (!jenis.empty() && std::isspace(static_cast<unsigned char>(jenis.front()))) jenis.erase(jenis.begin());
        while (!jenis.empty() && std::isspace(static_cast<unsigned char>(jenis.back()))) jenis.pop_back();

        std::string lower_jenis = jenis;
        for (char& c : lower_jenis) c = static_cast<char>(std::tolower(static_cast<unsigned char>(c)));

        // DIAGRAM: jenis valid??
        if (lower_jenis != "pemasukan" && lower_jenis != "pengeluaran") {
            // DIAGRAM: Inputan tidak valid
            std::cout << "Inputan tidak valid\n";
            continue;
        }

        // DIAGRAM: jenis == pemasukan??
        if (lower_jenis == "pemasukan") {
            // DIAGRAM: InputDataPemasukan()
            InputDataPemasukan();
        } else {
            // DIAGRAM: InputDataPengeluaran()
            InputDataPengeluaran();
        }
        break;
    }
}

// DIAGRAM: PerbaikiData()
void PerbaikiData(std::string& kategori, long long& nominal, std::string& teks_tanggal, Date& tanggal, const std::string& jenis) {
    if (nominal <= 0) {
        std::string teks;
        std::cout << "Perbaiki nominal: ";
        std::getline(std::cin, teks);
        if (!parseNominalRupiah(teks, nominal)) {
            nominal = 0;
        }
    }
    if (kategori.empty()) {
        if (jenis == "pemasukan") {
            std::cout << "Perbaiki sumber_dana: ";
        } else {
            std::cout << "Perbaiki kategori: ";
        }
        std::getline(std::cin, kategori);
        while (!kategori.empty() && std::isspace(static_cast<unsigned char>(kategori.front()))) kategori.erase(kategori.begin());
        while (!kategori.empty() && std::isspace(static_cast<unsigned char>(kategori.back()))) kategori.pop_back();
    }
    if (teks_tanggal.empty()) {
        std::cout << "Perbaiki tanggal (DD-MM-YYYY): ";
        std::getline(std::cin, teks_tanggal);
        while (!teks_tanggal.empty() && std::isspace(static_cast<unsigned char>(teks_tanggal.front()))) teks_tanggal.erase(teks_tanggal.begin());
        while (!teks_tanggal.empty() && std::isspace(static_cast<unsigned char>(teks_tanggal.back()))) teks_tanggal.pop_back();
        if (!parseTanggal(teks_tanggal, tanggal)) {
            teks_tanggal = "";
        }
    }
}

// DIAGRAM: ValidasiDataTransaksi()
bool ValidasiDataTransaksi(std::string& kategori, long long& nominal, std::string& teks_tanggal, Date& tanggal, const std::string& jenis) {
    while (true) {
        // DIAGRAM: tanggal / kategori kosong || nominal <= 0 ??
        if (teks_tanggal.empty() || kategori.empty() || nominal <= 0) {
            // DIAGRAM: Data tidak lengkap atau nominal tidak valid
            std::cout << "Data tidak lengkap atau nominal tidak valid\n";
            // DIAGRAM: CekUlang -> PerbaikiData()
            PerbaikiData(kategori, nominal, teks_tanggal, tanggal, jenis);
            continue;
        }
        break; // sampai valid -> return true (data valid)
    }
    // DIAGRAM: return true (data valid)
    return true;
}

// DIAGRAM: InputDataPemasukan()
void InputDataPemasukan() {
    std::string teks_nominal;
    long long nominal = 0;
    std::string sumber_dana;
    std::string teks_tanggal;
    Date tanggal;
    std::string catatan;

    // DIAGRAM: Input nominal, sumber_dana, tanggal
    std::cout << "Input nominal: ";
    std::getline(std::cin, teks_nominal);
    if (!parseNominalRupiah(teks_nominal, nominal)) {
        nominal = 0;
    }

    std::cout << "Input sumber_dana: ";
    std::getline(std::cin, sumber_dana);
    while (!sumber_dana.empty() && std::isspace(static_cast<unsigned char>(sumber_dana.front()))) sumber_dana.erase(sumber_dana.begin());
    while (!sumber_dana.empty() && std::isspace(static_cast<unsigned char>(sumber_dana.back()))) sumber_dana.pop_back();

    std::cout << "Input tanggal (DD-MM-YYYY): ";
    std::getline(std::cin, teks_tanggal);
    while (!teks_tanggal.empty() && std::isspace(static_cast<unsigned char>(teks_tanggal.front()))) teks_tanggal.erase(teks_tanggal.begin());
    while (!teks_tanggal.empty() && std::isspace(static_cast<unsigned char>(teks_tanggal.back()))) teks_tanggal.pop_back();
    if (!parseTanggal(teks_tanggal, tanggal)) {
        teks_tanggal = "";
    }

    // CATATAN-DIAGRAM: Catatan transaksi tetap ditanyakan dan boleh kosong sesuai Dekomposisi dan Abstraksi Struct.
    std::cout << "Input catatan (boleh kosong): ";
    std::getline(std::cin, catatan);
    while (!catatan.empty() && std::isspace(static_cast<unsigned char>(catatan.front()))) catatan.erase(catatan.begin());
    while (!catatan.empty() && std::isspace(static_cast<unsigned char>(catatan.back()))) catatan.pop_back();

    // CATATAN-DIAGRAM: Kategori pada transaksi pemasukan disamakan dengan sumber_dana (t.kategori = t.sumber_dana) karena form pemasukan tidak memiliki input kategori terpisah.
    std::string kategori = sumber_dana;

    // DIAGRAM: ValidasiDataTransaksi()
    ValidasiDataTransaksi(kategori, nominal, teks_tanggal, tanggal, "pemasukan");
    sumber_dana = kategori;

    // DIAGRAM: DataTransaksi t: id_transaksi, tanggal, jenis = "pemasukan", kategori, sumber_dana, nominal, catatan
    DataTransaksi t;
    t.tanggal = tanggal;
    t.jenis = "pemasukan";
    t.kategori = kategori;
    t.sumber_dana = sumber_dana;
    t.nominal = nominal;
    t.catatan = catatan;

    AlurSimpanTransaksi(t);
}

// DIAGRAM: InputDataPengeluaran()
void InputDataPengeluaran() {
    std::string teks_nominal;
    long long nominal = 0;
    std::string kategori;
    std::string teks_tanggal;
    Date tanggal;
    std::string catatan;

    // DIAGRAM: Input nominal, kategori, tanggal
    std::cout << "Input nominal: ";
    std::getline(std::cin, teks_nominal);
    if (!parseNominalRupiah(teks_nominal, nominal)) {
        nominal = 0;
    }

    std::cout << "Input kategori: ";
    std::getline(std::cin, kategori);
    while (!kategori.empty() && std::isspace(static_cast<unsigned char>(kategori.front()))) kategori.erase(kategori.begin());
    while (!kategori.empty() && std::isspace(static_cast<unsigned char>(kategori.back()))) kategori.pop_back();

    std::cout << "Input tanggal (DD-MM-YYYY): ";
    std::getline(std::cin, teks_tanggal);
    while (!teks_tanggal.empty() && std::isspace(static_cast<unsigned char>(teks_tanggal.front()))) teks_tanggal.erase(teks_tanggal.begin());
    while (!teks_tanggal.empty() && std::isspace(static_cast<unsigned char>(teks_tanggal.back()))) teks_tanggal.pop_back();
    if (!parseTanggal(teks_tanggal, tanggal)) {
        teks_tanggal = "";
    }

    // CATATAN-DIAGRAM: Catatan transaksi tetap ditanyakan dan boleh kosong sesuai Dekomposisi dan Abstraksi Struct.
    std::cout << "Input catatan (boleh kosong): ";
    std::getline(std::cin, catatan);
    while (!catatan.empty() && std::isspace(static_cast<unsigned char>(catatan.front()))) catatan.erase(catatan.begin());
    while (!catatan.empty() && std::isspace(static_cast<unsigned char>(catatan.back()))) catatan.pop_back();

    // DIAGRAM: ValidasiDataTransaksi()
    ValidasiDataTransaksi(kategori, nominal, teks_tanggal, tanggal, "pengeluaran");

    // DIAGRAM: DataTransaksi t: id_transaksi, tanggal, jenis = "pengeluaran", kategori, nominal, catatan
    DataTransaksi t;
    t.tanggal = tanggal;
    t.jenis = "pengeluaran";
    t.kategori = kategori;
    t.sumber_dana = "";
    t.nominal = nominal;
    t.catatan = catatan;

    AlurSimpanTransaksi(t);
}

// DIAGRAM: SimpanKeBasisData()
void SimpanKeBasisData(DataTransaksi& t) {
    // DIAGRAM: t.id_transaksi = RiwayatTransaksi.size() + 1
    t.id_transaksi = static_cast<int>(RiwayatTransaksi.size()) + 1;
    // DIAGRAM: RiwayatTransaksi .push_back(t)
    RiwayatTransaksi.push_back(t);
    // DIAGRAM: Transaksi tersimpan
    std::cout << "Transaksi tersimpan\n";
}

// DIAGRAM: PerbaruiSaldoTotal()
void PerbaruiSaldoTotal(const DataTransaksi& t) {
    // DIAGRAM: t.jenis == "pemasukan"??
    if (t.jenis == "pemasukan") {
        // DIAGRAM: LaporanKeuangan.total_pemasukan += t.nominal LaporanKeuangan.sisa_saldo += t.nominal
        LaporanKeuangan.total_pemasukan += t.nominal;
        LaporanKeuangan.sisa_saldo += t.nominal;
    } else if (t.jenis == "pengeluaran") {
        // DIAGRAM: LaporanKeuangan.total_pengeluaran += t.nominal LaporanKeuangan.sisa_saldo -= t.nominal a.total_pengeluaran += t.nominal (a.kategori == t.kategori) a.sisa_anggaran = a.batas_anggaran - a.total_pengeluaran
        LaporanKeuangan.total_pengeluaran += t.nominal;
        LaporanKeuangan.sisa_saldo -= t.nominal;
        for (auto& a : PengaturanAnggaran) {
            if (a.kategori == t.kategori) {
                a.total_pengeluaran += t.nominal;
                a.sisa_anggaran = a.batas_anggaran - a.total_pengeluaran;
            }
        }
    }
}

// DIAGRAM: Algoritma Simpan Transaksi
void AlurSimpanTransaksi(DataTransaksi& t) {
    // DIAGRAM: SimpanKeBasisData() (simpan transaksi t)
    SimpanKeBasisData(t);

    // DIAGRAM: PerbaruiSaldoTotal()
    PerbaruiSaldoTotal(t);

    // DIAGRAM: SinkronisasiBasisData (transaksi, anggaran, riwayat)
    SinkronisasiBasisData(t, PengaturanAnggaran, RiwayatTransaksi);

    // DIAGRAM: CekKecukupanAnggaran() (kategori, nominal)
    StatusAnggaran status = CekKecukupanAnggaran(t.kategori, t.nominal);

    // DIAGRAM: sisa anggaran kategori masih mencukupi??
    if (status != AMAN) {
        // DIAGRAM: TampilkanPeringatanAnggaran HampirHabisAtauTerlampaui()
        TampilkanPeringatanAnggaranHampirHabisAtauTerlampaui(status);
    }

    // DIAGRAM: TampilkanDashboard()
    TampilkanDashboard();

    // DIAGRAM: Selesai / kembali ke menu utama
}
