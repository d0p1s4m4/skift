#pragma once

#include <libsystem/io_new/Writer.h>
#include <libsystem/math/Math.h>
#include <libutils/Strings.h>

namespace System
{

struct NumberFormatter
{
    int _base;
    int _precision;
    bool _capitalized;

    static NumberFormatter binary()
    {
        return {2, 4, false};
    }

    static NumberFormatter octal()
    {
        return {8, 4, false};
    }

    static NumberFormatter decimal()
    {
        return {10, 4, false};
    }

    static NumberFormatter hexadecimal()
    {
        return {16, 4, false};
    }

    NumberFormatter capitalized()
    {
        NumberFormatter copy = *this;
        copy._capitalized = true;
        return copy;
    }

    ResultOr<size_t> format(System::Writer &writer, int64_t value)
    {
        bool is_negative = value < 0;

        if (is_negative)
        {
            writer.write('-');
            value = -value;
        }

        auto format_result = format(writer, (uint64_t)value);

        if (format_result)
        {
            return *format_result + is_negative ? 1 : 0;
        }
        else
        {
            return format_result;
        }
    }

    ResultOr<size_t> format(System::Writer &writer, uint64_t value)
    {
        if (value == 0)
        {
            auto zero_result = writer.write('0');

            if (zero_result == SUCCESS)
            {
                return 1;
            }

            return zero_result;
        }

        size_t i = 0;
        char buffer[64] = {};

        while (value != 0)
        {
            if (_capitalized)
            {
                buffer[i] = Strings::LOWERCASE_XDIGITS[value % _base];
            }
            else
            {
                buffer[i] = Strings::UPPERCASE_XDIGITS[value % _base];
            }

            value /= _base;
            i++;
        }

        strrvs(buffer);

        return writer.write(buffer, i);
    }

    ResultOr<size_t> format(System::Writer &writer, double value)
    {
        size_t written = 0;

        int64_t ipart = (int64_t)value;
        double fpart = value - (double)ipart;

        auto ipart_result = format(writer, ipart);

        if (!ipart_result)
        {
            return ipart_result;
        }

        written += *ipart_result;

        if (_precision > 0)
        {
            auto dot_result = writer.write('.');

            if (dot_result != SUCCESS)
            {
                return dot_result;
            }

            written += 1;

            int64_t ifpart = fpart * pow(_base, _precision);
            auto ifpart_result = format(writer, ifpart);

            if (!ifpart_result)
            {
                return ifpart_result;
            }

            written += *ipart_result;
        }

        return written;
    }
};

} // namespace System
