#include <libjson/Json.h>

static Json::Value *_root = nullptr;

void environment_load(const char *buffer)
{
    if (_root)
    {
        delete _root;
    }

    IO::MemoryReader memory{buffer};

    IO::Scanner scanner{memory};
    auto json = Json::parse(scanner);

    _root = new Json::Value(move(json));
}

Json::Value &environment()
{
    assert(_root);

    return *_root;
}

String environment_copy()
{
    if (!_root)
    {
        return "{}";
    }

    IO::MemoryWriter memory;

    IO::Prettifier pretty{memory};
    Json::prettify(pretty, *_root);

    return memory.string();
}
