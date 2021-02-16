#pragma once

#include <libfile/Archive.h>

#include <libio/BinaryReader.h>
#include <libio/BinaryWriter.h>

namespace Compression
{

class ZipArchive : public Archive
{
private:
    void read_archive();
    void read_local_headers(BinaryReader &reader);
    Result read_central_directory(BinaryReader &reader);

    void write_archive();
    void write_entry(const Entry &entry, BinaryWriter &writer, Reader &compressed_data);
    void write_central_directory(BinaryWriter &writer);

public:
    ZipArchive(Path path, bool read = true);

    Result extract(unsigned int entry_index, const char *dest_path) override;
    Result insert(const char *entry_name, const char *src_path) override;
};

} // namespace Compression