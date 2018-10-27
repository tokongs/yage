#pragma once
#include "config.h"
#include "ResourceLoader.h"
#include "Resource.h"
#include "Texture.h"


namespace yage
{
class TextureLoader : public ResourceLoader
{
  public:
    TextureLoader();
    ~TextureLoader();

    ResourcePtr load(std::string filepath) override;

  private:
    DECLARE_LOGGERS;
};
} // namespace yage