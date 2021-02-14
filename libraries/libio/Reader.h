#pragma once

#include <libio/Seek.h>
#include <libutils/ResultOr.h>

namespace IO
{

class Reader
{
public:
    virtual ResultOr<size_t> read(void *buffer, size_t size) = 0;

    virtual ResultOr<uint8_t> read_byte()
    {
        uint8_t byte = 0xfe;
        auto result = read(&byte, 1).result();

        if (result != SUCCESS)
        {
            return result;
        }
        else
        {
            return byte;
        }

        return result;
    };
};

template <typename T>
concept SeekableReader = IsBaseOf<Reader, T>::value &&IsBaseOf<Seek, T>::value;

} // namespace IO