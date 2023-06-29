#pragma once

#include <functional>

namespace cgl
{

class Renderer;
class GLContext;

}; // namespace cgl

cgl::GLContext* getCurrentContext();
void withContext(std::function<void(cgl::GLContext&)> fun);

cgl::Renderer* getCurrentRenderer();
void withRenderer(std::function<void(cgl::Renderer&)> fun);
