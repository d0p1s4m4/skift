#include <karm-base/clamp.h>

#include "color.h"

namespace Karm::Gfx {

Hsv rgbToHsv(Color color) {
    f64 r = color.red / 255.0;
    f64 g = color.green / 255.0;
    f64 b = color.blue / 255.0;

    f64 rgbMax = Karm::max(r, g, b);
    f64 rgbMin = Karm::min(r, g, b);

    f64 delta = rgbMax - rgbMin;

    f64 hue = 0.0f;
    if (delta != 0.0f) {
        if (rgbMax == r) {
            hue = (g - b) / delta;
        } else if (rgbMax == g) {
            hue = 2.0f + (b - r) / delta;
        } else if (rgbMax == b) {
            hue = 4.0f + (r - g) / delta;
        }
    }

    hue *= 60.0f;
    if (hue < 0.0f) {
        hue += 360.0f;
    }

    f64 saturation = rgbMax == 0.0f ? 0.0f : delta / rgbMax;

    return {hue, saturation, rgbMax};
}

Color hsvToRgb(Hsv hsv) {
    f64 h = hsv.hue;
    f64 s = hsv.saturation;
    f64 v = hsv.value;

    f64 c = v * s;
    f64 x = c * (1.0f - Math::abs(fmod(h / 60.0f, 2.0f) - 1.0f));
    f64 m = v - c;

    f64 r = 0.0f;
    f64 g = 0.0f;
    f64 b = 0.0f;

    if (h < 60.0f) {
        r = c;
        g = x;
    } else if (h < 120.0f) {
        r = x;
        g = c;
    } else if (h < 180.0f) {
        g = c;
        b = x;
    } else if (h < 240.0f) {
        g = x;
        b = c;
    } else if (h < 300.0f) {
        r = x;
        b = c;
    } else {
        r = c;
        b = x;
    }

    return {
        static_cast<u8>((r + m) * 255.0f),
        static_cast<u8>((g + m) * 255.0f),
        static_cast<u8>((b + m) * 255.0f),
        255,
    };
}

YCbCr rgbToYCbCr(Color color) {
    YCbCr yCbCr;
    yCbCr.y = 0.299 * color.red + 0.587 * color.green + 0.114 * color.blue;
    yCbCr.cb = 128 - 0.168736 * color.red - 0.331264 * color.green + 0.5 * color.blue;
    yCbCr.cr = 128 + 0.5 * color.red - 0.418688 * color.green - 0.081312 * color.blue;
    return yCbCr;
}

Color yCbCrToRgb(YCbCr yCbCr) {
    float r = yCbCr.y + 1.402f * yCbCr.cr + 128;
    float g = yCbCr.y - 0.344f * yCbCr.cb - 0.714f * yCbCr.cr + 128;
    float b = yCbCr.y + 1.772f * yCbCr.cb + 128;

    r = clamp(r, 0.0f, 255.0f);
    g = clamp(g, 0.0f, 255.0f);
    b = clamp(b, 0.0f, 255.0f);
    return Gfx::Color::fromRgba(r, g, b, 255);
}

} // namespace Karm::Gfx
