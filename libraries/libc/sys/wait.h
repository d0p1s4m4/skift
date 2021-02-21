#pragma once

#include <__libc__.h>
#include <sys/types.h>

__BEGIN_HEADER

pid_t wait(int *stat_loc);
pid_t waitpid(pid_t pid, int *stat_loc, int options);

__END_HEADER