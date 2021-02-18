#pragma once

#include <libio/Writer.h>
#include <libutils/String.h>
#include <libutils/unicode/Codepoint.h>

namespace IO
{

static inline ResultOr<size_t> write(Writer &writer, char v)
{
    return writer.write(&v, 1);
}

static inline ResultOr<size_t> write(Writer &writer, uint8_t v)
{
    return writer.write(&v, 1);
}

static inline ResultOr<size_t> write(Writer &writer, const char *cstring)
{
    return writer.write(cstring, strlen(cstring));
}

static inline ResultOr<size_t> write(Writer &writer, const String &string)
{
    return writer.write(string.cstring(), string.length());
}

static inline ResultOr<size_t> write(Writer &writer, Codepoint cp)
{
    char buffer[5];
    int length = codepoint_to_utf8(cp, (uint8_t *)buffer);
    return writer.write(buffer, length);
}

} // namespace IO
