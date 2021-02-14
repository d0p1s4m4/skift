#pragma once

#include <libsystem/Common.h>
#include <libsystem/Result.h>

Result memory_alloc(size_t size, uintptr_t *out_address);

Result memory_free(uintptr_t address);

Result memory_include(int handle, uintptr_t *out_address, size_t *out_size);

Result memory_get_handle(uintptr_t address, int *out_handle);
