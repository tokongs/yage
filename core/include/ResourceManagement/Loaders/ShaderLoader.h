#pragma once
#include "pugixml/pugixml.hpp"
#include <memory>
#include "config.h"
#include "ResourceLoader.h"
#include "Resource.h"
#include "Shader.h"
#include "FileReader.h"
#include "Logger.h"
namespace yage
{
class ShaderLoader : public ResourceLoader
{
  public:
    ShaderLoader();
    ~ShaderLoader();

    Resource* load(std::string filePath) override;

  private:
    FileReader mFileReader;
};
} // namespace yage