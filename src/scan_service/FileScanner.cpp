#include "FileScanner.h"

#include <fstream>
#include "ScanReport.h"

std::pair<Suspicions::SuspicionType, size_t> FileScanner::scanFile(std::ifstream& file)
{
    std::string fileData;
    std::getline(file, fileData, '\0');
    file.close();
    const Suspicions::Suspicion* suspicion = nullptr;
    size_t index = defineSuspicionType(fileData, suspicion);
    size_t count = 0;

    while (index < fileData.size()) {
        index = fileData.find(suspicion->suspicion, index);
        if (index != std::string::npos) {
            count++;
        }
        else {
            break;
        }
        index++; // we increase index by one instead of suspicion->suspicion.size() because suspicions can overlap
    }
    return { suspicion ? suspicion->suspicionType : Suspicions::SuspicionType::None, count };
}

ScanReport FileScanner::scan(std::vector<std::string>::const_iterator& begin,
                             const std::vector<std::string>::const_iterator& end)
{
    ScanReport scanReport;
    for (; begin != end; ++begin) {
        scanReport.checkedFiles++;
        std::ifstream file(*begin);
        if (!file.is_open()) {
            scanReport.errors++;
        }
        else {
            const std::pair scanResult = scanFile(file);
            if (scanResult.first != Suspicions::SuspicionType::None) {
                scanReport.suspicions[static_cast<int>(scanResult.first)] += scanResult.second;
            }
        }
    }
    return scanReport;
}

size_t FileScanner::defineSuspicionType(const std::string& fileData, const Suspicions::Suspicion*& suspicion)
{
    size_t index;
    for (const auto& it : Suspicions::suspicionArray) {
        if ((index = fileData.find(it.suspicion)) != std::string::npos) {
            suspicion = &it;
            break;
        }
    }
    return index;
}
