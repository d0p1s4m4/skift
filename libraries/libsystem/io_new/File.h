#pragma once

#include <libutils/Path.h>

#include <libio/Reader.h>
#include <libio/Writer.h>
#include <libsystem/Handle.h>

namespace System
{

class File final :
    public Reader,
    public Writer,
    public Seek
{
private:
    System::Handle _handle;
    Optional<Path> _path;

public:
    const Optional<Path> &path() { return _path; }

    File(const char *path, OpenFlag flags);
    File(String path, OpenFlag flags);
    File(Path &path, OpenFlag flags);
    File(System::Handle &&handle);

    ResultOr<size_t> read(void *buffer, size_t size) override;
    ResultOr<size_t> write(const void *buffer, size_t size) override;

    ResultOr<size_t> seek(SeekFrom from) override;
    ResultOr<size_t> tell() override;

    ResultOr<size_t> length() override;

    bool exist();
};

} // namespace System
