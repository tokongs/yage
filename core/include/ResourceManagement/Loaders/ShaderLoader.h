#pragma once
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

    ResourcePtr load(int id, std::string name, std::string file_path) override;

  private:
    FileReader m_file_reader;
};
} // namespace yage