#pragma once
#include <GL/glew.h>
#include <IndexBuffer.h>
#include <glm/vec4.hpp>
#include <glm/vec3.hpp>
#include <glm/vec2.hpp>
#include <vector>
#include <memory>
#include <config.h>


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
    bool has_position = false;        ///< Data contains position
    bool has_normal = false;          ///< Data contains normal
    bool has_color = false;          ///< Data contains color
    bool has_tex_coord = false;       ///< Data contains texture coordinates
    bool has_bones = false;          ///< Data has bones
    bool keep_shadow_buffer = false; ///< keep a shadow buffer in memory
};

/**
 * @brief Buffer that keeps vertex data in the graphics memory
 * Loads a series of verticesl into video memory with a specific layout depeneding
 * on what values the vertex contains. 
 * The data is interleaved like this with indexes:
 * 0:Position - 1:Normal - 2:Color - 3:Tex Coord - 4:Bone Id - 5:Bone Weight
 * The indexes will correspond with the right value even if one or more valures
 * aren't specified
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
     * @brief Bind the Vertex Array Object for operations on the graphics device
     */
    void bind();

    /**
     * @brief Unbind the Vertex Array Object so that it can no longer be modified by the graphics device
     */
    void unbind();
   
    /**
     * @brief Attach an IndexBuffer and enable indexed rendering for this buffer
     *
     * @param index_buffer std::shared_ptr<IndexBuffer> to the IndexBuffer to attach
     */
    void attachIndexBuffer(std::shared_ptr<IndexBuffer> index_buffer);

  private:
    /**
     * @brief Convert from a vector of vertices to an array of floats that can be loaded into video memory
     * 
     * @param desc 
     * @param data 
     * @param result 
     */
    void cleanData(VertexBufferDesc desc, std::vector<Vertex> data, float* result);

    /**
     * @brief Set up the OpengGL VAO so that the format of the vertex buffer can be interpreted by the GPU
     * 
     * @param desc 
     */
    void setupVao(VertexBufferDesc desc);
    GLuint m_vb_object_id;
    GLuint m_vao_object_id;

    VertexBufferDesc m_buffer_desc;
    std::shared_ptr<IndexBuffer> m_index_buffer;
    bool m_indexed = false;
    std::vector<float> m_shadow_copy;

    DECLARE_LOGGERS;

    private:
    /**
     * @brief Calculate the size of one verterx in bytes. Assumes all components are floats. May have to change...
     * 
     * @param desc 
     * @return int 
     */
    int sizeOfVertex(VertexBufferDesc desc);
};
} // namespace yage
