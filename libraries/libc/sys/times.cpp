#include <sys/times.h>
#include <string.h>

clock_t times(struct tms *buff)
{
    memset(buff, 0, sizeof(struct tms));
    return 0;
}