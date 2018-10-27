#include "Texture.h"

namespace yage
{
DEFINE_LOGGERS(Texture);
Texture::Texture(float width,
                 float height,
                 const void *data,
                 int format)
    : m_wrapping(GL_REPEAT), m_filtering(GL_LINEAR), m_texture_unit(0)
{
    INIT_LOGGERS(Texture)
    LOG(Texture, info, "Creating Texture");
    glGenTextures(1, &m_gl_object_id);
    glBindTexture(GL_TEXTURE_2D, m_gl_object_id);

    setOptions();
    loadData(width, height, data, format);
}

Texture::Texture()
    : m_wrapping(GL_REPEAT), m_filtering(GL_LINEAR)

{
    INIT_LOGGERS(Texture)
    LOG(Texture, info, "Creating Texture");
    glGenTextures(1, &m_gl_object_id);
    glBindTexture(GL_TEXTURE_2D, m_gl_object_id);

    setOptions();
    LOG(Texture, info, "Texture created with OpenGL ID: " + std::to_string(m_gl_object_id));
}

Texture::~Texture()
{
    LOG(Texture, info, "deleting texture with OpenGL ID: " + std::to_string(m_gl_object_id));
    glDeleteTextures(1, &m_gl_object_id);
}

void Texture::bind()
{
    glActiveTexture(TextureUnit0 + m_texture_unit);
    glBindTexture(GL_TEXTURE_2D, m_gl_object_id);
}

void Texture::setOptions()
{
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, m_wrapping);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, m_wrapping);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, m_filtering);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, m_filtering);
}

void Texture::loadData(float width, float height, const void *data, int format)
{
    glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
    glGenerateMipmap(GL_TEXTURE_2D);
}

void Texture::setWrapping(int wrap)
{
    m_wrapping = wrap;
}

void Texture::setFiltering(int filtering)
{
    m_filtering = filtering;
}

int Texture::getWrapping()
{
    return m_wrapping;
}

int Texture::getFiltering()
{
    return m_filtering;
}

int Texture::getGlObjectId()
{
    return m_gl_object_id;
}

void Texture::setTextureUnit(int unit)
{
    m_texture_unit = unit;
}

unsigned int Texture::getTextureUnit()
{
    return m_texture_unit;
}

} // namespace yage