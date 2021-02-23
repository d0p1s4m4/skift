#pragma once

#include <__libc__.h>
#include <sys/types.h>

__BEGIN_HEADER

typedef struct
{
    int handle;
} DIR;

struct dirent
{
    char d_name[256];
};

DIR *opendir(const char *name);
struct dirent *readdir(DIR *dir);
int scandir(const char *dir, struct dirent ***namelist,
            int (*select)(const struct dirent *),
            int (*compar)(const void *, const void *));
void seekdir(DIR *dir, off_t offset);
off_t telldir(DIR *dir);
void rewinddir(DIR *dir);
int closedir(DIR *dir);

__END_HEADER
