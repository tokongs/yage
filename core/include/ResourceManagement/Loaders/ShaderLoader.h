#pragma once
#include <memory>
#include "config.h"
#include "ResourceLoader.h"
#include "Resource.h"
#include "Shader.h"
#include "FileReader.h"
namespace yage
{
class ShaderLoader : public ResourceLoader
{
  public:
    ShaderLoader();
    ~ShaderLoader();

    ResourcePtr load(std::string file_path) override;

  private:
    DECLARE_LOGGERS;
    FileReader m_file_reader;
};
} // namespace yage