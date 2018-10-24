#pragma once
#include <memory>
#include <GL/glew.h>
#include "Resource.h"

namespace yage
{

class Texture : public Resource
{
    static const int TextureUnit0 = GL_TEXTURE0;

  public:
    Texture();
    ~Texture();

  private:
    unsigned int m_gl_object_id;

    unsigned int m_texture_unit;

    unsigned int m_s_wrapping;
    unsigned int m_t_wrapping;
    unsigned int m_mag_filtering;
    unsigned int m_min_filtering;
};

typedef std::shared_ptr<Texture> TexturePtr;
} // namespace yage