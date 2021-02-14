#pragma once

#include <libio/Prettifier.h>
#include <libio/Format.h>

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
        pretty.write('{');

        if (value.length() > 0)
        {
            pretty.push_ident();

            value.as_object().foreach ([&](auto &key, auto &value) {
                pretty.ident();

                pretty.color_depth();

                IO::format(pretty, "\"{}\": ", key);

                pretty.color_clear();

                pretty.write(": ");
                prettify(pretty, value);
                pretty.write(',');

                return Iteration::CONTINUE;
            });

            pretty.rewind();

            pretty.pop_ident();
        }

        pretty.ident();
        pretty.write('}');
    }
    else if (value.is(ARRAY))
    {
        pretty.write('[');

        if (value.length() > 0)
        {
            pretty.push_ident();

            for (size_t i = 0; i < value.length(); i++)
            {
                pretty.ident();
                prettify(pretty, value.get(i));
                pretty.write(',');
            }

            pretty.rewind(); // remove the last ","

            pretty.pop_ident();
        }

        pretty.ident();
        pretty.write(']');
    }
    else
    {
        IO::format(pretty, "{}", value.as_string());
    }
}

} // namespace Json
