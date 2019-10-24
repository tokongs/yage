/*
#include <Util/FileReader.h>
#include <Scripting/Script.h>
#include "AngelScriptLoader.h"

namespace yage{
    AngelScriptLoader::AngelScriptLoader(){

    }

    AngelScriptLoader::~AngelScriptLoader() {

    }

    ResourcePtr AngelScriptLoader::load(int id, std::string name, std::string file_path) {
        FileReader file_reader;
        ScriptPtr result = std::make_shared<Script>(id, name, file_path);
        result->compile(file_path, file_reader.readAsString(file_path));

        return result;
    }
}*/