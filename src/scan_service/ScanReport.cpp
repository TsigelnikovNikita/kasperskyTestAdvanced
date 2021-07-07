#include "ScanReport.h"

#include "Suspicions.h"

void ScanReport::append(const ScanReport& scanReport)
{
    errors += scanReport.errors;
    checkedFiles += scanReport.checkedFiles;
    for (int i = 0; i < Suspicions::suspicionCount; ++i) {
        suspicions[i] += scanReport.suspicions[i];
    }
}
