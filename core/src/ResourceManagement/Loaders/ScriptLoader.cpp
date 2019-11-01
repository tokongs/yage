#include "ScriptLoader.h"

namespace yage{
    ScriptLoader::ScriptLoader(){

    }

    ScriptLoader::~ScriptLoader() {

    }

    Resource* ScriptLoader::load(std::string file_path) {
        FileReader file_reader;

        pugi::xml_document doc;
        pugi::xml_parse_result r = doc.load_string(file_reader.readAsString(file_path).c_str());
        if(!r){
            YAGE_WARN("Failed to parse xml when loading script from {}", file_path);
            return nullptr;
        }
        pugi::xml_node root = doc.first_child();
        Script* result = new Script(file_reader.readAsString(root.attribute("path").value()));

        return result;
    }
}