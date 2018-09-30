#include "ShaderLoader.h"

namespace yage
{
DEFINE_LOGGERS(ShaderLoader)

ShaderLoader::ShaderLoader()
{
    INIT_LOGGERS(ShaderLoader);
}

ShaderLoader::~ShaderLoader()
{
}

ResourcePtr ShaderLoader::load(std::string file_path)
{

    LOG(ShaderLoader, info, "Loading shader form file: " + file_path);
    ShaderType type;
    if (std::string(file_path.end() - 2, file_path.end()) == "fs")
    {
        type = ShaderType::FRAGMENT_SHADER;
    }else if(std::string(file_path.end() - 2, file_path.end()) == "vs"){
        type = ShaderType::VERTEX_SHADER;

    }

    std::string code = m_file_reader.readAsString(file_path);

    if(code.empty()){
        LOG(ShaderLoader, error, "Trying to load shader from empty file: " + file_path);
        return nullptr;
    }
    ShaderPtr result = std::make_shared<Shader>(code, type);

    return std::dynamic_pointer_cast<Resource>(result);
}
} // namespace yage