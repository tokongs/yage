#include <IndexBuffer.h>
namespace yage
{
IndexBuffer::IndexBuffer(std::vector<unsigned int> data)
{
    glCreateBuffers(1, &m_gl_object_id);
    bind();

    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * data.size(), &data[0], GL_STATIC_DRAW);
    unbind();

    m_shadow_copy = data;
}

IndexBuffer::~IndexBuffer()
{
    glDeleteBuffers(1, &m_gl_object_id);
}

void IndexBuffer::bind()
{
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_gl_object_id);
}

void IndexBuffer::unbind()
{
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}
} // namespace yage