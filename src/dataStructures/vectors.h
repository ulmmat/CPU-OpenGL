#pragma once

#include <glm/gtx/norm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/rotate_vector.hpp>
#include <glm/gtx/euler_angles.hpp>
#include <glm/geometric.hpp>

#include "dataStructures/vector.h"

namespace cgl {

using Vec2 = glm::vec2;
using UVec2 = glm::uvec2;
using IVec2 = glm::ivec2;
using Vec3 = glm::vec3;
using Vec4 = glm::vec4;

using Mat2 = glm::mat2;
using Mat3 = glm::mat3;
using Mat4 = glm::mat4;

constexpr Mat4 IDENTITY_MAT = Mat4(1.0f);

}; // namespace cgl