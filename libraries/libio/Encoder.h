#pragma once

#include <libio/Writer.h>
#include <libutils/Endian.h>

namespace IO::Encoder
{

/* --- Signed --------------------------------------------------------------- */

static ResultOr<size_t> encode_s8be(Writer &writer, be_int8_t value)
{
    return writer.write(&value, sizeof(value));
}

static ResultOr<size_t> encode_s16be(Writer &writer, be_int16_t value)
{
    return writer.write(&value, sizeof(value));
}

static ResultOr<size_t> encode_s32be(Writer &writer, be_int32_t value)
{
    return writer.write(&value, sizeof(value));
}

static ResultOr<size_t> encode_s64be(Writer &writer, be_int64_t value)
{
    return writer.write(&value, sizeof(value));
}

static ResultOr<size_t> encode_s8le(Writer &writer, le_int8_t value)
{
    return writer.write(&value, sizeof(value));
}

static ResultOr<size_t> encode_s16le(Writer &writer, le_int16_t value)
{
    return writer.write(&value, sizeof(value));
}

static ResultOr<size_t> encode_s32le(Writer &writer, le_int32_t value)
{
    return writer.write(&value, sizeof(value));
}

static ResultOr<size_t> encode_s64le(Writer &writer, le_int64_t value)
{
    return writer.write(&value, sizeof(value));
}

/* --- Unsigned ------------------------------------------------------------- */

static ResultOr<size_t> encode_u8(Writer &writer, uint8_t value)
{
    return writer.write(&value, sizeof(value));
}

static ResultOr<size_t> encode_u16(Writer &writer, uint16_t value)
{
    return writer.write(&value, sizeof(value));
}

static ResultOr<size_t> encode_u32(Writer &writer, uint32_t value)
{
    return writer.write(&value, sizeof(value));
}

static ResultOr<size_t> encode_u64(Writer &writer, uint64_t value)
{
    return writer.write(&value, sizeof(value));
}

} // namespace IO::Encoder
