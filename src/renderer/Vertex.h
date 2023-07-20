#pragma once

#include "dataStructures/vectors.h"

namespace cgl{

/**
 * Structure representing vertices, with extra information
 * in addition to basic geometry
 */
struct Vertex{
    Vec4 pos = Vec4{0.0f, 0.0f, 0.0f, 1.0f};
    Vec4 color = Vec4{1.0f};
    Vec3 norm = Vec3{0.0f, 0.0f, 1.0f};
    Vec2 tex_coord = Vec2{0.0f};

    float eye_distance = 0;

    template<typename T>
    inline Vertex operator * (T i) const{
        return Vertex{
            pos * i,
            color * i,
            norm * i,
            tex_coord * i,
            eye_distance * i
        };
    }

    inline Vertex operator + (const Vertex& other) const{
        return Vertex{
            pos + other.pos,
            color + other.color,
            norm + other.norm,
            tex_coord + other.tex_coord,
            eye_distance + other.eye_distance
        };
    }
};

};