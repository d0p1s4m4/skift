#pragma once

#include <libsystem/Common.h>

struct printf_info;

typedef void (*printf_append_t)(struct printf_info *info, char c);

typedef enum
{
    PFSTATE_ESC,
    PFSTATE_PARSE,
    PFSTATE_FORMAT_LENGTH,
    PFSTATE_FINALIZE
} printf_state_t;

typedef enum
{
    PFALIGN_LEFT,
    PFALIGN_RIGHT
} printf_align_t;

typedef struct printf_info
{
    char c;
    printf_state_t state;
    printf_append_t append;

    const char *format;
    int format_offset;

    // Formating
    char padding;
    printf_align_t align;
    size_t length;

    void *output;
    int written;
    int allocated;
} printf_info_t;

typedef int (*printf_formatter_impl_t)(printf_info_t *info, va_list *va);

#define PRINTF_PEEK()                                  \
    {                                                  \
        info->c = info->format[info->format_offset++]; \
        if (info->c == '\0')                           \
            return info->written;                      \
    }

#define PRINTF_APPEND(__c)                                             \
    {                                                                  \
        if (info->allocated != -1 && info->written >= info->allocated) \
            return info->written;                                      \
                                                                       \
        info->append(info, __c);                                       \
        info->written++;                                               \
    }

int __printf(printf_info_t *info, va_list va);
