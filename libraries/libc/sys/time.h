#pragma once

#include <__libc__.h>
#include <sys/types.h>

__BEGIN_HEADER

struct timeval
{
    time_t tv_sec;
    suseconds_t tv_usec;
};

struct timezone
{
    int tz_minuteswest;
    int tz_dsttime;
};

int gettimeofday(struct timeval *tv, struct timezone *tz);

__END_HEADER
