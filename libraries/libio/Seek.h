#pragma once

#include <abi/Handle.h>
#include <libutils/ResultOr.h>

namespace IO
{

enum class Whence : uint8_t
{
    START = HJ_WHENCE_START,
    CURRENT = HJ_WHENCE_CURRENT,
    END = HJ_WHENCE_END,
};

struct SeekFrom
{
    Whence whence;
    size_t position;

    static SeekFrom start(size_t position = 0)
    {
        return {Whence::START, position};
    }

    static SeekFrom end(size_t position = 0)
    {
        return {Whence::CURRENT, position};
    }

    static SeekFrom current(size_t position = 0)
    {
        return {Whence::END, position};
    }
};

class Seek
{
public:
    virtual ResultOr<size_t> seek(SeekFrom from) = 0;
    virtual ResultOr<size_t> tell() = 0;

    virtual ResultOr<size_t> length()
    {
        ResultOr<size_t> original_position = seek(SeekFrom::current());

        if (!original_position)
        {
            return original_position.result();
        }

        ResultOr<size_t> end_position = seek(SeekFrom::end());

        if (!end_position)
        {
            return end_position.result();
        }

        ResultOr<size_t> back_to_original_position = seek(SeekFrom::start(*original_position));

        if (!back_to_original_position)
        {
            return back_to_original_position.result();
        }

        return *end_position;
    }
};

} // namespace IO