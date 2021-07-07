#include <iostream>
#include <csignal>
#include "DirectoryScanner.h"
#include "Pipe.h"
#include "pipeName.h"

static bool working = true;
Pipe pipe(pipeName);

void runService()
{
    std::cout << "== Scan service is started ==\n";

    while (working) {
        std::string pathToDirectory;
        std::string reportMessage;

        pipe >> pathToDirectory;
        try {
            DirectoryScanner directoryScanner(pathToDirectory);
            reportMessage = directoryScanner.scan();
        }
        catch (std::exception& e) {
            reportMessage = e.what();
            reportMessage.append("\n");
        }
        pipe << reportMessage;
    }
    std::cout << "== Scan service is stopped ==\n";
}

int main()
{
    const auto signalHandler = [](int){
        working = false;
        pipe.close();
    };
    std::signal(SIGINT, signalHandler);
    std::signal(SIGTERM, signalHandler);
    runService();
    return 0;
}
