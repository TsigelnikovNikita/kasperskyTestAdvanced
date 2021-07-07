#include "Pipe.h"
#include <sys/stat.h>
#include <cstring>

Pipe::Pipe(const std::string_view& pipeName, RemovePipeAfter removePipe)
    : pipeName_{ pipeName }
    , removePipe_{ removePipe }
{
    struct stat buffer{};
    if (stat(pipeName_.data(), &buffer) != 0) {
        mkfifo(pipeName_.data(), 0660);
    }
}

Pipe::~Pipe()
{
    close();
}

/**
 * Reads all available information from the pipe.
 */
void Pipe::operator>>(std::string& dest)
{
    std::ifstream stream(pipeName_.data());
    std::getline(stream, dest, '\0');
}

void Pipe::operator<<(const std::string_view& src)
{
    std::ofstream stream(pipeName_.data());
    stream << src;
}

/**
 * remove pipe file if it exists
 */
void Pipe::close()
{
    struct stat buffer{};

    if (removePipe_ == RemovePipeAfter::on && (stat(pipeName_.data(), &buffer) == 0)) {
        std::remove(pipeName_.data());
    }
}
