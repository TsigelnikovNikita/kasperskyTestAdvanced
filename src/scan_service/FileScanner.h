#ifndef KASPERSKYTEST_FILESCANNER_H
#define KASPERSKYTEST_FILESCANNER_H


#include <vector>
#include <string>

namespace Suspicions
{
    enum class SuspicionType;
    struct Suspicion;
}
struct ScanReport;

class FileScanner
{
public:
    static ScanReport scan(std::vector<std::string>::const_iterator& begin,
                           const std::vector<std::string>::const_iterator& end);

private:
    static std::pair<Suspicions::SuspicionType, size_t> scanFile(std::ifstream& file);
    static size_t defineSuspicionType(const std::string& fileData, const Suspicions::Suspicion*& suspicion);
};


#endif //KASPERSKYTEST_FILESCANNER_H
