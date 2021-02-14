#pragma once

#include <abi/Syscalls.h>
#include <libsystem/io_new/File.h>

namespace System
{

class Pipe
{
private:
    File _reader;
    File _writer;

public:
    File &reade() { return _reader; }
    File &write() { return _writer; }

    Pipe()
    {
        int reader_handle = HANDLE_INVALID_ID;
        int writer_handle = HANDLE_INVALID_ID;

        hj_create_pipe(&reader_handle, writer_handle);

        _reader = {reader_handle};
        _writer = {writer_handle};
    }
};

} // namespace System
