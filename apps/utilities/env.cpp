#include <libsystem/io_new/Streams.h>
#include <libsystem/process/Environment.h>

int main(int, char const *[])
{
    System::outln("{}", environment_copy());
    return PROCESS_SUCCESS;
}
