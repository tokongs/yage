#pragma once
#include <GL/glew.h>
#include <IndexBuffer.h>
#include <glm/vec4.hpp>
#include <glm/vec3.hpp>
#include <glm/vec2.hpp>
#include <vector>
#include <memory>
#include <config.h>
#include "Logger.h"

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
    glm::vec2 texCoord;
    glm::vec4 boneId;
    glm::vec4 boneWeight;
};

/**
 * @brief Decription and data needed for the creation of a vertex buffer
 * 
 */
struct VertexBufferDesc
{
    bool hasPosition = false;        ///< Data contains position
    bool hasNormal = false;          ///< Data contains normal
    bool hasColor = false;          ///< Data contains color
    bool hasTexCoord = false;       ///< Data contains texture coordinates
    bool hasBones = false;          ///< Data has bones
    bool keepShadowBuffer = false; ///< keep a shadow buffer in memory
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
   VertexBuffer();
    VertexBuffer(VertexBufferDesc desc, std::vector<Vertex> data, std::vector<unsigned int> indices);
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
    void attachIndexBuffer(IndexBuffer* indexBuffer);

    /**
     * @brief Get the Index Buffer object
     * 
     * @return std::shared_ptr<IndexBuffer> 
     */
    IndexBuffer* getIndexBuffer();

    /**
     * @brief Get the number of vertices in the buffer
     * 
     * @return unsigned int 
     */
    unsigned int getSize();
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
    unsigned int mVbObjectId;
    unsigned int mVaoObjectId;

    unsigned int mSize;

    VertexBufferDesc mBufferDesc;
    IndexBuffer *mIndexBuffer = nullptr;
    bool mIndexed = false;
    std::vector<float> mShadowCopy;

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
