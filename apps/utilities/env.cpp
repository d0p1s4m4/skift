#include <libio/Streams.h>
#include <skift/Environment.h>

int main(int, char const *[])
{
    System::outln("{}", environment_copy());
    return PROCESS_SUCCESS;
}
