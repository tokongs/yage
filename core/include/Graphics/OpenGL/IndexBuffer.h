#pragma once
#include <GL/glew.h>
#include <vector>
#include <config.h>
namespace yage
{
    /**
     * @brief IndexBuffer
     * 
     */
class IndexBuffer{
    public:
    /**
     * @brief Construct a new Index Buffer object with the indices in a vector as the argument
     * 
     */
    IndexBuffer(std::vector<unsigned int>);
    ~IndexBuffer();

    /**
     * @brief Bind the Index Buffer for operations on the graphics device
     * 
     */
    void bind();
    /**
     * @brief Unbind the Index Buffer so that it can't be modified on the graphics device
     * 
     */
    void unbind();

    /**
     * @brief Get the Id of the underlying gl object
     * 
     * @return unsigned int 
     */
    unsigned int getGlId();

    /**
     * @brief Get the the number of elements in the buffer
     * 
     * @return unsigned int 
     */
    unsigned int getSize();

    private:

    GLuint m_gl_object_id;
    unsigned int m_size;
    std::vector<unsigned int> m_shadow_copy;

    DECLARE_LOGGERS;
};
}