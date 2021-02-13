#pragma once

#include <libutils/Slice.h>

#include <libsystem/io_new/Reader.h>
#include <libsystem/io_new/Seek.h>

namespace System
{

class MemoryReader final :
    public Reader,
    public Seek
{
private:
    Slice _memory;
    size_t _position = 0;

public:
    MemoryReader(Slice memory) : _memory(memory)
    {
    }

    ResultOr<size_t> read(void *buffer, size_t size) override
    {
        size_t remaining = MIN(_memory.size() - _position, size);

        memcpy(buffer, ((uint8_t *)_memory.start()) + _position, remaining);
        _position += remaining;

        return remaining;
    }

    ResultOr<size_t> seek(size_t pos, Whence whence) override
    {
        switch (whence)
        {
        case WHENCE_START:
            _position = position;
            break;
        case WHENCE_HERE:
            _position += position;
            break;
        case WHENCE_END:
            _position = _size + position;
            break;
        default:
            ASSERT_NOT_REACHED();
            break;
        }

        return _position;
    }

    ResultOr<size_t> tell() override
    {
        return _position;
    }
};

} // namespace System
