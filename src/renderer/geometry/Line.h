#pragma once

#include "dataStructures/vectors.h"

namespace cgl{

    struct Line{

        public:
            Line(Vec3 c_point_a, Vec3 c_point_b);

            /**
             * @brief Check if the passed point if on the right side of this line (ignoring the z axis), in the direction from point_a to point_b
             */
            bool isOnTheRight(Vec3 point);

            const Vec3 point_a;
            const Vec3 point_b;
            /** Normalized */
            const Vec3 direction;
            const float max_direction;
            const float delta_x;
            const float delta_x_abs;
            const float delta_y;
            const float delta_y_abs;
            const float slope;

        private:
            float constant;
            const int dir;
    };
};