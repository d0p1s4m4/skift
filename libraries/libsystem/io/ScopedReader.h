#pragma once
#include <libsystem/io/Reader.h>
#include <libsystem/math/MinMax.h>

namespace IO
{

class ReadLimit final : public Reader
{
private:
    Reader &_reader;
    size_t _limit = 0;

public:
    ScopedReader(Reader &reader, size_t size);

    virtual size_t length() override;
    virtual size_t position() override;
    virtual size_t read(void *buffer, size_t size) override;
};

} // namespace IO
