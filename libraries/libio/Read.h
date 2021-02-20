#pragma once

#include <libutils/Endian.h>
#include <libutils/Slice.h>
#include <libutils/String.h>

#include <libio/Copy.h>
#include <libio/MemoryWriter.h>
#include <libio/Reader.h>

namespace IO
{

template <typename T>
inline ResultOr<T> read(Reader &reader)
{
    T result;
    auto read_result = reader.read(&result, sizeof(T)).result();

    if (read_result != SUCCESS)
    {
        return read_result;
    }

    return result;
}

template <typename T>
inline ResultOr<T> read_little_endian(Reader &reader)
{
    auto value = read<LittleEndian<T>>(reader);

    if (!value)
    {
        return value.result();
    }

    return (*value)();
}

template <typename T>
inline ResultOr<T> read_big_endian(Reader &reader)
{
    auto value = read<BigEndian<T>>(reader);

    if (!value)
    {
        return value.result();
    }

    return (*value)();
}

static inline ResultOr<int8_t> read_int8(Reader &reader) { return read<int8_t>(reader); }
static inline ResultOr<int16_t> read_int16(Reader &reader) { return read<int16_t>(reader); }
static inline ResultOr<int32_t> read_int32(Reader &reader) { return read<int32_t>(reader); }
static inline ResultOr<int64_t> read_int64(Reader &reader) { return read<int64_t>(reader); }

static inline ResultOr<uint8_t> read_uint8(Reader &reader) { return read<uint8_t>(reader); }
static inline ResultOr<uint16_t> read_uint16(Reader &reader) { return read<uint16_t>(reader); }
static inline ResultOr<uint32_t> read_uint32(Reader &reader) { return read<uint32_t>(reader); }
static inline ResultOr<uint64_t> read_uint64(Reader &reader) { return read<uint64_t>(reader); }

static inline ResultOr<int8_t> read_le_int8(Reader &reader) { return read_little_endian<int8_t>(reader); }
static inline ResultOr<int16_t> read_le_int16(Reader &reader) { return read_little_endian<int16_t>(reader); }
static inline ResultOr<int32_t> read_le_int32(Reader &reader) { return read_little_endian<int32_t>(reader); }
static inline ResultOr<int64_t> read_le_int64(Reader &reader) { return read_little_endian<int64_t>(reader); }

static inline ResultOr<uint8_t> read_be_uint8(Reader &reader) { return read_big_endian<uint8_t>(reader); }
static inline ResultOr<uint16_t> read_be_uint16(Reader &reader) { return read_big_endian<uint16_t>(reader); }
static inline ResultOr<uint32_t> read_be_uint32(Reader &reader) { return read_big_endian<uint32_t>(reader); }
static inline ResultOr<uint64_t> read_be_uint64(Reader &reader) { return read_big_endian<uint64_t>(reader); }

static inline ResultOr<Slice> read_slice(Reader &reader)
{
    MemoryWriter memory;

    auto copy_result = copy(reader, memory);

    if (copy_result != SUCCESS)
    {
        return copy_result;
    }

    return Slice{memory.slice()};
}

static inline ResultOr<Slice> read_slice(Reader &reader, size_t n)
{
    MemoryWriter memory{n};

    auto copy_result = copy(reader, memory, n);

    if (copy_result != SUCCESS)
    {
        return copy_result;
    }

    return Slice{memory.slice()};
}

static inline ResultOr<String> read_string(Reader &reader)
{
    MemoryWriter memory;

    auto copy_result = copy(reader, memory);

    if (copy_result != SUCCESS)
    {
        return copy_result;
    }

    return String{memory.string()};
}

static inline ResultOr<String> read_string(Reader &reader, size_t n)
{
    MemoryWriter memory{n};

    auto copy_result = copy(reader, memory, n);

    if (copy_result != SUCCESS)
    {
        return copy_result;
    }

    return String{memory.string()};
}

} // namespace IO
