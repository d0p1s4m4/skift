#pragma once

#include <libsystem/Common.h>
#include <libsystem/Result.h>
#include <libsystem/io_new/File.h>

namespace Compression
{
struct Entry
{
    String name;
    size_t uncompressed_size;
    size_t compressed_size;
    size_t archive_offset;
    unsigned int compression;
};

class Archive : public RefCounted<Archive>
{
protected:
    Vector<Entry> _entries;
    System::Path _path;
    bool _valid = true;

public:
    static RefPtr<Archive> open(System::Path path, bool read = true);

    Archive(System::Path path) : _path(path)
    {
    }

    inline const Vector<Entry> &entries()
    {
        return _entries;
    }

    virtual Result extract(unsigned int entry_index, IO::Writer &writer) = 0;
    virtual Result insert(IO::Reader &reader, const char *src_dir) = 0;

    inline const System::Path &get_path()
    {
        return _path;
    }

    inline bool valid()
    {
        return _valid;
    }
};

} // namespace Compression
