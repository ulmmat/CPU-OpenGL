#pragma once

#include "dataStructures/vectors.h"

#include <algorithm>
#include <limits>

namespace cgl{

/**
 * @brief Structure representing a 32 bit pixel in the framebuffer
 *
 * Currently hardcoded to expect a BGRA window
 */
struct ColorCell{

    static constexpr unsigned char MAX_VALUE = std::numeric_limits<unsigned char>::max();

    unsigned char blue = MAX_VALUE;
    unsigned char green = MAX_VALUE;
    unsigned char red = MAX_VALUE;
    unsigned char alpha = MAX_VALUE;

    template<typename T>
    ColorCell operator * (T i) const {
        return ColorCell{
            static_cast<unsigned char>(std::clamp<int>(blue * i, 0, MAX_VALUE)),
            static_cast<unsigned char>(std::clamp<int>(green * i, 0, MAX_VALUE)),
            static_cast<unsigned char>(std::clamp<int>(red * i, 0, MAX_VALUE)),
            static_cast<unsigned char>(std::clamp<int>(alpha * i, 0, MAX_VALUE))
        };

        return *this;
    }

    inline ColorCell operator * (const ColorCell& c) const {
        return ColorCell{
            static_cast<unsigned char>((static_cast<float>(blue) / MAX_VALUE) * c.blue),
            static_cast<unsigned char>((static_cast<float>(green) / MAX_VALUE) * c.green),
            static_cast<unsigned char>((static_cast<float>(red) / MAX_VALUE) * c.red),
            static_cast<unsigned char>((static_cast<float>(alpha) / MAX_VALUE) * c.alpha)
        };

        return *this;
    }

    inline ColorCell operator + (const ColorCell& c) const{
        return ColorCell{
            static_cast<unsigned char>(std::clamp(blue + c.blue, 0, static_cast<int>(MAX_VALUE))),
            static_cast<unsigned char>(std::clamp(green + c.green, 0, static_cast<int>(MAX_VALUE))),
            static_cast<unsigned char>(std::clamp(red + c.red, 0, static_cast<int>(MAX_VALUE))),
            static_cast<unsigned char>(std::clamp(alpha + c.alpha, 0, static_cast<int>(MAX_VALUE)))
        };
    }


    inline Vec4 normalize() const {
        return Vec4{
            static_cast<float>(blue) / MAX_VALUE,
            static_cast<float>(green) / MAX_VALUE,
            static_cast<float>(red) / MAX_VALUE,
            static_cast<float>(alpha) / MAX_VALUE
        };
    }

    inline Vec4 normalizeRGBA() const {
        return Vec4{
            static_cast<float>(red) / MAX_VALUE,
            static_cast<float>(green) / MAX_VALUE,
            static_cast<float>(blue) / MAX_VALUE,
            static_cast<float>(alpha) / MAX_VALUE
        };
    }

    inline float normalizeAlpha() const {
        return static_cast<float>(alpha) / MAX_VALUE;
    }
};

}; // namespace cgl