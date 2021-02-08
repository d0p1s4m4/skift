#include <libsystem/io_new/Streams.h>
#include <libutils/Path.h>

int main(int argc, char **argv)
{
    if (argc == 1)
    {
        stream_format(err_stream, "usage: %s path\n", argv[0]);
        return PROCESS_FAILURE;
    }

    System::outln("{}", Path::parse(argv[1]).basename());

    return PROCESS_SUCCESS;
}
