#pragma once

#include "dataStructures/vectors.h"

#include <optional>

namespace cgl
{
class Triangle2D
{
    public:
        Triangle2D(const Vec2& c_vertex_a, const Vec2& c_vertex_b, const Vec2& c_vertex_c)
            : vertex_a(c_vertex_a),
            vertex_b(c_vertex_b),
            vertex_c(c_vertex_c),
            line_ab(vertex_b - vertex_a),
            line_ac(vertex_c - vertex_a),
            dot_ab_ab(glm::dot(line_ab, line_ab)),
            dot_ab_ac(glm::dot(line_ab, line_ac)),
            dot_ac_ac(glm::dot(line_ac, line_ac)),
            denominator(1.0f / ((dot_ab_ab * dot_ac_ac) - (dot_ab_ac * dot_ab_ac)))
        {
        }

        /**
         * @brief Get the barycentric coordinates of the passed point.
         *
         * @param x Horizontal position of the point.
         * @param y Vertical position of the point.
         * @param out_coords Calculated coordinates, with x representing the multiplier of vertex_a, y vertex_b, z vertex_c.
         */
        inline void getBarycentricCoordinates(const Vec2& point, Vec3 &out_coords) const
        {
            Vec2 line_ap(point - vertex_a);
            float dot_ap_ab = glm::dot(line_ap, line_ab);
            float dot_ap_ac = glm::dot(line_ap, line_ac);
            float v = ((dot_ac_ac * dot_ap_ab) - (dot_ab_ac * dot_ap_ac)) * denominator;
            float w = ((dot_ab_ab * dot_ap_ac) - (dot_ab_ac * dot_ap_ab)) * denominator;
            out_coords.x = (1.0f - v - w);
            out_coords.y = (v);
            out_coords.z = (w);
        }

        inline const Vec2& getVertexA() const{
            return vertex_a;
        }
        inline const Vec2& getVertexB() const{
            return vertex_b;
        }
        inline const Vec2& getVertexC() const{
            return vertex_c;
        }


    protected:
        Vec2 vertex_a;
        Vec2 vertex_b;
        Vec2 vertex_c;


        Vec2 line_ab;
        Vec2 line_ac;

        float dot_ab_ab;
        float dot_ab_ac;
        float dot_ac_ac;
        float denominator;
};

};