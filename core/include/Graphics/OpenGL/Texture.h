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
    unsigned int mGlObjectId;

    unsigned int mTextureUnit;

    unsigned int mSWrapping;
    unsigned int mTWrapping;
    unsigned int mMagFiltering;
    unsigned int mMinFiltering;
};
} // namespace yage