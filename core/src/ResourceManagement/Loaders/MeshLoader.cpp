#include "MeshLoader.h"

namespace yage {
    MeshLoader::MeshLoader() {
    }

    MeshLoader::~MeshLoader() {

    }
    Resource *MeshLoader::load(std::string file_path) {
        std::string fileContent = mFileReader.readAsString(file_path);
        YAGE_INFO("Loading Mesh from {}", file_path);

        pugi::xml_document doc;
        pugi::xml_parse_result r = doc.load_string(fileContent.c_str());
        if(!r){
            YAGE_WARN("Failed to parse xml when loading mesh from {}", file_path);
            return nullptr;
        }
        pugi::xml_node root = doc.first_child();
       ;
        if (std::string(root.first_child().name()) == "Wavefront") {
            VertexBuffer *buffer = mWavefrontLoader.loadWavefront(root.first_child().attribute("path").value());
            Mesh *result = new Mesh(buffer);
            YAGE_INFO("Done loading mesh {} from {}", root.attribute("name").value(), file_path);
            return result;
        }

        YAGE_WARN("Failed to load mesh {} from {}", root.attribute("name").value(), file_path);
        return nullptr;
    }

} // namespace yage