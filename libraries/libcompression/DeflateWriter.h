#pragma once

#include <libcompression/Deflate.h>
#include <libsystem/io/MemoryWriter.h>
#include <libsystem/io/Writer.h>

namespace Compression
{

class DeflateWriter : public Writer
{
private:
    Deflate _deflate;
    MemoryWriter _mem_buffer;
    Writer &_writer;

public:
    DeflateWriter(Writer &writer, int level = 5);
    ~DeflateWriter();

    virtual size_t length() override;
    virtual size_t position() override;

    virtual void flush() override;
    virtual size_t write(const void *buffer, size_t size) override;
};

} // namespace Compression