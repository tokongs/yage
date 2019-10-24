#include "ScriptLoader.h"

namespace yage{
    ScriptLoader::ScriptLoader(){

    }

    ScriptLoader::~ScriptLoader() {

    }

    ResourcePtr ScriptLoader::load(int id, std::string name, std::string file_path) {
        FileReader file_reader;
        ScriptPtr result = std::make_shared<Script>(id, name, file_path, file_reader.readAsString(file_path));

        return result;
    }
}