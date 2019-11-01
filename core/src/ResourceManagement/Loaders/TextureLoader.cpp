#include "TextureLoader.h"
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image/stb_image.h"

namespace yage {
    TextureLoader::TextureLoader() {
    }

    TextureLoader::~TextureLoader() {

    }
    Resource *TextureLoader::load(std::string file_path) {
        std::string fileContent = mFileReader.readAsString(file_path);
        YAGE_INFO("Loading Material from {}", file_path);

        pugi::xml_document doc;
        pugi::xml_parse_result r = doc.load_string(fileContent.c_str());
        if(!r){
            YAGE_WARN("Failed to parse xml when loading material from {}", file_path);
            return nullptr;
        }
        pugi::xml_node root = doc.first_child();

        std::string path = root.attribute("path").value();

        int width, height, numChannels;
        unsigned char *data = stbi_load(path.c_str(), &width, &height, &numChannels, 0);

        Texture *result = new Texture(data, width, height, numChannels);
        stbi_image_free(data);
        return result;
    }

} // namespace yage