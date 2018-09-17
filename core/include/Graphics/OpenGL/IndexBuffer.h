#pragma once
#include <GL/glew.h>
#include <vector>
namespace yage
{
    /**
     * @brief IndexBuffer
     * 
     */
class IndexBuffer{
    public:
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

    private:

    GLuint m_gl_object_id;
    std::vector<unsigned int> m_shadow_copy;
};
}