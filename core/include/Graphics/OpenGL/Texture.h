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
    Texture(unsigned char * textureData, int width, int height, int numChannels);
    ~Texture();
    Texture(const Texture &other);

    Texture& operator= (const Texture &other);

    void activate();

  private:

    int mWidth;
    int mHeight;
    int mNumChannels;

    unsigned int mGlObjectId;
    unsigned int mTextureUnit;

    unsigned int mSWrapping;
    unsigned int mTWrapping;
    unsigned int mMagFiltering;
    unsigned int mMinFiltering;
};
} // namespace yage