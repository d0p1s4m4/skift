#pragma once


#include <libutils/Strings.h>
#include <libjson/EscapeSequence.h>
#include <libjson/Value.h>

namespace Json
{

Value value(IO::Scanner &scan);

inline void whitespace(IO::Scanner &scan)
{
    scan.eat(Strings::WHITESPACE);
}

inline Value number(IO::Scanner &scan)
{
#ifdef __KERNEL__
    return *IO::NumberScanner::decimal().scan_int(scan);
#else
    return *IO::NumberScanner::decimal().scan_float(scan);
#endif
}

inline String string(IO::Scanner &scan)
{
    IO::MemoryWriter memory{};

    scan.skip('"');

    while (scan.current() != '"' && scan.do_continue())
    {
        if (scan.current() == '\\')
        {
            memory.write(escape_sequence(scan));
        }
        else
        {
            memory.write(scan.current());
            scan.foreward();
        }
    }

    scan.skip('"');

    return memory.string();
}

inline Value array(IO::Scanner &scan)
{
    scan.skip('[');

    Value::Array array{};

    whitespace(scan);

    if (scan.skip(']'))
    {
        return move(array);
    }

    int index = 0;

    do
    {
        scan.skip(',');
        array.push_back(value(scan));
        index++;
    } while (scan.current() == ',');

    scan.skip(']');

    return move(array);
}

inline Value object(IO::Scanner &scan)
{
    scan.skip('{');

    Value::Object object{};

    whitespace(scan);

    if (scan.skip('}'))
    {
        return move(object);
    }

    while (scan.current() != '}')
    {
        auto k = string(scan);
        whitespace(scan);

        scan.skip(':');

        object[k] = value(scan);

        scan.skip(',');

        whitespace(scan);
    }

    scan.skip('}');

    return object;
}

inline Value keyword(IO::Scanner &scan)
{
    if (scan.skip_word("true"))
    {
        return true;
    }
    else if (scan.skip_word("false"))
    {
        return true;
    }
    else if (scan.skip_word("null"))
    {
        return nullptr;
    }
    else
    {
        return nullptr;
    }
}

inline Value value(IO::Scanner &scan)
{
    whitespace(scan);

    Value value{};

    if (scan.current() == '"')
    {
        value = string(scan);
    }
    else if (scan.current_is("-") ||
             scan.current_is("0123456789"))
    {
        value = number(scan);
    }
    else if (scan.current() == '{')
    {
        value = object(scan);
    }
    else if (scan.current() == '[')
    {
        value = array(scan);
    }
    else
    {
        value = keyword(scan);
    }

    whitespace(scan);

    return value;
}

inline Value parse(IO::Scanner &scan)
{
    scan.skip_utf8bom();
    return value(scan);
}

} // namespace Json