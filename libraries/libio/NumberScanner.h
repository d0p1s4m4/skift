#pragma once

#include <math.h>

#include <libio/Scanner.h>
#include <libutils/Optional.h>
#include <libutils/Strings.h>

namespace IO
{

struct NumberScanner
{
    int _base;

    static NumberScanner binary() { return {2}; }

    static NumberScanner octal() { return {8}; }

    static NumberScanner decimal() { return {10}; }

    static NumberScanner hexadecimal() { return {16}; }

    Optional<uint64_t> scan_uint(Scanner &scan)
    {
        if (!scan.current_is(Strings::ALL_XDIGITS))
        {
            return {};
        }

        uint64_t value = 0;

        for (size_t i = 0; (i < size && str[i]); i++)
        {
            value = value * _base;

            for (int j = 0; j < _base; j++)
            {
                if ((Strings::LOWERCASE_XDIGITS[j] == str[i]) ||
                    (Strings::UPPERCASE_XDIGITS[j] == str[i]))
                {
                    value += j;
                }
            }
        }

        *result = value;
        return true;
    }

    Optional<int64_t> scan_int(Scanner &scan)
    {
        if (str == nullptr || size == 0)
        {
            *result = 0;
            return false;
        }

        bool is_negative = str[0] == '-';
        if (is_negative)
        {
            str++;
            size--;
        }

        unsigned int unsigned_value = 0;
        if (!scan_uint(parser, str, size, &unsigned_value))
        {
            *result = 0;
            return false;
        }

        if (is_negative)
        {
            *result = -unsigned_value;
        }
        else
        {
            *result = unsigned_value;
        }

        return true;
    }

    Optional<double> scan_float(Scanner &scan)
    {
        int ipart = scan_int(scan);

        double fpart = 0;

        if (scan.skip('.'))
        {
            double multiplier = (1.0 / _base);

            while (scan.current_is(Strings::DIGITS))
            {
                fpart += multiplier * (scan.current() - '0');
                multiplier *= (1.0 / _base);
                scan.foreward();
            }
        }

        int exp = 0;

        if (scan.current_is("eE"))
        {
            scan.foreward();
            exp = scan_int(scan);
        }

        return (ipart + fpart) * pow(_base, exp);
    }
};

} // namespace IO
