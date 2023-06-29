#include "renderer/geometry/Line.h"

#include <cmath>

namespace cgl{

    Line::Line(Vec3 c_point_a, Vec3 c_point_b) :
        point_a(c_point_a),
        point_b(c_point_b),
        direction(glm::normalize(point_b - point_a)),
        max_direction(
            direction.x != 0.0f ? ((point_b.x - point_a.x) / direction.x) :
            direction.y != 0.0f ? ((point_b.y - point_a.y) / direction.y) :
            direction.z != 0.0f ? ((point_b.z - point_a.z) / direction.z) : 0.0f),
        delta_x(point_b.x - point_a.x),
        delta_x_abs(std::abs(delta_x)),
        delta_y(point_b.y - point_a.y),
        delta_y_abs(std::abs(delta_y)),
        slope(delta_y / delta_x),
        constant(point_a.y - (slope * point_a.x)),
        dir(((delta_x < 0) ? -1 : 1))
    {

    }

    bool Line::isOnTheRight(Vec3 point){
        if (delta_x_abs < 0.001f)
            return point.x > point_a.x;
        return (slope * point.x - point.y + constant) * dir > 0.0f;
    }

};