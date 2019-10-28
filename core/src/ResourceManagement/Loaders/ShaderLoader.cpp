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

    std::string fileContent = mFileReader.readAsString(file_path);
    YAGE_INFO("Loading shader from {}", file_path);

    pugi::xml_document doc;
    pugi::xml_parse_result r = doc.load_string(fileContent.c_str());
    if(!r){
        YAGE_WARN("Failed to parse xml when loading shader from {}", file_path);
        return nullptr;
    }
    pugi::xml_node root = doc.first_child();
    pugi::xml_node current = root.first_child();
    std::string vs = "";
    std::string fs = "";

    while(!current.empty()){
        if(!current.attribute("path").value())
            continue;
        if(std::string(current.name()) == "vertexshader"){
            vs = mFileReader.readAsString(current.attribute("path").value());
        }
        if(std::string(current.name()) == "fragmentshader"){
            fs = mFileReader.readAsString(current.attribute("path").value());
        }
        current = current.next_sibling();
    }
    if(vs.size() == 0 && fs.size() == 0){
        YAGE_WARN("Cannot load shader {} from {}", root.attribute("name").value(), file_path);
        return nullptr;
    }
    Shader* result = new Shader(vs, fs);
    if(result)
        YAGE_INFO("Loaded shader {} from {}", root.attribute("name").value(), file_path);
    return result;
}
} // namespace yage