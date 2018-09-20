#include <IndexBuffer.h>
namespace yage
{
DEFINE_LOGGERS(IndexBuffer);
IndexBuffer::IndexBuffer(std::vector<unsigned int> data)
{
    INIT_LOGGERS(IndexBuffer);
    glCreateBuffers(1, &m_gl_object_id);
    LOG(IndexBuffer, info, "Created Index Buffer Object, ID: " + std::to_string(m_gl_object_id));
    bind();

    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * data.size(), &data[0], GL_STATIC_DRAW);
    unbind();

    m_shadow_copy = data;
}

IndexBuffer::~IndexBuffer()
{
    LOG(IndexBuffer, info, "Deleting Index Buffer Object, ID: " + std::to_string(m_gl_object_id));
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

unsigned int IndexBuffer::getGlId()
{
    return m_gl_object_id;
}
} // namespace yage