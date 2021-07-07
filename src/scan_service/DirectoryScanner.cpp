#include "DirectoryScanner.h"

#include <iostream>
#include <filesystem>
#include <algorithm>
#include "ScanReport.h"
#include "FileScanner.h"

tm localtime(time_t time)
{
    tm result{};

    result.tm_hour = time / 3600;
    time -= result.tm_hour * 3600;
    result.tm_min = time / 60;
    time -= result.tm_min * 60;
    result.tm_sec = time;
    return result;
}

DirectoryScanner::DirectoryScanner(const std::string_view& pathToDirectory)
    : pathToDirectory_{ pathToDirectory }
{
}

size_t DirectoryScanner::getCountThreads()
{
    size_t result = std::thread::hardware_concurrency();
    return result ? result : 4;
}

std::vector<std::string> DirectoryScanner::getFilesList() const
{
    std::vector<std::string> result;
    for (const auto& file : std::filesystem::directory_iterator(pathToDirectory_)) {
        result.emplace_back(file.path().string());
    }
    return result;
}

std::string DirectoryScanner::scan()
{
    const time_t start = std::time(nullptr);
    const std::vector<std::string> filesList = getFilesList();
    std::vector<std::future<ScanReport>> fileScanResults = runFileScan(filesList);
    ScanReport scanReport = getFileScanResult(fileScanResults);
    const time_t finish = std::time(nullptr);

    scanReport.executionTime = localtime(finish - start);
    std::string reportMessage = getReportMessage(scanReport);
    return reportMessage;
}

std::vector<std::future<ScanReport>> DirectoryScanner::runFileScan(const std::vector<std::string>& filesList)
{
    std::vector<std::future<ScanReport>> futures;

    auto iterator = filesList.begin();
    const std::vector<int> countTasksPerThread = getCountTasksPerThread(filesList.size());
    futures.reserve(countTasksPerThread.size());
    for (const int& countTasks : countTasksPerThread) {
        futures.emplace_back(std::async(std::launch::async, [begin=iterator, end=iterator + countTasks]() mutable {
            return FileScanner::scan(begin, end);
        }));
        iterator += countTasks;
    }
    return futures;
}

ScanReport DirectoryScanner::getFileScanResult(std::vector<std::future<ScanReport>>& fileScanResults)
{
    ScanReport scanReport;

    std::for_each(fileScanResults.begin(), fileScanResults.end(), [&scanReport](auto& fileScanResult) {
        scanReport.append(fileScanResult.get());
    });
    return scanReport;
}

std::string DirectoryScanner::getReportMessage(const ScanReport& scanReport)
{
    char executionTime[10];
    strftime(executionTime, 10, "%H:%M:%S", &scanReport.executionTime);

    std::stringstream report;

    report << "====== Scan result ======\n"
              "Processed files: " << scanReport.checkedFiles << "\n";

    for (int i = 0; i < Suspicions::suspicionCount; ++i) {
        report << Suspicions::suspicionNames[i] << " detects: " << scanReport.suspicions[i] << "\n";
    }
    report << "Errors: " << scanReport.errors << "\n"
              "Execution time: " << executionTime << "\n"
              "=========================\n";
    return report.str();
}

std::vector<int> DirectoryScanner::getCountTasksPerThread(size_t countTasks)
{
    const size_t countThreads = getCountThreads();
    const size_t tasksPerThread = countTasks / countThreads;
    std::vector<int> result(std::min(countTasks, countThreads), tasksPerThread);

    for (int i = 0; i < countTasks % countThreads; ++i) {
        result[i]++;
    }
    return result;
}
