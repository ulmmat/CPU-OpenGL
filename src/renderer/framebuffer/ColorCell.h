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

    using value_type = unsigned char;
    static constexpr value_type MAX_VALUE = std::numeric_limits<value_type>::max();
    static constexpr float MAX_VALUE_DIV_FLOAT = 1.0f / MAX_VALUE;

    value_type blue = MAX_VALUE;
    value_type green = MAX_VALUE;
    value_type red = MAX_VALUE;
    value_type alpha = MAX_VALUE;

    template<typename T>
    ColorCell operator * (T i) const {
        return ColorCell{
            static_cast<value_type>(std::clamp<int>(blue * i, 0, MAX_VALUE)),
            static_cast<value_type>(std::clamp<int>(green * i, 0, MAX_VALUE)),
            static_cast<value_type>(std::clamp<int>(red * i, 0, MAX_VALUE)),
            static_cast<value_type>(std::clamp<int>(alpha * i, 0, MAX_VALUE))
        };

        return *this;
    }

    inline ColorCell operator * (const ColorCell& c) const {
        return ColorCell{
            static_cast<value_type>((static_cast<float>(blue)  * MAX_VALUE_DIV_FLOAT) * c.blue),
            static_cast<value_type>((static_cast<float>(green) * MAX_VALUE_DIV_FLOAT) * c.green),
            static_cast<value_type>((static_cast<float>(red)   * MAX_VALUE_DIV_FLOAT) * c.red),
            static_cast<value_type>((static_cast<float>(alpha) * MAX_VALUE_DIV_FLOAT) * c.alpha)
        };

        return *this;
    }

    inline ColorCell operator + (const ColorCell& c) const{
        return ColorCell{
            static_cast<value_type>(std::clamp(blue + c.blue, 0, static_cast<int>(MAX_VALUE))),
            static_cast<value_type>(std::clamp(green + c.green, 0, static_cast<int>(MAX_VALUE))),
            static_cast<value_type>(std::clamp(red + c.red, 0, static_cast<int>(MAX_VALUE))),
            static_cast<value_type>(std::clamp(alpha + c.alpha, 0, static_cast<int>(MAX_VALUE)))
        };
    }


    inline Vec4 normalize() const {
        return Vec4{
            static_cast<float>(blue)  * MAX_VALUE_DIV_FLOAT,
            static_cast<float>(green) * MAX_VALUE_DIV_FLOAT,
            static_cast<float>(red)   * MAX_VALUE_DIV_FLOAT,
            static_cast<float>(alpha) * MAX_VALUE_DIV_FLOAT
        };
    }

    inline Vec4 normalizeRGBA() const {
        return Vec4{
            static_cast<float>(red)   * MAX_VALUE_DIV_FLOAT,
            static_cast<float>(green) * MAX_VALUE_DIV_FLOAT,
            static_cast<float>(blue)  * MAX_VALUE_DIV_FLOAT,
            static_cast<float>(alpha) * MAX_VALUE_DIV_FLOAT
        };
    }

    inline float normalizeAlpha() const {
        return static_cast<float>(alpha) * MAX_VALUE_DIV_FLOAT;
    }
};

}; // namespace cgl