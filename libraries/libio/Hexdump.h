#pragma once

#include <ctype.h>

#include <libio/Format.h>
#include <libio/Reader.h>
#include <libio/Writer.h>

namespace IO
{

inline Result hexdump(Reader &reader, Writer &writer)
{
    char buffer[16];
    auto read_result = reader.read(buffer, sizeof(buffer));
    size_t offset;

    while (read_result)
    {
        format(writer, "{06x}: ", offset);

        for (size_t i = 0; i < 16; i++)
        {
            if (i < *read_result)
            {
                format(writer, "{02x} ", buffer[i]);
            }
            else
            {
                format(writer, "   ");
            }
        }

        format(writer, " | ");

        for (size_t i = 0; i < 16; i++)
        {
            if (i < *read_result)
            {
                char c = isprint(buffer[i]) ? buffer[i] : '.';

                format(writer, "{c}", c);
            }
        }

        format(writer, "\n");

        offset += 16;
        reader.read(buffer, sizeof(buffer));
    }
}

} // namespace IO