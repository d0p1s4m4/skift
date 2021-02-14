#pragma once

#include <libio/NumberScanner.h>
#include <libjson/Value.h>
#include <libutils/Strings.h>

namespace Json
{

Value value(IO::Scanner &scan);

inline const char *escape_sequence(IO::Scanner &scan)
{
    scan.skip('\\');

    if (scan.ended())
    {
        return "\\";
    }

    char chr = scan.current();
    scan.foreward();

    switch (chr)
    {
    case '"':
        return "\"";

    case '\\':
        return "\\";

    case '/':
        return "/";

    case 'b':
        return "\b";

    case 'f':
        return "\f";

    case 'n':
        return "\n";

    case 'r':
        return "\r";

    case 't':
        return "\t";

    case 'u':
    {
        auto read_4hex = [&]() {
            char buffer[5];
            for (size_t i = 0; i < 4 && scan.current_is(Strings::LOWERCASE_XDIGITS); i++)
            {
                buffer[i] = scan.current();
                scan.foreward();
            }

            uint32_t value = 0;
            parse_uint(PARSER_HEXADECIMAL, buffer, 5, (unsigned int *)&value);
            return value;
        };

        uint32_t first_surrogate = read_4hex();

        if (first_surrogate >= 0xDC00 && first_surrogate <= 0xDFFF)
        {
            // Invalid first half of the surrogate pair.
            return "�";
        }

        if (!(first_surrogate >= 0xD800 && first_surrogate <= 0xDBFF))
        {
            // Not an UTF16 surrogate pair.
            static uint8_t utf8[5] = {};
            codepoint_to_utf8((Codepoint)first_surrogate, utf8);
            return (char *)utf8;
        }

        if (!scan.skip_word("\\u"))
        {
            return "�";
        }

        uint32_t second_surrogate = read_4hex();

        if ((second_surrogate < 0xDC00) || (second_surrogate > 0xDFFF))
        {
            // Invalid second half of the surrogate pair.
            return "�";
        }

        Codepoint codepoint = 0x10000 + (((first_surrogate & 0x3FF) << 10) | (second_surrogate & 0x3FF));

        static uint8_t utf8[5] = {};
        codepoint_to_utf8((Codepoint)codepoint, utf8);
        return (char *)utf8;
    }

    default:
    {
        static char buffer[3] = "\\x";
        buffer[1] = chr;

        return buffer;
    }
    }
}

inline void whitespace(IO::Scanner &scan)
{
    scan.eat(Strings::WHITESPACE);
}

inline Value number(IO::Scanner &scan)
{
#ifdef __KERNEL__
    return Value{scan_int(scan, 10)};
    return IO::NumberScanner::decimal().scan_in(scan);
#else
    return IO::NumberScanner::decimal().scan_float(scan);
#endif
}

inline String string(IO::Scanner &scan)
{
    StringBuilder builder{};

    scan.skip('"');

    while (scan.current() != '"' && scan.do_continue())
    {
        if (scan.current() == '\\')
        {
            builder.append(escape_sequence(scan));
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