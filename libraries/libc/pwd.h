#pragma once

#include <__libc__.h>

#include <sys/types.h>

__BEGIN_HEADER

struct passwd
{
    char *pw_name;
    uid_t pw_uid;
    gid_t pw_gid;
    char *pw_dir;
    char *pw_shell;
};

__END_HEADER