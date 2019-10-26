#include "ScriptLoader.h"

namespace yage{
    ScriptLoader::ScriptLoader(){

    }

    ScriptLoader::~ScriptLoader() {

    }

    Resource* ScriptLoader::load(std::string file_path) {
        FileReader file_reader;

        Script* result = new Script(file_reader.readAsString(file_path));

        return result;
    }
}