#include "TextureLoader.h"
#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

namespace yage
{
DEFINE_LOGGERS(TextureLoader);
TextureLoader::TextureLoader()
{
    INIT_LOGGERS(TextureLoader);
}

TextureLoader::~TextureLoader()
{
}

ResourcePtr TextureLoader::load(std::string filepath)
{
    LOG(TextureLoader, info, "Trying to load texture from: " + filepath);
    int width, height, channels;
    unsigned char *image = stbi_load(filepath.c_str(), &width, &height, &channels, STBI_rgb);
    TexturePtr texture = std::make_shared<Texture>(width, height, image, GL_RGB);
    LOG(TextureLoader, info, "Texture Loaded successfully at OpenGL ID: " + std::to_string(texture->getGlObjectId()));

    return std::static_pointer_cast<Resource>(texture);
}

} // namespace yage