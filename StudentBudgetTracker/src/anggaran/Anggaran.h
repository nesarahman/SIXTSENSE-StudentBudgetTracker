#ifndef ANGGARAN_H
#define ANGGARAN_H

#include <string>
#include "../models/DataAnggaran.h"

// DIAGRAM: AturAnggaranBulananBatasKategori()
void AturAnggaranBulananBatasKategori();

// DIAGRAM: CekKecukupanAnggaran() (kategori, nominal)
StatusAnggaran CekKecukupanAnggaran(const std::string& kategori, long long nominal);

// DIAGRAM: TampilkanPeringatanAnggaranHampirHabisAtauTerlampaui()
void TampilkanPeringatanAnggaranHampirHabisAtauTerlampaui(StatusAnggaran status);

#endif
