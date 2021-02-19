#pragma once

#include <libutils/Array.h>

#include <libio/Reader.h>
#include <libio/Writer.h>

namespace IO
{

constexpr int COPY_CHUNK_SIZE = 4096;

Result copy(Reader &from, Writer &to, size_t n)
{
    size_t remaining = n;

    do
    {
        Array<uint8_t, COPY_CHUNK_SIZE> copy_chunk;

        auto result_or_read = from.read(copy_chunk.raw_storage(), MIN(COPY_CHUNK_SIZE, remaining));

        if (!result_or_read)
        {
            return result_or_read.result();
        }

        if (*result_or_read == 0)
        {
            to.flush();
            return SUCCESS;
        }

        size_t chunk_size = *result_or_read;
        auto result_or_written = to.write(copy_chunk.raw_storage(), chunk_size);

        if (!result_or_written)
        {
            return result_or_written.result();
        }

        remaining -= chunk_size;

        if (*result_or_written == 0 || remaining == 0)
        {
            to.flush();
            return SUCCESS;
        }
    } while (1);
}

Result copy(Reader &from, Writer &to)
{
    do
    {
        Array<uint8_t, COPY_CHUNK_SIZE> copy_chunk;

        auto result_or_read = from.read(copy_chunk.raw_storage(), copy_chunk.count());

        if (!result_or_read)
        {
            return result_or_read.result();
        }

        if (*result_or_read == 0)
        {
            to.flush();
            return SUCCESS;
        }

        size_t chunk_size = *result_or_read;
        auto result_or_written = to.write(copy_chunk.raw_storage(), chunk_size);

        if (!result_or_written)
        {
            return result_or_written.result();
        }

        if (*result_or_written == 0)
        {
            to.flush();
            return SUCCESS;
        }
    } while (1);
}

} // namespace IO
