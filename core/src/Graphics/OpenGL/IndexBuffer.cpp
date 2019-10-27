#include <IndexBuffer.h>
namespace yage
{
IndexBuffer::IndexBuffer(std::vector<unsigned int> data)
{

    glGenBuffers(1, &mGlObjectId);
    YAGE_INFO("Created Index Buffer Object, ID: " + std::to_string(mGlObjectId));
    bind();

    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * data.size(), &data[0], GL_STATIC_DRAW);
    unbind();
    mSize = data.size();
    m_shadow_copy = data;

}

IndexBuffer::~IndexBuffer()
{
    YAGE_INFO("Deleting Index Buffer Object, ID: " + std::to_string(mGlObjectId));
    glDeleteBuffers(1, &mGlObjectId);
}

void IndexBuffer::bind()
{
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mGlObjectId);
}

void IndexBuffer::unbind()
{
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

unsigned int IndexBuffer::getGlId()
{
    return mGlObjectId;
}

unsigned int IndexBuffer::getSize(){
    return mSize;
}

} // namespace yage