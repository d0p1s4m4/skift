#pragma once

#include <libutils/json/Value.h>

namespace json
{

Value value(Scanner &scan);

static Value value(Scanner &scan);

static void whitespace(Scanner &scan)
{
    scan.eat(Strings::WHITESPACE);
}

static Value number(Scanner &scan)
{
#ifdef __KERNEL__
    return Value{scan_int(scan, 10)};
#else
    return {scan_float(scan)};
#endif
}

static String string(Scanner &scan)
{
    StringBuilder builder{};

    scan.skip('"');

    while (scan.current() != '"' && scan.do_continue())
    {
        if (scan.current() == '\\')
        {
            builder.append(scan_json_escape_sequence(scan));
        }
        else
        {
            builder.append(scan.current());
            scan.foreward();
        }
    }

    scan.skip('"');

    return builder.finalize();
}

static Value array(Scanner &scan)
{
    scan.skip('[');

    Array array{};

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

static Value object(Scanner &scan)
{
    scan.skip('{');

    Object object{};

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

static Value keyword(Scanner &scan)
{
    StringBuilder builder{};

    while (scan.current_is(Strings::LOWERCASE_ALPHA) &&
           scan.do_continue())
    {
        builder.append(scan.current());
        scan.foreward();
    }

    auto keyword = builder.finalize();

    if (keyword == "true")
    {
        return true;
    }
    else if (keyword == "false")
    {
        return false;
    }
    else
    {
        return nullptr;
    }
}

static Value value(Scanner &scan)
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

Value parse(Scanner &scan)
{
    scan_skip_utf8bom(scan);
    return value(scan);
}

} // namespace json
