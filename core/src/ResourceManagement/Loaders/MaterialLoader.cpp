#include <ResourceManagement/ResourceManager.h>
#include "MaterialLoader.h"

namespace yage {
    MaterialLoader::MaterialLoader() {
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
        while(!current.empty()){
            if(std::string(current.name()) == "shader"){
                Material *result = new Material(ResourceManager::getInstance().getResource<Shader>(current.attribute("name").value()));
                YAGE_INFO("Done loading material {} from {}", root.attribute("name").value(), file_path);
                return result;
            }
            current = current.next_sibling();
        }


        YAGE_WARN("Failed to load material {} from {}", root.attribute("name").value(), file_path);
        return nullptr;
    }

} // namespace yage