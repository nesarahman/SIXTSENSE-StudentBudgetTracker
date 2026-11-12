#ifndef FORMAT_RUPIAH_H
#define FORMAT_RUPIAH_H

#include <string>

std::string formatRupiah(long long nominal);
bool parseNominalRupiah(const std::string& teks, long long& hasil);

#endif
