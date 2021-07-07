#include <iostream>
#include "Pipe.h"
#include "pipeName.h"

void exitWithError(const std::string_view& message)
{
    std::cerr << message << std::endl;
    std::exit(-1);
}

int main(int ac, char** av)
{
    Pipe pipe(pipeName, RemovePipeAfter::off);
    std::string reportMessage;

    if (ac != 2) {
        exitWithError("I need the path to the directory in the argument");
    }
    pipe << av[1];
    pipe >> reportMessage;
    std::cout << reportMessage;
    return 0;
}
