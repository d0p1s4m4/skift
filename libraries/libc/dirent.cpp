#include <dirent.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include <abi/Syscalls.h>

DIR *opendir(const char *name)
{
    int handle = 0;
    Result result = hj_handle_open(&handle, name, strlen(name), OPEN_READ | OPEN_DIRECTORY);
    if (result != Result::SUCCESS)
    {
        return NULL;
    }

    DIR *dir = (DIR *)malloc(sizeof(DIR));
    dir->handle = handle;
    return dir;
}

struct dirent *readdir(DIR *dir)
{
    static struct dirent direntry;
    size_t read;
    DirectoryEntry entry;
    Result result;

    result = hj_handle_read(dir->handle, &entry, sizeof(entry), &read);
    if (result == Result::SUCCESS && read > 0)
    {
        strcpy(direntry.d_name, entry.name);
        read = strlen(entry.name);
        direntry.d_name[read] = '\0';
        return &direntry;
    }
    return NULL;
}

int scandir(const char *dir, struct dirent ***namelist,
            int (*select)(const struct dirent *),
            int (*compar)(const void *, const void *))
{
    __unused(dir);
    __unused(namelist);
    __unused(select);
    __unused(compar);

    return 0;
}

void seekdir(DIR *dir, off_t offset)
{
    __unused(dir);
    __unused(offset);
}

off_t telldir(DIR *dir)
{
    __unused(dir);
    return 0;
}

void rewinddir(DIR *dir)
{
    __unused(dir);
}

int closedir(DIR *dir)
{
    Result result = hj_handle_close(dir->handle);
    free(dir);

    return result == Result::SUCCESS ? 0 : -1;
}