#pragma once
#include <GL/glew.h>
#include <glm/vec4.hpp>
#include <glm/vec3.hpp>
#include <glm/vec2.hpp>
#include <vector>

namespace yage
{

/**
 * @brief A vertex
 * 
 */
struct Vertex
{
    glm::vec3 position;
    glm::vec3 normal;
    glm::vec3 color;
    glm::vec2 tex_coord;
    glm::vec4 bone_id;
    glm::vec4 bone_weight;
};

/**
 * @brief Decription and data needed for the creation of a vertex buffer
 * 
 */
struct VertexBufferDesc
{
    bool has_position = true;        ///< Data contains position
    bool has_normal = true;          ///< Data contains normal
    bool has_color = false;          ///< Data contains color
    bool has_tex_coord = true;       ///< Data contains texture coordinates
    bool has_bones = false;          ///< Data has bones
    bool keep_shadow_buffer = false; ///< keep a shadow buffer in memory
};

/**
 * @brief Buffer that keeps vertex data in the graphics memory
 * 
 */
class VertexBuffer
{

  public:
    /**
   * @brief Construct a new Vertex Buffer object
   * 
   * @param desc 
   * @param data 
   */
    VertexBuffer(VertexBufferDesc desc, std::vector<Vertex> data);
    ~VertexBuffer();

    /**
     * @brief Bind the vertex buffer for operations on the graphics device
     */
    void bind();

    /**
     * @brief Unbind the vertex buffer so that it can no longer be modified by the graphics device
     */
    void unbind();

  private:
    /**
     * @brief Convert from a vector of vertices to an array of floats that can be loaded into video memory
     * 
     * @param desc 
     * @param data 
     * @param result 
     */
    void cleanData(VertexBufferDesc desc, std::vector<Vertex> data, float* result);

    GLuint m_gl_object_id;
    VertexBufferDesc m_buffer_desc;
    float* m_shadow_copy;
};
} // namespace yage