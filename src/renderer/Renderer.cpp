#include "renderer/Renderer.h"
#include "ogl/ogl_constants.h"

#include <glm/ext/matrix_transform.hpp>
#include <stdexcept>

namespace cgl
{

Rasterizer::DrawStats Renderer::fetchFrameStats(){
    Rasterizer::DrawStats stats = m_rasterizer.getStats();
    m_rasterizer.resetStats();
    return stats;
}
void Renderer::resizeFramebuffers(int width, int height){
    for (auto& p : m_framebuffers){
        p.second.resizeFramebuffer(width, height);
    }
    m_viewport_info.x = 0;
    m_viewport_info.y = 0;
    m_viewport_info.width  = width;
    m_viewport_info.height = height;
}

void Renderer::setViewport(ViewportInfo vp_info){
    m_viewport_info = vp_info;
}

void Renderer::setReadFramebuffer(GLenum type){
    if (type != GL_FRONT && type != GL_BACK){
        coutPrint("Invalid frambuffer type: ", type);
        return;
    }
    m_read_framebuffer = type;
}

void Renderer::setDrawFramebuffer(GLenum type){
    if (type != GL_FRONT && type != GL_BACK){
        coutPrint("Invalid frambuffer type: ", type);
        return;
    }
    m_draw_framebuffer = type;
}

GLenum Renderer::getReadFramebuffer() const{
    return m_read_framebuffer;
}
GLenum Renderer::getDrawFramebuffer() const{
    return m_draw_framebuffer;
}


Map<GLenum, FrameBuffer*> Renderer::getFramebuffers(){
    Map<GLenum, FrameBuffer*> map;
    for (auto& p : m_framebuffers){
        map.emplace(p.first, &p.second);
    }
    return map;
}

void Renderer::setBackfaceCullMode(GLenum mode){
    m_cull_mode = mode;
}
void Renderer::useBackfaceCull(bool val){
    m_backface_cull = val;
}
void Renderer::setFrontFace(GLenum mode){
    m_cull_ccw = (mode == GL_CCW) ? true : false;
}
bool Renderer::getCapability(GLenum capability) const{
    return m_capabilities[capability].val;
}
void Renderer::setCapability(GLenum capability, bool value){
    m_capabilities[capability].val = value;
}

void Renderer::setClientState(GLenum state, bool value){
    auto it = m_client_state.find(state);
    if (it != m_client_state.end()){
        it->second.val = value;
    }
}
bool Renderer::getClientState(GLenum state){
    return m_client_state[state].val;
}
void Renderer::setBlending(GLenum sfactor, GLenum dfactor){
    m_blend_options.source_fun = sfactor;
    m_blend_options.dest_fun   = dfactor;
}
void Renderer::setAlphaFunc(GLenum func, GLclampf val){
    m_alpha_func = func;
    m_alpha_val = val;
}

void Renderer::setColorMask(GLbitfield mask){
    m_color_mask = mask;
}

void Renderer::setDepthFunc(GLenum func){
    m_depth_func = func;
}

void Renderer::setDepthMask(GLboolean flag){
    m_depth_mask = flag;
}
void Renderer::setDepthRange(GLfloat near, GLfloat far){
    m_depth_range_far = std::clamp(far, 0.0f, 1.0f);
    m_depth_range_near = std::clamp(near, 0.0f, far);
}
void Renderer::setDepthClear(GLfloat depth){
    m_depth_clear = depth;
}

void Renderer::setStencilFunc(GLenum func, GLint ref, GLuint mask){
    m_stencil_func = func;
    m_stencil_ref = ref;
    m_stencil_mask = mask;
}
void Renderer::setStencilMask(GLuint mask){
    m_stencil_mask = mask;
}
void Renderer::setStencilOp(GLenum stencil_fail, GLenum depth_fail, GLenum both_pass){
    m_stencil_fail_op = stencil_fail;
    m_stencil_depth_fail_op = depth_fail;
    m_stencil_both_pass_op = both_pass;
}
void Renderer::setStencilClear(GLint stencil){
    m_clear_stencil = stencil & STENC_CELL_MASK;
}
void Renderer::setScissorBox(GLint x, GLint y, GLsizei width, GLsizei height){
    m_scissor_box.min_x = x;
    m_scissor_box.max_x = x + width;

    m_scissor_box.min_y = y;
    m_scissor_box.max_y = y + height;
}
void Renderer::setPolygonOffset(GLfloat factor, GLfloat units){
    m_polygon_offset.factor = factor;
    m_polygon_offset.units = units;
}
template<typename T>
void Renderer::setFogOption(GLenum param, T val){
    return setFogOptionV<T>(param, &val);
}

template<typename T>
void Renderer::setFogOptionV(GLenum param, const T* vals){
    switch (param)
    {
        case GL_FOG_MODE:
            m_fog_options.fog_mode = *vals;
            break;

        case GL_FOG_DENSITY:
            m_fog_options.fog_density = *vals;
            break;

        case GL_FOG_START:
            m_fog_options.fog_start = *vals;
            break;

        case GL_FOG_END:
            m_fog_options.fog_end = *vals;
            break;

        case GL_FOG_COLOR:
            m_fog_options.fog_color = Vec4{
                vals[0], vals[1], vals[2], vals[3]
            };
            m_fog_options.fog_color_cell = ColorCell{
                static_cast<ColorCell::value_type>(m_fog_options.fog_color[0] * ColorCell::MAX_VALUE),
                static_cast<ColorCell::value_type>(m_fog_options.fog_color[1] * ColorCell::MAX_VALUE),
                static_cast<ColorCell::value_type>(m_fog_options.fog_color[2] * ColorCell::MAX_VALUE),
                static_cast<ColorCell::value_type>(m_fog_options.fog_color[3] * ColorCell::MAX_VALUE)
            };
            break;

        case GL_FOG_INDEX:
            throw std::runtime_error("Fog Color index is unsupported");
            break;

        default:
            throw std::runtime_error("Unknown Fod param");
            break;
    }
}

template void Renderer::setFogOption<GLfloat>(GLenum param, GLfloat val);
template void Renderer::setFogOption<GLint>(GLenum param, GLint val);

template void Renderer::setFogOptionV<GLfloat>(GLenum param, const GLfloat* vals);
template void Renderer::setFogOptionV<GLint>(GLenum param, const GLint* vals);


void Renderer::setClearColor(Vec4 color){
    m_clear_color = color;
}
void Renderer::setMainColor(Vec4 color){
    m_cur_color = color;
    if (!m_vertices_for_draw.empty()){
        m_vertices_for_draw.back().color = m_cur_color;
    }
}

FrameBuffer& Renderer::readFramebuffer(){
    return m_framebuffers.at(m_read_framebuffer);
}

FrameBuffer& Renderer::drawFramebuffer(){
    return m_framebuffers.at(m_draw_framebuffer);
}

void Renderer::clear(GLbitfield mask){
    m_rasterizer.clearBuffer(
        drawFramebuffer(),
        m_clear_color.x,
        m_clear_color.y,
        m_clear_color.z,
        m_clear_color.w,
        m_depth_clear,
        m_clear_stencil,
        mask
    );
}

void Renderer::setMatrixStack(GLenum stack){
    auto& map = m_mat_stacks.MODE_STACK_MAP;
    auto it = map.find(stack);
    if (it != map.end()){
        m_cur_stack = it->second;
    }
}
void Renderer::setCurMatrix(const Mat4& mat){
    curMatrix() = mat;
    m_matrices_modified = true;
}
const Mat4& Renderer::curMatrix() const {
    return m_cur_stack->top();
}
Mat4& Renderer::curMatrix() {
    m_matrices_modified = true;
    return m_cur_stack->top();
}

void Renderer::popMatrix(){
    if (m_cur_stack->size() > 1){
        m_cur_stack->pop();
    }
    m_matrices_modified = true;
}
void Renderer::pushMatrix(){
    m_cur_stack->push(m_cur_stack->top());
    m_matrices_modified = true;
}
void Renderer::rotateMat(GLfloat angle, GLfloat x, GLfloat y, GLfloat z){
    Mat4& mat = curMatrix();
    mat = glm::rotate(mat, angle, Vec3(x, y, z));
}
void Renderer::rotateMatd(GLfloat angle, GLdouble x, GLdouble y, GLdouble z){
    Mat4& mat = curMatrix();
    mat = glm::rotate(mat, angle, Vec3(x, y, z));
}
void Renderer::translateMat(GLfloat x, GLfloat y, GLfloat z){
    Mat4& mat = curMatrix();
    mat = glm::translate(mat, Vec3(x, y, z));
}

void Renderer::translateMatd(GLdouble x, GLdouble y, GLdouble z){
    Mat4& mat = curMatrix();
    mat = glm::translate(mat, Vec3(x, y, z));
}

void Renderer::multMatf(const GLfloat* mat_data){
    Mat4 mult_mat = glm::make_mat4(mat_data);
    Mat4& mat = curMatrix();
    mat *= mult_mat;
}
void Renderer::multMatd(const GLdouble* mat_data){
    Mat4 mult_mat = glm::make_mat4(mat_data);
    Mat4& mat = curMatrix();
    mat *= mult_mat;
}
template<typename T>
void Renderer::scaleMat(T x, T y, T z){
    Mat4& mat = curMatrix();
    mat = glm::scale(mat, Vec3{x, y, z});
}
template void Renderer::scaleMat<GLfloat>(GLfloat x, GLfloat y, GLfloat z);
template void Renderer::scaleMat<GLdouble>(GLdouble x, GLdouble y, GLdouble z);

void Renderer::perspectiveMat(GLdouble fovy, GLdouble aspect, GLdouble zNear, GLdouble zFar){
    Mat4& mat = curMatrix();
    mat *= glm::perspective<float>(fovy, aspect, zNear, zFar);
}

void Renderer::frustumMat(
    GLdouble left, GLdouble right,
    GLdouble bottom, GLdouble top,
    GLdouble near_val, GLdouble far_val
){
    Mat4& mat = curMatrix();
    mat *= glm::frustum<float>(left, right, bottom, top, near_val, far_val);
}
void Renderer::orthoMat(GLdouble left, GLdouble right, GLdouble bottom, GLdouble top, GLdouble near_val, GLdouble far_val){
    Mat4& mat = curMatrix();
    mat *= glm::ortho<float>(left, right, bottom, top, near_val, far_val);
}

/** Vertex Buffers */

void Renderer::setGenericBuffer(BufferType type, const GenericBuffer& buf){

    auto it = BUFFER_MAP.find(type);
    if (it != BUFFER_MAP.end()){
        *it->second = buf;
    }
}

/**
 * Indices contains indices marking polygons with poly_size vertices
 *
 * Fills the buffer with indices that draw the original complex polygon as a triangle fan
 *
 * Only tested with quads
 */
template<typename TIndices>
void fillIndicesBuffer(int poly_size, GLsizei count, const TIndices* indices, Vector<GLuint>& buffer){
    buffer.clear();
    for (GLsizei i = 0; i < count; i += poly_size){

        for (int poly_i = 2; poly_i < poly_size; poly_i++){
            buffer.emplace_back(indices[i]);
            buffer.emplace_back(indices[i + poly_i - 1]);
            buffer.emplace_back(indices[i + poly_i]);
        }
    }
}
template<typename TIndices>
void Renderer::drawElements(GLenum mode, GLsizei count, GLenum type, const TIndices* indices){
    if (mode != GL_TRIANGLES && mode != GL_QUADS && mode != GL_POLYGON){
        throw std::runtime_error("Unsupported draw mode");
    }

    DrawSettings set = createDrawSettings();

    if (m_matrices_modified){
        m_rasterizer.setMatrices(m_mat_stacks.modelview_stack.top(), m_mat_stacks.projection_stack.top());
        m_matrices_modified = false;
    }
    if (mode == GL_POLYGON){
        fillIndicesBuffer(count, count, indices, m_indices_buffer);
        drawTrianglesInternal<GLuint>(set, drawFramebuffer(), vertex_pointer, m_indices_buffer.data(), m_indices_buffer.size(), tex_coord_pointer, color_pointer);
    }
    else if (mode == GL_QUADS){
        fillIndicesBuffer(4, count, indices, m_indices_buffer);
        drawTrianglesInternal<GLuint>(set, drawFramebuffer(), vertex_pointer, m_indices_buffer.data(), m_indices_buffer.size(), tex_coord_pointer, color_pointer);
    }
    else{
        drawTrianglesInternal<TIndices>(set, drawFramebuffer(), vertex_pointer, indices, count, tex_coord_pointer, color_pointer);
    }
}
DrawSettings Renderer::createDrawSettings() const{
    return DrawSettings{
        .cull_face = getCapability(GL_CULL_FACE),
        .cull_mode = m_cull_mode,
        .cull_ccw = m_cull_ccw,
        .triangle_strip = false,
        .color_mask = m_color_mask,
        .depth_test = getCapability(GL_DEPTH_TEST),
        .depth_func = m_depth_func,
        .depth_mask = m_depth_mask,
        .depth_range_dif = ( (m_depth_range_far - m_depth_range_near) * 0.5f),
        .stencil_test = getCapability(GL_STENCIL_TEST),
        .stencil_fun = m_stencil_func,
        .stencil_ref = m_stencil_ref,
        .stencil_mask = m_stencil_mask,
        .stencil_fail_op = m_stencil_fail_op,
        .stencil_dfail_op = m_stencil_depth_fail_op,
        .stencil_pass_op = m_stencil_both_pass_op,
        .fog_enabled = getCapability(GL_FOG),
        .fog_options = m_fog_options,
        .blend = getCapability(GL_BLEND),
        .src_blend_func = m_blend_options.source_fun,
        .dst_blend_func = m_blend_options.dest_fun,
        .texture_env = m_texture_env,
        .alpha_test = getCapability(GL_ALPHA_TEST),
        .alpha_test_func = m_alpha_func,
        .alpha_test_val = m_alpha_val,
        .scissor_test = getCapability(GL_SCISSOR_TEST),
        .scissor_box = m_scissor_box,
        .offset_enabled = getCapability(GL_POLYGON_OFFSET_FILL),
        .offset_options = m_polygon_offset,
        .main_color = m_cur_color,
        .vp_info = m_viewport_info,
        .tex = (getCapability(GL_TEXTURE_2D) && m_cur_texture && m_cur_texture->getWidth() && m_cur_texture->getHeight()) ? m_cur_texture : nullptr
    };
}
void Renderer::drawArrays(GLenum mode, GLint first, GLsizei count){
    m_array_index.clear();

    if (m_matrices_modified){
        m_rasterizer.setMatrices(m_mat_stacks.modelview_stack.top(), m_mat_stacks.projection_stack.top());
        m_matrices_modified = false;
    }

    DrawSettings set = createDrawSettings();

    switch (mode)
    {
        case GL_TRIANGLES:
            for (GLsizei i = 0; i < count; i+=3){
                m_array_index.emplace_back(first + i + 0);
                m_array_index.emplace_back(first + i + 1);
                m_array_index.emplace_back(first + i + 2);
            }
            break;
        case GL_TRIANGLE_STRIP:
            for (GLsizei i = 0; i < count - 2; i++){
                m_array_index.emplace_back(first + i + 0);
                m_array_index.emplace_back(first + i + 1);
                m_array_index.emplace_back(first + i + 2);
            }
            set.triangle_strip = true;
            break;
        case GL_TRIANGLE_FAN:{
            GLsizei anchor = first;
            for (GLsizei i = 0; i < count - 2; i++){
                m_array_index.emplace_back(anchor);
                m_array_index.emplace_back(first + i + 1);
                m_array_index.emplace_back(first + i + 2);
            }
            break;
        }

        case GL_QUADS:{
            for (GLsizei i = 0; i < count; i+=4){
                m_array_index.emplace_back(first + i + 0);
                m_array_index.emplace_back(first + i + 1);
                m_array_index.emplace_back(first + i + 2);

                m_array_index.emplace_back(first + i + 0);
                m_array_index.emplace_back(first + i + 2);
                m_array_index.emplace_back(first + i + 3);
            }
            break;
        }

        default:
            throw std::runtime_error("Unsupported mode");
            break;
    }
    drawTrianglesInternal<GLuint>(
        set,
        drawFramebuffer(),
        vertex_pointer,
        m_array_index.data(),
        m_array_index.size(),
        tex_coord_pointer,
        getClientState(GL_COLOR_ARRAY) ? color_pointer : dummy_buffer
    );
}

template void Renderer::drawElements<GLubyte>(GLenum mode, GLsizei count, GLenum type, const GLubyte* indices);
template void Renderer::drawElements<GLushort>(GLenum mode, GLsizei count, GLenum type, const GLushort* indices);
template void Renderer::drawElements<GLuint>(GLenum mode, GLsizei count, GLenum type, const GLuint* indices);

const MatrixStacks& Renderer::getMatrixStack() const{
    return m_mat_stacks;
}

/** Draw Transaction */
void Renderer::beginDraw(GLenum type){
    if (m_begin_transaction.has_value()){
        throw std::runtime_error("Begin draw while end not called yet");
        return;
    }
    switch (type)
    {
        case GL_POINTS :
            m_tr_vertex_cnt = PrimitiveVertexCount::POINT;
            break;
        case GL_LINES :
        case GL_LINE_STRIP :
        case GL_LINE_LOOP :
            m_tr_vertex_cnt = PrimitiveVertexCount::LINE;
            break;
        case GL_TRIANGLES :
        case GL_TRIANGLE_STRIP :
        case GL_TRIANGLE_FAN :
            m_tr_vertex_cnt = PrimitiveVertexCount::TRIANGLE;
            break;

        case GL_QUADS :
        case GL_QUAD_STRIP :
            m_tr_vertex_cnt = PrimitiveVertexCount::QUAD;
            break;
        case GL_POLYGON :
            m_tr_vertex_cnt = PrimitiveVertexCount::POLYGON;
            break;
        default:
            break;
    }

    m_vertices_for_draw.clear();
    m_vertices_for_draw.emplace_back().color = m_cur_color;
    m_begin_transaction = type;
}
void Renderer::addVertex(const Vec3& vec){
    m_vertices_for_draw.back().pos = Vec4{vec, 1.0f};
    m_vertices_for_draw.emplace_back().color = m_cur_color;
}
void Renderer::setVertexNormal(const Vec3& norm){
    m_vertices_for_draw.back().norm = norm;
}
void Renderer::setVertexColor(const Vec4& color){
    m_vertices_for_draw.back().color = color;
}
void Renderer::setVertexTexCoords(const Vec2& coords){
    m_vertices_for_draw.back().tex_coord = coords;
}
void Renderer::setVertexArrayElem(GLint i){
    m_rasterizer.fillVertex( m_vertices_for_draw.back(), i, vertex_pointer, color_pointer, tex_coord_pointer, m_cur_color);
    m_vertices_for_draw.emplace_back().color = m_cur_color;
}
void Renderer::endDraw(){
    if (!m_begin_transaction.has_value()){
        throw std::runtime_error("Cannot end without first starting a draw transation");
        return;
    }
    transactionDoDraw();
    m_begin_transaction.reset();
}
void Renderer::transactionDoDraw(){
    m_vertices_for_draw.pop_back();
    if (m_vertices_for_draw.empty()){
        return;
    }

    DrawSettings set = createDrawSettings();

    if (m_matrices_modified){
        m_rasterizer.setMatrices(m_mat_stacks.modelview_stack.top(), m_mat_stacks.projection_stack.top());
        m_matrices_modified = false;
    }

    switch (m_begin_transaction.value())
    {
        case GL_POINT :
            /** Unsupported */
            break;
        case GL_LINE :
            /** Unsupported */
            break;
        case GL_TRIANGLES :
            for (size_t i = 0; i < m_vertices_for_draw.size(); i += 3){
                drawTriangleInternal(drawFramebuffer(), m_vertices_for_draw[i], m_vertices_for_draw[i+1], m_vertices_for_draw[i+2]);
            }
            break;
        case GL_TRIANGLE_FAN : {
            Vertex& anchor = m_vertices_for_draw.front();
            for (GLsizei i = 0; i < m_vertices_for_draw.size() - 2; i++){
                drawTriangleInternal(
                    drawFramebuffer(),
                    anchor,
                    m_vertices_for_draw[i+1],
                    m_vertices_for_draw[i+2]
                );
            }
            break;
        }

        case GL_TRIANGLE_STRIP : {
            for (GLsizei i = 0; i < m_vertices_for_draw.size() - 2; i++){
                m_rasterizer.drawTriangle(
                    set,
                    drawFramebuffer(),
                    m_vertices_for_draw[i + 0],
                    m_vertices_for_draw[i + 1],
                    m_vertices_for_draw[i + 2]
                );
                set.cull_ccw = !set.cull_ccw;
            }
            break;

            Vertex& anchor = m_vertices_for_draw.front();
            for (GLsizei i = 0; i < m_vertices_for_draw.size() - 2; i++){
                drawTriangleInternal(
                    drawFramebuffer(),
                    anchor,
                    m_vertices_for_draw[i+1],
                    m_vertices_for_draw[i+2]
                );
            }
            break;
        }

        case GL_QUADS :
            for (size_t i = 0; i < m_vertices_for_draw.size(); i += 4){
                drawTriangleInternal(drawFramebuffer(), m_vertices_for_draw[i], m_vertices_for_draw[i+1], m_vertices_for_draw[i+2]);
                drawTriangleInternal(drawFramebuffer(), m_vertices_for_draw[i], m_vertices_for_draw[i+2], m_vertices_for_draw[i+3]);
            }
            break;
        // Draw a triangle fan
        case GL_POLYGON :{
            Vertex& anchor = m_vertices_for_draw[0];
            for (size_t i = 1; i < m_vertices_for_draw.size() - 1; i++){
                drawTriangleInternal(drawFramebuffer(), anchor, m_vertices_for_draw[i], m_vertices_for_draw[i+1]);
            }
            break;
        }
        default:
            break;
    }
}

template<typename T>
void Renderer::getInternalValue(GLenum pname, T* data){
    switch (pname)
    {
        case GL_MAX_TEXTURE_SIZE:
            *data = 16384;
            break;

        case GL_ALPHA_BITS:
            *data = 8;
            break;

        case GL_RED_BITS:
            *data = 8;
            break;

        case GL_GREEN_BITS:
            *data = 8;
            break;

        case GL_BLUE_BITS:
            *data = 8;
            break;

        case GL_DEPTH_BITS:
            *data = 32;
            break;

        case GL_STENCIL_BITS:
            *data = 8;
            break;

        case GL_SAMPLES:
            *data = 0;
            break;
        default:
            throw std::runtime_error("Unknown requested value");
            break;
    }
}

template void Renderer::getInternalValue<GLint>(GLenum pname, GLint* data);
template void Renderer::getInternalValue<GLboolean>(GLenum pname, GLboolean* data);

void Renderer::generateTextures(GLsizei n, GLuint* textures){
    for (GLsizei i = 0; i < n; i++){
        while(true){
            size_t id = m_tex_ctr++;
            auto it = m_textures.find(id);
            if (it == m_textures.end() ){
                m_textures[id] = Texture();
                textures[i] = id;
                break;
            }
        }
    }
}
void Renderer::bindTexture(GLuint texture){
    auto it = m_textures.find(texture);
    if (it != m_textures.end() ){
        m_cur_texture = &it->second;
        m_cur_texture_id = texture;
    }
    else{
        m_cur_texture = &m_textures[texture];
        m_cur_texture_id = texture;
    }

}

void Renderer::deleteTextures(GLsizei n, const GLuint* textures){
    for (GLsizei i = 0; i < n; i++){
        m_textures.erase(textures[i]);
    }
}

void Renderer::setTextureParameter(GLenum target, GLenum pname, GLint param){
    if (m_cur_texture){
        switch (pname)
        {
            case GL_TEXTURE_MAG_FILTER :
                m_cur_texture->mag_filter = param;
                break;
            case GL_TEXTURE_MIN_FILTER :
                m_cur_texture->min_filter = param;
                break;
            case GL_TEXTURE_WRAP_S :
                m_cur_texture->wrap_s = param;
                if (param != GL_REPEAT && param != GL_CLAMP && param != GL_CLAMP_TO_EDGE){
                    throw std::runtime_error("Unknown texture wrap");
                }
                break;
            case GL_TEXTURE_WRAP_T :
                m_cur_texture->wrap_t = param;
                if (param != GL_REPEAT && param != GL_CLAMP && param != GL_CLAMP_TO_EDGE){
                    throw std::runtime_error("Unknown texture wrap");
                }
                break;

            default:
                #ifdef DEBUG
                throw std::runtime_error("Unknown texture parameter");
                #endif
                break;
        }
    }
}

void Renderer::setTexture(
    GLenum target, GLint level,
    GLint internal_format,
    GLsizei width, GLsizei height,
    GLint border, GLenum format, GLenum type,
    const GLvoid* pixels
){
    if (m_cur_texture && m_cur_texture->level >= level){

        m_cur_texture->setData(
            target, level,
            internal_format,
            width, height,
            border, format, type,
            pixels
        );
    }
 }

void Renderer::copyFramebufferToTex(
    GLenum target, GLint level,
    GLint xoffset, GLint yoffset,
    GLint x, GLint y,
    GLsizei width, GLsizei height
){
    switch (target)
    {
        case GL_TEXTURE_2D:
            if (m_cur_texture){

                m_cur_texture->setFramebufferSubData(
                    target, level,
                    xoffset, yoffset,
                    x, y,
                    width, height,
                    readFramebuffer()
                );
            }
            break;

        default:
            throw std::runtime_error("Unsupported texture target");
            break;
    }
}

const Texture* Renderer::getTexture(GLenum target) const{
    switch (target)
    {
        case GL_TEXTURE_2D:
            return m_cur_texture;
            break;

        default:
            throw std::runtime_error("Invalid texture type");
            break;
    }
}

void Renderer::subTexture(
    GLenum target,GLint level,
    GLint xoffset,GLint yoffset,
    GLsizei width,GLsizei height,
    GLenum format,GLenum type,
    const GLvoid* pixels
){
    if (m_cur_texture && m_cur_texture->level <= level){
        m_cur_texture->setSubData(
            target, level,
            xoffset, yoffset,
            width, height,
            format, type,
            pixels
        );
    }

}
void Renderer::setTextureEnv(GLenum mode){
    m_texture_env = mode;
}

void Renderer::drawTriangleInternal(
    FrameBuffer& fb,
    Vertex point_0,
    Vertex point_1,
    Vertex point_2
){
    DrawSettings set = createDrawSettings();

    m_rasterizer.drawTriangle(set, fb, point_0, point_1, point_2);
}


} // namespace cgl
