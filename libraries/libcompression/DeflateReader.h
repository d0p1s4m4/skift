#pragma once

#include <libcompression/Inflate.h>
#include <libsystem/io/MemoryWriter.h>
#include <libsystem/io/Reader.h>
#include <libutils/Vector.h>

namespace Compression
{

class DeflateReader : public Reader
{
private:
    MemoryWriter _mem_buffer;
    Reader &_reader;
    Inflate _inflate;
    size_t _position = 0;

public:
    DeflateReader(Reader &reader);

    virtual size_t length() override;
    virtual size_t position() override;

    virtual size_t read(void *buffer, size_t size) override;
};

} // namespace Compression