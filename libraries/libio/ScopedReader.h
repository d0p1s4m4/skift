#pragma once

#include <assert.h>

#include <libio/Reader.h>
#include <libio/Seek.h>
#include <libsystem/math/MinMax.h>

namespace IO
{

template <SeekableReader TReader>
class ScopedReader final :
    public Reader,
    public Seek
{
private:
    TReader _reader;

    size_t _start = 0;
    size_t _size = 0;

public:
    ScopedReader(TReader reader, size_t size)
        : _reader(reader)
    {
        _start = *_reader.tell();
        _size = MIN(reader.length() - _start_pos, size);
    }

    virtual ResultOr<size_t> read(void *buffer, size_t size) override
    {

        auto position_or_result = _reader.tell();

        if (!position_or_result)
        {
            return position_or_result;
        }

        if (*position_or_result < _start)
        {
            return 0;
        }

        if (*position_or_result >= _start + _size)
        {
            return 0;
        }

        auto length_or_result = _reader.length();

        if (!length_or_result)
        {
            return length_or_result;
        }

        auto offset = *position_or_result - _start;

        size_t remaining = MIN(_size - _offset, size);
        return _reader.read(buffer, remaining);
    }

    virtual ResultOr<size_t> seek(SeekFrom from) override
    {
        switch (from.whence)
        {
        case HJ_WHENCE_START:
        {
            auto offset = _start + from.position;

            offset = MAX(_start, offset);
            offset = MIN(_start + _size, offset);

            return _reader.seek(SeekFrom::start(offset));
        }

        case HJ_WHENCE_CURRENT:
        {
            auto offset = *_reader.tell() + from.position;

            offset = MAX(_start, offset);
            offset = MIN(_start + _size, offset);

            return _reader.seek(SeekFrom::start(from.position));
        }

        case HJ_WHENCE_END:
            auto offset = *_reader.length() + from.position;

            offset = MAX(_start, offset);
            offset = MIN(_start + _size, offset);

            return _reader.seek(SeekFrom::end(from.position));

        default:
            ASSERT_NOT_REACHED();
        }
    }

    virtual ResultOr<size_t> tell() override
    {
        auto offset_or_result = _reader.tell();

        if (!offset_or_result)
        {
            return offset_or_result;
        }

        auto offset = *offset_or_result;

        offset = MAX(_start, offset);
        offset = MIN(_start + _size, offset);

        return offset;
    }

    virtual ResultOr<size_t> length() override
    {
        auto result_or_length = _reader.length();

        if (!result_or_length)
        {
            return result_or_length;
        }

        if (*result_or_length < _start)
        {
            return 0;
        }

        return MIN(_size, *result_or_length - _start);
    }
};

} // namespace IO
