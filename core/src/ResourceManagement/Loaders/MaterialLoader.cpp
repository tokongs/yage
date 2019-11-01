#include <ResourceManagement/ResourceManager.h>
#include "MaterialLoader.h"

namespace yage {
    MaterialLoader::MaterialLoader() {
    }

    MaterialLoader::~MaterialLoader(){

    }

    Resource *MaterialLoader::load(std::string file_path) {
        std::string fileContent = mFileReader.readAsString(file_path);
        YAGE_INFO("Loading Material from {}", file_path);

        pugi::xml_document doc;
        pugi::xml_parse_result r = doc.load_string(fileContent.c_str());
        if(!r){
            YAGE_WARN("Failed to parse xml when loading material from {}", file_path);
            return nullptr;
        }
        pugi::xml_node root = doc.first_child();

        pugi::xml_node current = root.first_child();
        Material *result = nullptr;
        while(!current.empty()){
            if(std::string(current.name()) == "Shader"){
                result = new Material(ResourceManager::getInstance().getResource<Shader>(current.attribute("name").value()));
                YAGE_INFO("Done loading material {} from {}", root.attribute("name").value(), file_path);
            }
            if(std::string(current.name()) == "Texture"){
                if(result){
                    result->setAmbientTexture(ResourceManager::getInstance().getResource<Texture>(current.attribute("name").value()));
                    YAGE_INFO("Done loading material {} from {}", root.attribute("name").value(), file_path);
                }
                else{
                    YAGE_WARN("Set shader before texture in material!");
                    continue;
                }
            }
            current = current.next_sibling();
        }

        if(!result){
            YAGE_WARN("Failed to load material {} from {}", root.attribute("name").value(), file_path);
        }

        return result;
    }

} // namespace yage