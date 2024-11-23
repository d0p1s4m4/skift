#pragma once

#include <karm-base/array.h>
#include <karm-base/slice.h>

namespace Karm::Crypto {

static constexpr usize SHA224_BYTES = 28;
static constexpr usize SHA256_BYTES = 32;
static constexpr usize SHA384_BYTES = 48;
static constexpr usize SHA512_BYTES = 64;

class Sha2 {
public:
    void init() {}

    void update(String str) {
        update(Bytes(str));
    }

    void update(Bytes bytes) {}

    Bytes digest() { return Bytes(); }

    Res<String> hexDigest() {
        return hexEncode(digest());
    };
}

class Sha256 : public Sha2 {
public:
    void init();

    void update(Bytes bytes);
    Bytes digest();

protected:
    Array<u32, 8> state;
};

class Sha224 : public Sha256 {
public:
    void init();
    Bytes digest();
};

class Sha512 : public Sha2 {
public:
    void init();
    void update(Bytes bytes);
    Bytes digest();

protected:
    Array<u64, 8> state;
};

class Sha384 : public Sha512 {
public:
    void init();
    Bytes digest();
};

Bytes sha224(Bytes bytes);
Bytes sha256(Bytes bytes);
Bytes sha384(Bytes bytes);
Bytes sha512(Bytes bytes);

} // namespace Karm::Crypto