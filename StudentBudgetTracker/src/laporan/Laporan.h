#ifndef LAPORAN_H
#define LAPORAN_H

#include <string>

// DIAGRAM: TampilkanDashboard()
void TampilkanDashboard();

// DIAGRAM: BuatLaporanKeuangan (pilih_periode)
void BuatLaporanKeuangan();

// DIAGRAM: ValidasiPeriodeLaporan()
bool ValidasiPeriodeLaporan(const std::string& periode);

// DIAGRAM: ValidasiPeriodeLaporanBulanan()
bool ValidasiPeriodeLaporanBulanan(const std::string& periode);

// DIAGRAM: TampilkanLaporanKeuangan()
void TampilkanLaporanKeuangan(const std::string& periode);

// DIAGRAM: SelesaiAturanKembaliKeMenuUtama()
void SelesaiAturanKembaliKeMenuUtama();

#endif
