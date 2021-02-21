#pragma once

#include <__libc__.h>

__BEGIN_HEADER

#define NCCS 20

#define VEOF 0
#define VEOL 1
#define VERASE 2
#define VINTR 3
#define VKILL 4
#define VQUIT 5
#define VSTART 6
#define VSTOP 7
#define VSUSP 8

typedef unsigned char cc_t;
typedef long speed_t;
typedef unsigned long tcflag_t;

struct termios
{
    tcflag_t c_iflag;
    tcflag_t c_oflag;
    tcflag_t c_cflag;
    tcflag_t c_lflag;
    cc_t c_cc[NCCS];
};

__END_HEADER