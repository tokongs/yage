#include "Texture.h"

namespace yage{
    Texture::Texture(unsigned char *textureData, int width, int height, int numChannels) {
        glGenTextures(1, &mGlObjectId);
        activate();
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, textureData);
        glGenerateMipmap(GL_TEXTURE_2D);
        YAGE_INFO("Texture created with OpenGL ID {}", mGlObjectId);
    }

    Texture::Texture(const yage::Texture &other) {
        mGlObjectId = other.mGlObjectId;
        mHeight = other.mHeight;
        mWidth = other.mWidth;
    }

    Texture& Texture::operator=(const yage::Texture &other) {
        mGlObjectId = other.mGlObjectId;
        mHeight = other.mHeight;
        mWidth = other.mWidth;
        return *this;
    }

    Texture::~Texture() {
        int id = mGlObjectId;
        glDeleteTextures(1, &mGlObjectId);
        YAGE_INFO("Texture deleted with OpenGL ID {}", id);

    }

    void Texture::activate() {
        glBindTexture(GL_TEXTURE_2D, mGlObjectId);
    }
}