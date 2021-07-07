
#ifndef KASPERSKYTEST_PIPE_H
#define KASPERSKYTEST_PIPE_H

#include <fstream>

enum class RemovePipeAfter
{
    on,
    off
};

/**
 * A humble high-level view of mkfifo.
 * The constructor takes an optional parameter 'removePipe' - an option that the destructor uses to
 * determine whether to remove the file/ By default is 'on'
 */
class Pipe
{
public:
    explicit Pipe(const std::string_view& pipeName, RemovePipeAfter removePipe = RemovePipeAfter::on);
    ~Pipe();

    void close();
    void operator>>(std::string& dest);
    void operator<<(const std::string_view& src);

private:
    const RemovePipeAfter removePipe_;
    const std::string_view pipeName_;
};

#endif //KASPERSKYTEST_PIPE_H
