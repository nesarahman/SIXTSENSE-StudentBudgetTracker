# Student Budget Tracker - Tim Sixth Sense

Aplikasi terminal C++17 untuk mencatat transaksi keuangan mahasiswa, pemantauan anggaran per kategori, dashboard otomatis, dan laporan bulanan yang telah diselaraskan persis dengan diagram alur sistem Sixth Sense (`Sixth Sense-Sistem Manajemen Keuangan dan Pelacak Anggaran Mahasiswa-revisi.drawio`).

## Struktur Proyek
- `src/models/`: Struktur data (`DataTransaksi`, `DataAnggaran`, `LaporanKeuangan`, `Date`).
- `src/transaksi/`: Alur pencatatan transaksi pemasukan dan pengeluaran, validasi, perbaikan data, dan penyimpanan.
- `src/anggaran/`: Pengaturan anggaran bulanan per kategori, pengecekan kecukupan anggaran, dan peringatan batas anggaran.
- `src/laporan/`: Pembuatan laporan bulanan periode MM-YYYY dan tampilan dashboard ringkasan serta grafik anggaran.
- `src/database/`: Sinkronisasi basis data file teks lokal (`data/transaksi.txt` dan `data/anggaran.txt`).
- `src/utils/`: Utilitas parsing tanggal (`Date.cpp`), pemformatan mata uang rupiah (`FormatRupiah.cpp`), dan validasi input (`Validasi.cpp`).
- `src/main.cpp`: Menu utama aplikasi (1. Transaksi, 2. Atur Anggaran, 3. Laporan Keuangan, Keluar).

## Cara Menjalankan di Windows
1. Buka terminal pada folder `StudentBudgetTracker`.
2. Kompilasi program menggunakan g++:
```bash
g++ -std=c++17 -Wall -Wextra src/main.cpp src/utils/Date.cpp src/utils/Validasi.cpp src/utils/FormatRupiah.cpp src/database/Database.cpp src/transaksi/Transaksi.cpp src/anggaran/Anggaran.cpp src/laporan/Laporan.cpp -o budget_tracker.exe
```
3. Jalankan aplikasi:
```bash
.\budget_tracker.exe
```

## Format Input
- Pilihan menu utama: `1`, `2`, `3`, atau `Keluar` (tidak peka huruf besar/kecil).
- Jenis transaksi: `pemasukan` atau `pengeluaran`.
- Tanggal transaksi: format `DD-MM-YYYY` (contoh: `12-11-2026`).
- Periode laporan: format `MM-YYYY` (contoh: `11-2026`).
- Nominal: angka atau dengan format rupiah (contoh: `500000` atau `500.000` atau `Rp 500.000`).

## Catatan Penyimpanan
Data transaksi dan anggaran secara otomatis tersimpan secara persisten pada file `data/transaksi.txt` dan `data/anggaran.txt`.
