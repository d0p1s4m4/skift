#pragma once

#include <__libc__.h>
#include <sys/types.h>

__BEGIN_HEADER

struct tms
{
    clock_t tms_utime;
    clock_t tms_stime;
    clock_t tms_cutime;
    clock_t tms_cstime;
};

clock_t times(struct tms *buff);

__END_HEADER
