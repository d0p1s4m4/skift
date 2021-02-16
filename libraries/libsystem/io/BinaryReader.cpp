#include <libsystem/io/BinaryReader.h>

// Inherited from SeekableReader
size_t BinaryReader::length()
{
    return _reader.length();
}

size_t BinaryReader::position()
{
    return _reader.position();
}

size_t BinaryReader::seek(SeekFrom from)
{
    return _reader.seek(pos, whence);
}

size_t BinaryReader::read(void *buffer, size_t size)
{
    return _reader.read(buffer, size);
}