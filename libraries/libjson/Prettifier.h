#pragma once

#include <libio/Format.h>
#include <libio/Prettifier.h>

#include <libjson/Value.h>

namespace Json
{

inline void prettify(IO::Prettifier &pretty, const Value &value)
{
    if (value.is(STRING))
    {
        IO::format(pretty, "\"{}\"", value.as_string());
    }
    else if (value.is(INTEGER))
    {
        IO::format(pretty, "{d}", value.as_integer());
    }
#ifndef __KERNEL__
    else if (value.is(DOUBLE))
    {
        IO::format(pretty, "{d}", value.as_double());
    }
#endif
    else if (value.is(OBJECT))
    {
        IO::write_char(pretty, '{');

        if (value.length() > 0)
        {
            pretty.push_ident();

            value.as_object().foreach ([&](auto &key, auto &value) {
                pretty.ident();

                pretty.color_depth();

                IO::format(pretty, "\"{}\": ", key);

                pretty.color_clear();

                IO::write_cstring(pretty, ": ");
                prettify(pretty, value);
                IO::write_char(pretty, ',');

                return Iteration::CONTINUE;
            });

            pretty.rewind();

            pretty.pop_ident();
        }

        pretty.ident();
        IO::write_char(pretty, '}');
    }
    else if (value.is(ARRAY))
    {
        IO::write_char(pretty, '[');

        if (value.length() > 0)
        {
            pretty.push_ident();

            for (size_t i = 0; i < value.length(); i++)
            {
                pretty.ident();
                prettify(pretty, value.get(i));
                IO::write_char(pretty, ',');
            }

            pretty.rewind(); // remove the last ","

            pretty.pop_ident();
        }

        pretty.ident();
        IO::write_char(pretty, ']');
    }
    else
    {
        IO::format(pretty, "{}", value.as_string());
    }
}

} // namespace Json
