#pragma once

#include <karm-base/cursor.h>
#include <karm-base/enum.h>
#include <karm-base/string.h>

namespace StupidFS {

static constexpr usize BLOCK_SIZE = 512;
static constexpr u32 MAGIC = 0x44505453; /** XXX: endianness */
static constexpr u8 REVISION = 1;

struct [[gnu::packed]] FreeList {
    u32 free[100];
    u8 nfree;
};

enum struct State : u16 {
    CLEANLY_UNMOUNTED = 0,
    ERROR = 1,
    DIRTY = 1,
};

struct [[gnu::packed]] SuperBlock {
    u32 magic;
    u32 isize;
    u32 fsize;
    FreeList freelist;
    u8 revision;
    u16 state;
    u64 time;
};

static constexpr u32 BAD_INODE = 0;
static constexpr u32 ROOT_INODE = 1;
static constexpr u32 BOOT_INODE = 2;

static constexpr int NDIR = 7;
static constexpr int SIND = 7; /* indirect */
static constexpr int DIND = 8; /* double indirect */
static constexpr int TIND = 9; /* triple indirect */

enum struct InodeFlag : u16 {
    ALLOCATED = 1 << 15,
    COMPRESSED = 1 << 1,
    ENCRYPTED = 1 << 2,
};

struct [[gnu::packed]] Inode {
    u16 mode;
    u16 nlink;
    u16 uid;
    u16 gid;
    u16 flags;
    u32 size;
    u32 zones[10];
    u64 actime;
    u64 modtime;
};

static constexpr usize INODES_PER_BLOCK = BLOCK_SIZE / sizeof(Inode);
static constexpr usize ZONES_PER_BLOCK = BLOCK_SIZE / sizeof(u32);

static constexpr usize NAME_MAX = 28;

struct [[gnu::packed]] DirEntry {
    u32 inum;
    char filename[NAME_MAX];
};

static constexpr usize DIRENTRY_PER_BLOCK = BLOCK_SIZE / sizeof(DirEntry);

struct Fs {
    Bytes _buf;

    Fs(Bytes cursor) : _buf(cursor) {}

    bool valid() const {
        return false;
    }

    Superblock &SuperBlock() {
        *(SuperBlock *)(_buf.buf() + BLOCK_SIZE);
    }
};
} // namespace StupidFS