#ifndef KASPERSKYTEST_SCANREPORT_H
#define KASPERSKYTEST_SCANREPORT_H


#include <array>
#include "Suspicions.h"

struct ScanReport
{
    std::array<size_t, Suspicions::suspicionCount> suspicions{};
    size_t errors = 0;
    size_t checkedFiles = 0;
    tm executionTime{};

    void append(const ScanReport& scanReport);
};


#endif //KASPERSKYTEST_SCANREPORT_H
