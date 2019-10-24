#include "ShaderLoader.h"

namespace yage
{

ShaderLoader::ShaderLoader()
{
}

ShaderLoader::~ShaderLoader()
{
}

ResourcePtr ShaderLoader::load(int id, std::string name, std::string file_path)
{

    YAGE_INFO("Loading shader form file: " + file_path);
    ShaderType type;
    if (std::string(file_path.end() - 2, file_path.end()) == "fs")
    {
        type = ShaderType::FRAGMENT_SHADER;
    }else if(std::string(file_path.end() - 2, file_path.end()) == "vs"){
        type = ShaderType::VERTEX_SHADER;

    }

    std::string code = m_file_reader.readAsString(file_path);

    if(code.empty()){
        YAGE_ERROR("Trying to load shader from empty file: " + file_path);
        return nullptr;
    }
    ShaderPtr result = std::make_shared<Shader>(id, name, file_path, code, type);

    return std::dynamic_pointer_cast<Resource>(result);
}
} // namespace yage