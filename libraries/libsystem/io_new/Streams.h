#pragma once

#include <libutils/String.h>

#include <libio/Format.h>
#include <libio/MemoryWriter.h>
#include <libio/Reader.h>
#include <libio/Scanner.h>
#include <libio/Writer.h>
#include <libsystem/Handle.h>

namespace System
{

class InStream :
    public IO::Reader,
    public RawHandle
{
private:
    Handle _handle{0};

public:
    using Reader::read;

    ResultOr<size_t> read(void *buffer, size_t size) override { return _handle.read(buffer, size); }
    Handle &handle() override { return _handle; }
};

class OutStream :
    public IO::Writer,
    public RawHandle
{
private:
    Handle _handle{1};

public:
    using Writer::write;

    ResultOr<size_t> write(const void *buffer, size_t size) override { return _handle.write(buffer, size); }
    Handle &handle() override { return _handle; }
};

class ErrStream :
    public IO::Writer,
    public RawHandle

{
private:
    Handle _handle{2};

public:
    using Writer::write;

    ResultOr<size_t> write(const void *buffer, size_t size) override { return _handle.write(buffer, size); }
    Handle &handle() override { return _handle; }
};

class LogStream :
    public IO::Writer,
    public RawHandle
{
private:
    Handle _handle{3};

public:
    using Writer::write;

    ResultOr<size_t> write(const void *buffer, size_t size) override { return _handle.write(buffer, size); }
    Handle &handle() override { return _handle; }
};

InStream &in();

OutStream &out();

ErrStream &err();

LogStream &log();

static inline ResultOr<String> inln()
{
    IO::Scanner scan{in()};
    IO::MemoryWriter writer{};

    while (!(scan.ended() || scan.current() == '\n'))
    {
        writer.write(scan.current());
        out().write(scan.current());
        scan.foreward();
    }

    out().write('\n');
    scan.skip('\n');

    return String{writer.string()};
}

template <IO::Formatable... Args>
static ResultOr<size_t> print(Writer &writer, const char *fmt, Args... args)
{
    StringScanner scan{fmt, strlen(fmt)};
    auto format_result = format(writer, scan, forward<Args>(args)...);

    if (!format_result)
    {
        return format_result.result();
    }

    return *format_result;
}

template <Formatable... Args>
static ResultOr<size_t> println(Writer &writer, const char *fmt, Args... args)
{
    StringScanner scan{fmt, strlen(fmt)};
    auto format_result = format(writer, scan, forward<Args>(args)...);

    if (!format_result)
    {
        return format_result.result();
    }

    auto endline_result = writer.write('\n');

    if (endline_result != SUCCESS)
    {
        return endline_result;
    }

    return *format_result + 1;
}

template <Formatable... Args>
static ResultOr<size_t> out(const char *fmt, Args... args) { return print(out(), fmt, forward<Args>(args)...); }

template <Formatable... Args>
static ResultOr<size_t> outln(const char *fmt, Args... args) { return println(out(), fmt, forward<Args>(args)...); }

template <Formatable... Args>
static ResultOr<size_t> err(const char *fmt, Args... args) { return print(err(), fmt, forward<Args>(args)...); }

template <Formatable... Args>
static ResultOr<size_t> errln(const char *fmt, Args... args) { return println(err(), fmt, forward<Args>(args)...); }

template <Formatable... Args>
static ResultOr<size_t> log(const char *fmt, Args... args) { return print(log(), fmt, forward<Args>(args)...); }

template <Formatable... Args>
static ResultOr<size_t> logln(const char *fmt, Args... args) { return println(log(), fmt, forward<Args>(args)...); }

} // namespace System
