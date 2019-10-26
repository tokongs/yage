#include "ShaderLoader.h"

namespace yage
{

ShaderLoader::ShaderLoader()
{
}

ShaderLoader::~ShaderLoader()
{
}

Resource* ShaderLoader::load(std::string file_path)
{

    YAGE_INFO("Loading shader form file: " + file_path);
    ShaderType type;
    if (std::string(file_path.end() - 2, file_path.end()) == "fs")
    {
        type = ShaderType::FRAGMENT_SHADER;
    }else if(std::string(file_path.end() - 2, file_path.end()) == "vs"){
        type = ShaderType::VERTEX_SHADER;

    }

    std::string code = mFileReader.readAsString(file_path);

    if(code.empty()){
        YAGE_ERROR("Trying to load shader from empty file: " + file_path);
        return nullptr;
    }
    Shader* result = new Shader(code, type);

    return result;
}
} // namespace yage