
#include <Util/FileReader.h>
#include "AngelScriptLoader.h"

namespace yage{
    AngelScriptLoader::AngelScriptLoader(){

    }

    AngelScriptLoader::~AngelScriptLoader() {

    }

    ResourcePtr AngelScriptLoader::load(std::string file_path) {
        FileReader file_reader;
        ScriptPtr result = std::make_shared<Script>(file_reader.readAsString(file_path));

        return result;
    }
}