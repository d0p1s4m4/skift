#include <sys/time.h>

int gettimeofday(struct timeval *tv, struct timezone *tz)
{
    tv->tv_sec = 0;
    tv->tv_usec = 0;
    tz->tz_dsttime = 0;
    tz->tz_minuteswest = 0;
    return 0;
}