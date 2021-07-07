#ifndef KASPERSKYTEST_DIRECTORYSCANNER_H
#define KASPERSKYTEST_DIRECTORYSCANNER_H

#include <vector>
#include <future>

class ScanReport;

class DirectoryScanner
{
public:
    explicit DirectoryScanner(const std::string_view& pathToDirectory);

    std::string scan();
private:
    std::string_view pathToDirectory_;

    std::vector<std::string> getFilesList() const;
    static std::vector<std::future<ScanReport>> runFileScan(const std::vector<std::string>& filesList);
    static ScanReport getFileScanResult(std::vector<std::future<ScanReport>>& fileScanResults);
    static std::string getReportMessage(const ScanReport& scanReport);
    static size_t getCountThreads();
    static std::vector<int> getCountTasksPerThread(size_t countTasks);
};


#endif //KASPERSKYTEST_DIRECTORYSCANNER_H
