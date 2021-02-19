#pragma once

#include <libutils/String.h>
#include <libutils/unicode/Codepoint.h>

#include <libio/Copy.h>
#include <libio/MemoryReader.h>

namespace IO
{

template <typename T>
static inline ResultOr<size_t> write(Writer &writer, T &what)
{
    return writer.write(&what, sizeof(T));
}

static inline ResultOr<size_t> write_char(Writer &writer, char v)
{
    return writer.write(&v, 1);
}

static inline ResultOr<size_t> write_uint8(Writer &writer, uint8_t v)
{
    return writer.write(&v, 1);
}

static inline ResultOr<size_t> write_cstring(Writer &writer, const char *cstring)
{
    return writer.write(cstring, strlen(cstring));
}

// Write a string as UTF-8
static inline ResultOr<size_t> write_string(Writer &writer, const String &string)
{
    return writer.write(string.cstring(), string.length());
}

// Write a code point as UTF-8
static inline ResultOr<size_t> write_codepoint(Writer &writer, Codepoint cp)
{
    char buffer[5];
    int length = codepoint_to_utf8(cp, (uint8_t *)buffer);
    return writer.write(buffer, length);
}

Result write_slice(Writer &writer, Slice data)
{
    MemoryReader memory{data};
    return copy(memory, writer);
}

} // namespace IO
