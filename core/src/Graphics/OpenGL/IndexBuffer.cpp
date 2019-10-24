#include <IndexBuffer.h>
namespace yage
{
IndexBuffer::IndexBuffer(std::vector<unsigned int> data)
{

    glGenBuffers(1, &m_gl_object_id);
    YAGE_INFO("Created Index Buffer Object, ID: " + std::to_string(m_gl_object_id));
    bind();

    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * data.size(), &data[0], GL_STATIC_DRAW);
    unbind();
    m_size = data.size();
    m_shadow_copy = data;

}

IndexBuffer::~IndexBuffer()
{
    YAGE_INFO("Deleting Index Buffer Object, ID: " + std::to_string(m_gl_object_id));
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

unsigned int IndexBuffer::getSize(){
    return m_size;
}

} // namespace yage